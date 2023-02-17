#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <typeinfo>
#include "node.h"

using namespace std;

int hashf(int, int);
int getI(int&);
void add(Node** hashmap, Node* newStudent, int);
void print(Node** hashmap, Node* student);

int main(){
  int HASH_LENGTH = 100;
  //Node* hashmap[HASH_LENGTH];
  Node** hashmap = new Node*[HASH_LENGTH];
  for(int i = 0; i < HASH_LENGTH; i++){
    hashmap[i] = NULL;
  }
  cout << hashmap[3] << endl;
  int ii = 0;
  
  while(true){
    cout << "Input command (ADD, DLT, QUIT, PRINT)" << endl;
    char input[10];
    cin >> input;

    if(strcmp(input, "ADD") == 0){
      cout << "Add by user input (INPUT) or randomization (RAND)?" << endl;
      cin >> input;
      if(strcmp(input, "INPUT") == 0){
	cout << "Input ID:" << endl;
	cin >> input;
	int id = (input[5]-'0') + (input[4]-'0')*10 + (input[3]-'0')*100 +
	  (input[2]-'0')*1000 + (input[1]-'0')*10000 + (input[0]-'0')*100000;
	
	cout << "Input First Name:" << endl;
	char first[35];
	cin >> first;
      
	cout << "Input Last Name:" << endl;
	char last[35];
	cin >> last;

	cout << "Input GPA:" << endl;
	float gpa = 0.00;
	cin >> gpa;

	int pos = hashf(id, HASH_LENGTH);
	Node* newStudent = new Node(new Student((char*)first, last, id, gpa));
	add(hashmap, newStudent, pos);
      }else if(strcmp(input, "RAND") == 0){
	//gen 1st name
	ifstream firstFile;
	firstFile.open("firstname.txt");
	char arr[30][55];
	int i = 0;
	while(firstFile.getline(arr[i],50,' ')){
	  i++;
	}
	srand((unsigned) time(NULL));
	int random = rand() % 49;
	char* first = arr[random];
	
	//gen last name
	ifstream lastFile;
	lastFile.open("lastnames.txt");
	i = 0;
	while(lastFile.getline(arr[i],50,' ')){
	  i++;
	}
	random = rand() % 49;
	char* last = arr[random];

	cout << first << " " << last << endl;
	
	//gen gpa
	double randF = (double)rand();
	double gpa = fmod(randF, 4.99);
		
	int id = getI(ii);
	int pos = hashf(id, HASH_LENGTH);
	Node* newStudent = new Node(new Student((char*)first, last, id, gpa));
	add(hashmap, newStudent, pos);
      }
    }else if(strcmp(input, "PRINT") == 0){
      cout << "Enter student ID:" << endl;
      int id = 0;
      cin >> id;
      int pos = hashf(id, HASH_LENGTH);
      print(hashmap, hashmap[pos]);
    }
  }  
  return 0;
}

void print(Node** hashmap, Node* current){
  Student* student = current->getStudent();
  cout << student->id << " " << student->first << " " << student->last << " " << student->gpa << endl;
   if(current->getNext() != NULL){
     print(hashmap, current->getNext());
   }
}

void add(Node** hashmap, Node* newStudent, int pos){
  newStudent->setNext(NULL);
  if(hashmap[pos] == NULL){
    hashmap[pos] = newStudent;
  }else{
    hashmap[pos]->setNext(newStudent);
  }
}

int hashf(int id, int HASH_LENGTH){
  return id % HASH_LENGTH;
}

int getI(int& i){
  i++;
  return i;
}

/*
int hashf(char* id, int HASH_LENGTH){
  //hashes input (with too much int division)
  return ((id[0] - '0') + (id[1] - '0') + (id[2] - '0') +
	  (id[3] - '0') + (id[4] - '0') + (id[5] - '0')) * (id[5] - '0') / (HASH_LENGTH/25);
}
*/
