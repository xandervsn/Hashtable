#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <typeinfo>
#include "node.h"

using namespace std;

int hashf(int, int);
int getI(int&);

int main(){
  int HASH_LENGTH = 122;
  Node** hashmap = new Node*[HASH_LENGTH];
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

	Node* newStudent = new Node(new Student((char*)first, last, id, gpa));
	hashmap[hashf(id, HASH_LENGTH)] = newStudent;
	cout << hashmap[hashf(id, HASH_LENGTH)]->getStudent()->gpa << endl;
	cout << hashmap[3] << endl;
      }else if(strcmp(input, "RAND") == 0){
	//gen 1st name
	ifstream firstFile;
	firstFile.open("firstname.txt");
	char arr[30][105];
	int i = 0;
	while(firstFile.getline(arr[i],100,' ')){
	  i++;
	}
	srand((unsigned) time(NULL));
	int random = rand() % 49;
	char* first = arr[random];

	//gen last name
	ifstream lastFile;
	lastFile.open("lastnames.txt");
	char arr2[30][105];
	i = 0;
	while(lastFile.getline(arr2[i],100,' ')){
	  i++;
	}
	random = rand() % 49;
	char* last = arr2[random];

	//gen gpa
	double randF = (double)rand();
	double gpa = fmod(randF, 4.99);
		
	int id = getI(ii);
	cout << "ID:" << id << endl;
	cout << "1" << endl;
	int pos = hashf(id, HASH_LENGTH);
	cout << "2" << endl;
	Node* newStudent = new Node(new Student((char*)first, last, id, gpa));
	cout << "3" << endl;
	cout << hashmap[3] << endl;
	//hashmap[hashf(id, HASH_LENGTH)] = newStudent;
	cout << "4" << endl;
      }
    }
  }  
  return 0;
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
