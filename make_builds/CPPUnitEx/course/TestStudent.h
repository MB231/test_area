#ifndef TestStudent_h
#define TestStudent_h

#include <iostream>
#include <string>

// Note 1
#include "cppunit/TestCase.h"
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"
#include "cppunit/TestRunner.h"

#include "Student.h"

class StudentTestCase : public TestCase { // Note 2 
public:
  // constructor - Note 3
  StudentTestCase(std::string name) : TestCase(name) {}

  // method to test the constructor
  void testConstructor();

  // method to test the assigning and retrieval of grades
  void testAssignAndRetrieveGrades();

  // method to create a suite of tests
  static Test *suite ();
};
#endif
