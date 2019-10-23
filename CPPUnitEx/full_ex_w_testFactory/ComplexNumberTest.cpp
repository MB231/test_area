#include "ComplexNumberTest.hpp"

//Below is registration with TestFactoryRegistry. In .cpp not .h file
CPPUNIT_TEST_SUITE_REGISTRATION( ComplexNumberTest );
// header file no longer needs to be included in main.cpp

void ComplexNumberTest::setUp() {
    // unique pointer reset will delete the object it was pointed to and assign the new object
    m_10_1.reset(new std::complex<double>(10, 1));
    m_1_1.reset(new std::complex<double>(1, 1));
    m_11_2.reset(new std::complex<double>(11, 2));
}

void ComplexNumberTest::tearDown() {
    // no need to delete the unique pointers
}

void ComplexNumberTest::testEquality() {
    CPPUNIT_ASSERT(*m_10_1 == *m_10_1);
    CPPUNIT_ASSERT(!(*m_10_1 == *m_11_2));
}

void ComplexNumberTest::testAddition() {
    CPPUNIT_ASSERT(*m_10_1 + *m_1_1 == *m_11_2);
}

