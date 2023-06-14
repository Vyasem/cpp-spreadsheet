#pragma once

#include "common.h"
#include "formula.h"
#include <algorithm>

class Impl {
public:
	virtual ~Impl() = default;
    virtual CellInterface::Value GetValue(const SheetInterface&) const = 0;
    virtual std::string GetText() const = 0;
    virtual std::vector<Position> GetReferencedCells() const {
        return {};
    };
};

class EmptyImpl : public Impl {
public:
    CellInterface::Value GetValue(const SheetInterface&) const override;
    std::string GetText() const override;
};

class TextImpl : public Impl {
public:
    explicit TextImpl(std::string expr);
    CellInterface::Value GetValue(const SheetInterface&) const override;
    std::string GetText() const override;
private:
    std::string value_;
};

class FormulaImpl : public Impl {
public:
    explicit FormulaImpl(std::string expr);
    CellInterface::Value GetValue(const SheetInterface& sheet) const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;
private:
    std::unique_ptr<FormulaInterface> value_;
};


struct CellCache {
    double value = 0.0;
    bool valid = false;
};

class Cell : public CellInterface {
public:
    Cell() = default;
    explicit Cell(SheetInterface& sheet);
    ~Cell();

    void Set(std::string text) override;
    void Clear();
    void ClearCache() override;

    void SetCache(double value);
    bool HasCache();
    double GetCache();

    Value GetValue() override;
    std::string GetText() const override;

    std::vector<Position> GetReferencedCells() const override;
    bool IsReferenced() const;

private:    
    std::unique_ptr<Impl> impl_;
    SheetInterface& sheet_;
    CellCache cache_;
};
