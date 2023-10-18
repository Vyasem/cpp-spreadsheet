#pragma once

class UnitTest{
public:
    UnitTest();
    void run();
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
};
