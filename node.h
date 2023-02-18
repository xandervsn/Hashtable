#include <iostream>
#include <cstring>

class Student{
 public:
  char first[35];
  char last[35];
  int id;
  float gpa;
  Student(char*, char*, int, float);
};

class Node{
 private:
  Student* student;
  Node* next;
 public:
  Node* getNext();
  Student* getStudent();
  void setNext(Node*);
  Node(Student*);
  ~Node();
};

struct node{
  char first[100];
  char last[100];
  float gpa;
  int id;
  node* next = NULL;
};
