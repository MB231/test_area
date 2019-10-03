#include <complex>
#include "cppunit/TestFixture.h"
#include "cppunit/TestCase.h"
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"


class ComplexNumberTest : public CppUnit::TestFixture  {
private:
    std::complex<double> *m_10_1, *m_1_1, *m_11_2;
public:
  void setUp()
  {
    m_10_1 = new std::complex<double>( 10, 1 );
    m_1_1 = new std::complex<double>( 1, 1 );
    m_11_2 = new std::complex<double>( 11, 2 );
  }

  void tearDown() 
  {
    delete m_10_1;
    delete m_1_1;
    delete m_11_2;
  }

  void testEquality()
  {
    CPPUNIT_ASSERT( *m_10_1 == *m_10_1 );
    CPPUNIT_ASSERT( !(*m_10_1 == *m_11_2) );
  }

  void testAddition()
  {
    CPPUNIT_ASSERT( *m_10_1 + *m_1_1 == *m_11_2 );
  }
    static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ComplexNumberTest" );
    suiteOfTests->addTest( new CppUnit::TestCaller<ComplexNumberTest>( 
                                   "testEquality", 
                                   &ComplexNumberTest::testEquality ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<ComplexNumberTest>(
                                   "testAddition",
                                   &ComplexNumberTest::testAddition ) );
    return suiteOfTests;
  }
};
