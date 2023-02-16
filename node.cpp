#include <iostream>
#include "node.h"

using namespace std;

Student::Student(char* first, char* last, int id, float gpa){
  strcpy(this->first, first);
  strcpy(this->last, last);
  this->id = id;
  this->gpa = gpa;
}

// Get next node
Node* Node::getNext() {
  return next;
}

// Get student from node 
Student* Node::getStudent() {
  return student;
}

// Set next node
void Node::setNext(Node* n) {
  next = n;
}

// Node constructor
Node::Node(Student* s) {
  student = s;
  next = nullptr;
}

// Node destructor
Node::~Node() {
  delete student; // Make sure we get rid of the student too 
}
