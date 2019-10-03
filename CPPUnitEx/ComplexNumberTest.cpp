#include "ComplexNumberTest.h"

//Below is registration with TestFactoryRegistry. In .cpp not .h file
CPPUNIT_TEST_SUITE_REGISTRATION( ComplexNumberTest );
//header file no longer needs to be included in main.cpp

void ComplexNumberTest::setUp()
{
    m_10_1 = new std::complex<double>( 10, 1 );
    m_1_1 = new std::complex<double>( 1, 1 );
    m_11_2 = new std::complex<double>( 11, 2 );
}

void ComplexNumberTest::tearDown() 
{
    delete m_10_1;
    delete m_1_1;
    delete m_11_2;
}

void ComplexNumberTest::testEquality()
{
    CPPUNIT_ASSERT( *m_10_1 == *m_10_1 );
    CPPUNIT_ASSERT( !(*m_10_1 == *m_11_2) );
}

void ComplexNumberTest::testAddition()
{
    CPPUNIT_ASSERT( *m_10_1 + *m_1_1 == *m_11_2 );
}
