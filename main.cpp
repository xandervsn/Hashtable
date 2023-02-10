#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

int hash_func(char*);

int main(){
  int HASH_LENGTH = 122;
  Node* hashmap[HASH_LENGTH];
  cout << "Input command (ADD, DLT, QUIT, PRINT)" << endl;
  char input[10];
  cin >> input;

  if(strcmp(input, "ADD") == 0){
    cout << "Input Student ID:" << endl;
    char idIn[10];
    cin >> idIn;
    int id = (idIn[5]-'0') + (idIn[4]-'0')*10 + (idIn[3]-'0')*100 +
      (idIn[2]-'0')*1000 + (idIn[1]-'0')*10000 + (idIn[0]-'0')*100000;
    int pos = hash_func(idIn);
    cout << "Input First Name:" << endl;

    cout << "Input Last Name:" << endl;

    cout << "Input GPA:" << endl;
  }

  return 0;
}

int hash_func(char* id){
  return ((id[0] - '0') + (id[1] - '0') + (id[2] - '0') +
	   (id[3] - '0') + (id[4] - '0') + (id[5] - '0')) * (id[5] - '0') / 4;
}
