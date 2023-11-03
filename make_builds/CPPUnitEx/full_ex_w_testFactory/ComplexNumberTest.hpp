#ifndef COMPLEXNUMBERTEST_H
#define COMPLEXNUMBERTEST_H
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>

#include <complex>
#include <memory>
// now included
#include <cppunit/extensions/HelperMacros.h>
// No longer included #include "cppunit/TestFixture.h"

class ComplexNumberTest : public CppUnit::TestFixture {
    //start of macros to create test suite
    CPPUNIT_TEST_SUITE( ComplexNumberTest ); //declaration of suite passing class name to macro
    //Suite is created and static suite() method is named after class name
    CPPUNIT_TEST( testEquality ); //declare each test case of the fixture
    CPPUNIT_TEST( testAddition );
    CPPUNIT_TEST_SUITE_END();  //End of suite declaration
    //now a method with following signature created: static CppUnit::TestSuite *suite();
  private:
    // unique pointer chosen over smart pointer to keep control over object that needs to be
    // destroyed. We want the object destroyed at every setup. Shared pointer may be left
    // with a pointer somwhere preventing that object from being destroyed.
    std::unique_ptr<std::complex<double>> m_10_1;
    std::unique_ptr<std::complex<double>> m_1_1;
    std::unique_ptr<std::complex<double>> m_11_2;

  public:
    void setUp();
    void tearDown();
    void testEquality();
    void testAddition();

    /* This test Fixture no longer used with factory and helper macros
    static CppUnit::Test *suite() {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("ComplexNumberTest");

        suiteOfTests->addTest(
                new CppUnit::TestCaller<ComplexNumberTest>("testEquality", &ComplexNumberTest::testEquality));

        suiteOfTests->addTest(
                new CppUnit::TestCaller<ComplexNumberTest>("testAddition", &ComplexNumberTest::testAddition));

        return suiteOfTests;
    }
    */
};
#endif
