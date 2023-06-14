#include "common.h"
#include "cell.h"

#include <cassert>
#include <iostream>
#include <string>
#include <optional>


CellInterface::Value EmptyImpl::GetValue(const SheetInterface&) const {
	return GetText();
}

std::string EmptyImpl::GetText() const {
	return "";
}

TextImpl::TextImpl(std::string expr) : value_(std::move(expr)){}

CellInterface::Value TextImpl::GetValue(const SheetInterface&) const {
	if (value_[0] == ESCAPE_SIGN) {
		return GetText().substr(1);
	}
	return GetText();
}

std::string TextImpl::GetText() const {
	return value_;
}

FormulaImpl::FormulaImpl(std::string expr) : value_(std::move(ParseFormula(std::move(expr)))) {}

CellInterface::Value FormulaImpl::GetValue(const SheetInterface& sheet) const {
	FormulaInterface::Value result = value_->Evaluate(sheet);
	if (std::holds_alternative<double>(result)) {
		return std::get<double>(result);
	}
	return std::get<FormulaError>(result);
}

std::string FormulaImpl::GetText() const {
	return '='+value_->GetExpression();
}

std::vector<Position> FormulaImpl::GetReferencedCells() const {
	return value_->GetReferencedCells();
}

Cell::Cell(SheetInterface& sheet) : impl_(std::make_unique<EmptyImpl>()), sheet_(sheet){}
Cell::~Cell() = default;

void Cell::Set(std::string text) {
	if (text.empty()) {
		impl_ = std::make_unique<EmptyImpl>();
	}else if (text[0] != FORMULA_SIGN || text.size() == 1) {
		impl_ = std::make_unique<TextImpl>(text);
	}else {
		impl_ = std::make_unique<FormulaImpl>(text.substr(1));		
	}
}

void Cell::Clear() {
	impl_.reset();
}

void Cell::ClearCache() {
	cache_.valid = false;
	cache_.value = 0.0;
}

void Cell::SetCache(double value) {
	cache_.valid = true;
	cache_.value = value;
}

bool Cell::HasCache() {
	return cache_.valid;
}

double Cell::GetCache() {
	if (HasCache()) {
		return cache_.value;
	}
	return 0.0;
}

Cell::Value Cell::GetValue() {
	if (HasCache()) {
		return GetCache();
	}

	Cell::Value res = impl_->GetValue(sheet_);
	if (std::holds_alternative<double>(res)) {
		SetCache(std::get<double>(res));
		return GetCache();
	}
	return res;
}

std::string Cell::GetText() const {
	return impl_->GetText();
}

std::vector<Position> Cell::GetReferencedCells() const {
	return impl_->GetReferencedCells();
}
