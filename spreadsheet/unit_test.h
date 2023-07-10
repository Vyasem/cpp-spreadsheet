#pragma once

#include <iostream>
#include "common.h"
#include "formula.h"

class UnitTest{
public:
    UnitTest(int argc, char** argv);
    int run();
private:
    static void TestPositionAndStringConversion();
    static void TestPositionToStringInvalid();
    static void TestStringToPositionInvalid();
    static void TestEmpty();
    static void TestInvalidPosition();
    static void TestSetCellPlainText();
    static void TestClearCell();
    static void TestFormulaArithmetic();
    static void TestFormulaReferences();
    static void TestFormulaExpressionFormatting();
    static void TestFormulaReferencedCells();
    static void TestErrorValue();
    static void TestErrorDiv0();
    static void TestEmptyCellTreatedAsZero();
    static void TestFormulaInvalidPosition();
    static void TestPrint();
    static void TestCellReferences();
    static void TestFormulaIncorrect();
    static  void TestCellCircularReferences();
    static void TestValidFormula();
private:
int t_argc;
char** t_argv;
};
