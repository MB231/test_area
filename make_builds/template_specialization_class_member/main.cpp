#include <iostream>
#include "classTest.hpp"

void callParentFuncTest(Interface& interface) {
    std::cout << "\n\ncalling interface functions:\n" << std::endl;
    interface.read();
    interface.serialfunc();

}
int main() {
    std::cout << "\nnormal Test:\n" << std::endl;

    normalDFPort dfNormal;
    dfNormal.serialfunc();
    dfNormal.read();

    std::cout << "\n\neth Test:\n" << std::endl;

    ethDFPort df;
    df.serialfunc();
    df.ethFunc();
    df.read();

    std::cout << "\n\n Templated eth Test:\n" << std::endl;

    templatedClass<ethDFPort> templtedDf;
    templtedDf.serialfunc();
    templtedDf.ethFunc();
    templtedDf.read();

    std::cout << "\n\n Templated serial Test:\n" << std::endl;

    templatedClass<serialClass> templetedSerial;
    templetedSerial.serialfunc();
    templetedSerial.read();

    std::cout << "\n\n default serial Test:\n" << std::endl;

    templatedClass<otherClass> otherSerial;
    otherSerial.serialfunc();
    otherSerial.read();

    callParentFuncTest(templtedDf);
    return 0;
}
