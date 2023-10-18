#include "unit_test.h"
#include "gui/gui.h"

int test(int argc, char** argv){
    QApplication app(argc, argv);
    UnitTest testObj;
    testObj.run();
    return app.exec();
}

int main(int argc, char** argv) {
    Gui gui(argc, argv);
    return gui.run();
 }
