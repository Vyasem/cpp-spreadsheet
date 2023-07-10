#include "gui/gui.h"
#include "unit_test.h"

int test(int argc, char** argv){
    UnitTest testObj(argc, argv);
    return testObj.run();
}

int main(int argc, char** argv) {
    return test(argc, argv);
 }
