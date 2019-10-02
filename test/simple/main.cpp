#include <cppunit/ui/text/TestRunner.h>
#include "ComplexNumberTest.h"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( ComplexNumberTest::suite() );
  runner.run();
  return 0;
}
