#ifndef COMPLEXNUMBERTEST_H
#define COMPLEXNUMBERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>

#include <complex>

class ComplexNumberTest : public CppUnit::TestFixture  {
    //start of macros to create test suite
    CPPUNIT_TEST_SUITE( ComplexNumberTest ); //declaration of suite passing class name to macro
    //Suite is created and static suite() method is named after class name
    CPPUNIT_TEST( testEquality ); //declare each test case of the fixture
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST_SUITE_END();  //End of suite declaration
    //now a method with following signature created: static CppUnit::TestSuite *suite();
private:
    std::complex<double> *m_10_1, *m_1_1, *m_11_2;
public:
    void setUp();
    void tearDown();
    void testEquality();
    void testAddition();
};



#endif
