#include "formula.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std::literals;

std::ostream& operator<<(std::ostream& output, FormulaError fe) {
    return output << fe.ToString();
}

class Formula : public FormulaInterface {
public:
    explicit Formula(std::string expression) : ast_(ParseFormulaAST(expression)) {}
    Value Evaluate(const SheetInterface& sheet) const override {
        Value result;
        try {
            result = ast_.Execute(sheet);
        }
        catch (const FormulaError& error) {
            result = error;
        }
        return result;
    }

    std::string GetExpression() const override {
        std::ostringstream os;
        ast_.PrintFormula(os);
        return os.str();
    }

    std::vector<Position> GetReferencedCells() const override {
        std::vector<Position> a = ast_.GetReferencedCells();
        return a;
    }

private:
    FormulaAST ast_;
};

std::unique_ptr<FormulaInterface> ParseFormula(std::string expression) {
    return std::make_unique<Formula>(std::move(expression));
}