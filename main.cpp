#include <iostream>
#include <fstream>
#include <cstring>
#include "node.h"

using namespace std;

int hash_func(char*, int);

int main(){
  int HASH_LENGTH = 122;
  Node* hashmap[HASH_LENGTH];
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
      int pos = hash_func(input, HASH_LENGTH);

      cout << "Input First Name:" << endl;
      cin >> input;
      
      cout << "Input Last Name:" << endl;
      cin >> input;
      
      cout << "Input GPA:" << endl;
      cin >> input;
    }else if(strcmp(input, "RAND") == 0){
      ifstream firstFile;
      firstFile.open("firstname.txt");
      char arr[30][105];
      int i = 0;
      while(firstFile.getline(arr[i],100,' ')){
	cout << arr[i] << endl;
	cout << i << endl;
	i++;
      }
      srand((unsigned) time(NULL));
      int random = rand() % 49;
      cout << arr[random] << endl;

      ifstream lastFile;
      lastFile.open("lastnames.txt");
      char arr2[30][105];
      i = 0;
      while(lastFile.getline(arr2[i],100,' ')){
        cout << arr2[i] << endl;
        cout << i << endl;
        i++;
      }
      random = rand() % 49;
      cout << arr2[random] << endl;

    }
  }
  
  return 0;
}

int hash_func(char* id, int HASH_LENGTH){
  //hashes input (with too much int division)
  return ((id[0] - '0') + (id[1] - '0') + (id[2] - '0') +
	  (id[3] - '0') + (id[4] - '0') + (id[5] - '0')) * (id[5] - '0') / (HASH_LENGTH/25);
}
