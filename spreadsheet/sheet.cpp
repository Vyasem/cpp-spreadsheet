#include "common.h"
#include "sheet.h"
#include "cell.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>
#include <memory>
#include <utility>

using namespace std::literals;

DirectGraph::DirectGraph() = default;
DirectGraph::~DirectGraph() = default;

void DirectGraph::AddVertex(Position from, Position to) {
    graph_[&*vertexList.insert(from).first].insert(&*vertexList.insert(to).first);
}

void DirectGraph::FindCyclicDependencies(Position pos) {
    auto a = vertexList.find(pos);
    std::unordered_map <const Position*, char> colors;
    std::vector<const Position*> stack;
    stack.push_back(&*a);
    while (!stack.empty()) {
        const Position* v = stack[stack.size() - 1];
        stack.pop_back();
        if (!colors.count(v)) {            
            colors[v] = 'g';
            stack.push_back(v);
            for (const Position* i : graph_[v]) {
                if (!colors.count(i)) {
                    stack.push_back(i);
                }else if (colors[i] == 'g') {                    
                    throw CircularDependencyException("Cycle");
                }
            }
        }else if (colors[v] == 'g') {
            colors[v] = 'b';
        }
    }
}

void DirectGraph::dfs(const Position* node, Position findPos, std::unordered_map < const Position*, char>& colors, SheetInterface& sh) {
    colors[node] = 'g';
    for (const Position* i : graph_[node]) {
        if (!colors.count(i)) {
            dfs(i, findPos, colors, sh);
        }

        if (colors[i] == 'r') {
            colors[node] = 'r';
            sh.InvalidateCellCache(*node);
        }
    }
    if (colors[node] != 'r') {
        if (*node == findPos) {
            colors[node] = 'r';
            sh.InvalidateCellCache(*node);
        }else {
            colors[node] = 'b';
        }
    }
}

void DirectGraph::InvalidateCache(Position findPos, SheetInterface& sh) {
    std::unordered_map < const Position*, char> colors;
    for (const Position& pos : vertexList) {
        if (colors.count(&pos)) {
            continue;
        }
        dfs(&pos, findPos, colors, sh);
    }
}

Sheet::~Sheet() = default;

void Sheet::SetCell(Position pos, std::string text) {
    if (!pos.IsValid()) {
        throw InvalidPositionException("Wrong position");
    }

    if (!sheet_[pos.row][pos.col].get()) {
        sheet_[pos.row][pos.col] = std::make_unique<Cell>(*this);        
    }

    std::string prevCellText = sheet_[pos.row][pos.col]->GetText();
    sheet_[pos.row][pos.col]->ClearCache();
    sheet_[pos.row][pos.col]->Set(text);    

    std::vector<Position> refs = sheet_[pos.row][pos.col]->GetReferencedCells();
    if (!refs.empty()) {
        for (const Position& innerPos : refs) {
            graph_.AddVertex(pos, innerPos);
        }

        try {
            graph_.FindCyclicDependencies(pos);
        }catch (...) {
            sheet_[pos.row][pos.col]->Set(prevCellText);
            throw;
        }
        
    }
    graph_.InvalidateCache(pos, *this);
    
    if (pos.row >= printAbleSize_.rows) {
        printAbleSize_.rows = pos.row + 1;
    }

    if (pos.col >= printAbleSize_.cols) {
        printAbleSize_.cols = pos.col + 1;
    }
}

const CellInterface* Sheet::GetCellPtr(Position pos) const {
    if (!pos.IsValid()) {
        throw InvalidPositionException("Wrong position");
    }

    try {
        return sheet_.at(pos.row).at(pos.col).get();
    }catch (...) {}

    return nullptr;
}

const CellInterface* Sheet::GetCell(Position pos) const {
    return GetCellPtr(pos);
}

CellInterface* Sheet::GetCell(Position pos) {
    return const_cast<CellInterface*>(GetCellPtr(pos));
}

void Sheet::ClearCell(Position pos) {
    if (!pos.IsValid()) {
        throw InvalidPositionException("Wrong position");
    }

    sheet_[pos.row][pos.col].reset();
    bool removeRow = true;
    int removeAfterCol = -1;
    for (int row = printAbleSize_.rows - 1; row >= 0; --row) {
        for (int col = printAbleSize_.cols - 1; col > removeAfterCol; --col) {
            if (GetCell({ row , col })) {
                removeRow = false;
                removeAfterCol = col;
                break;
            }
        }

        if (!removeRow) {
            continue;
        }
        --printAbleSize_.rows;
    }
    printAbleSize_.cols -= printAbleSize_.cols - (removeAfterCol + 1);
}

Size Sheet::GetPrintableSize() const {
    return printAbleSize_;
}

void Sheet::PrintValues(std::ostream& output) const {
    for (int row = 0; row < printAbleSize_.rows; ++row) {
        for (int col = 0; col < printAbleSize_.cols; ++col) {
            try {
                if (sheet_.at(row).at(col).get()) {
                    auto val = sheet_.at(row).at(col)->GetValue();
                    if (std::holds_alternative<double>(val)) {
                        output << std::get<double>(val);                       
                    }
                    else if (std::holds_alternative<std::string>(val)) {
                        output << std::get<std::string>(val);
                    }
                    else {
                        FormulaError error = std::get<FormulaError>(val);
                        output << error;
                    }
                }
            }catch (...) {}
            if (col < printAbleSize_.cols - 1) {
                output << '\t';
            }
        }
        output << '\n';
    }
}

void Sheet::PrintTexts(std::ostream& output) const {
    for (int row = 0; row < printAbleSize_.rows; ++row) {
        for (int col = 0; col < printAbleSize_.cols; ++col) {
            try {
                if (sheet_.at(row).at(col).get()) {
                    output << sheet_.at(row).at(col)->GetText();
                }
            }catch (...) {}
            if (col < (printAbleSize_.cols - 1)) {
                output << '\t';
            }
        }
        output << '\n';
    }
}

void Sheet::CreateDependencies(Position from, const std::vector<Position>& dependencies) {
    for (const Position& to : dependencies) {
        graph_.AddVertex(from, to);
    }
}

void Sheet::FindCyclicDependencies(Position pos) {
    graph_.FindCyclicDependencies(pos);
}

void Sheet::InvalidateCache(Position pos) {
    graph_.InvalidateCache(pos, *this);
}

void Sheet::InvalidateCellCache(Position pos) {
    sheet_[pos.row][pos.col]->ClearCache();
}

std::unique_ptr<SheetInterface> CreateSheet() {
    return std::make_unique<Sheet>();
}
