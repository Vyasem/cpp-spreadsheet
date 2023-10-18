#pragma once

#include "common.h"

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

struct GraphHasher {
    size_t operator()(Position pos) const {
        return (pos.row + pos.col) * pos.row * pos.col;
    }
};

class DirectGraph {
public:
    DirectGraph();
    ~DirectGraph();

    void AddVertex(Position from, Position to);
    void FindCyclicDependencies(Position pos);    
    void InvalidateCache(Position findPos, SheetInterface& sh);
    void dfs(const Position* node, Position findPos, std::unordered_map < const Position*, char>& colors, SheetInterface& sh);

private:
    std::unordered_set<Position, GraphHasher> vertexList;
    std::unordered_map<const Position*, std::unordered_set<const Position*>> graph_;
};

struct SheetHasher {
    size_t operator()(int key) const {
        return key;
    }
};

class Sheet : public SheetInterface {
public:
    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;
    void InvalidateCellCache(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

    void CreateDependencies(Position from, const std::vector<Position>& dependencies) override;

    void FindCyclicDependencies(Position pos) override;

    void InvalidateCache(Position pos) override;

private:
    const CellInterface* GetCellPtr(Position pos) const;
private:
    std::unordered_map<int, std::unordered_map<int, std::unique_ptr<CellInterface>, SheetHasher>, SheetHasher> sheet_;
    Size printAbleSize_;
    DirectGraph graph_;
    std::unique_ptr<CellInterface> emptyCell;
};
