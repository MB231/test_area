#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
//fixture header file no longer included


int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner; //create runner object
  //below retrieves instance of TestFactoryRegistry
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  //obtain and add new TestSuite created by the TestFactoryRegistry that contains
  //all the test suites registered useing CPPUNIT_TEST_SUITE_REGISTRATION macro
  runner.addTest( registry.makeTest() ); //run tests
  //run() returns a bool value that can be returned to calling function to main
  //allowing automated return of results rather than "return 0" which only says
  //main() was successful
  bool wasSuccessful = runner.run( "", false );
  return !wasSuccessful;
}
