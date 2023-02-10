#include <iostream>
#include "node.h"

using namespace std;

Student::Student(char* first, char* last, int id, float gpa){
  strcpy(this->first, first);
  strcpy(this->last, last);
  this->id = id;
  this->gpa = gpa;
}


