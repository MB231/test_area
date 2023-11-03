#include <complex>
#include <memory>

#include "cppunit/TestCaller.h"
#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TestSuite.h"

class ComplexNumberTest : public CppUnit::TestFixture {
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

    static CppUnit::Test *suite() {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("ComplexNumberTest");

        suiteOfTests->addTest(
                new CppUnit::TestCaller<ComplexNumberTest>("testEquality", &ComplexNumberTest::testEquality));

        suiteOfTests->addTest(
                new CppUnit::TestCaller<ComplexNumberTest>("testAddition", &ComplexNumberTest::testAddition));

        return suiteOfTests;
    }
};
