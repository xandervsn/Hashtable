/*Xander Siruno-Nebel
  C++/Data Structures
  Galbraith
  Feb 17, 2022

  Hashtable: implementation of a hashtable (aka map aka hashmap) in C++
 */


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <typeinfo>
#include "node.h"

using namespace std;

int hashf(int, int);
int getI(int&);
void add(Node** hashmap, Node* newStudent, int, int&);
void print(Node** hashmap, Node* student, int, int);
void dlt(Node** hashmap, Node* current, int, int);

int main(){
  int HASH_LENGTH = 100;
  //Node* hashmap[HASH_LENGTH];
  Node** hashmap = new Node*[HASH_LENGTH];
  for(int i = 0; i < HASH_LENGTH; i++){
    hashmap[i] = NULL;
  }
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
        int id = 0;
        cin >> id;
        //int id = (input[5]-'0') + (input[4]-'0')*10 + (input[3]-'0')*100 +
        //  (input[2]-'0')*1000 + (input[1]-'0')*10000 + (input[0]-'0')*100000;

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
        //creates new student
        Node* newStudent = new Node(new Student((char*)first, last, id, gpa));
        add(hashmap, newStudent, pos, HASH_LENGTH);
      }else if(strcmp(input, "RAND") == 0){
        //gen 1st name
        ifstream firstFile; //file reader
        firstFile.open("firstname.txt");
        char arr[30][55];
        int i = 0;
        while(firstFile.getline(arr[i],50,' ')){
          i++;
        }
        //pick random name from created char* array above
        srand((unsigned) time(NULL));
        int random = rand() % 49;
        char* first = arr[random];

        //gen last name
        //same as above
        ifstream lastFile;
        lastFile.open("lastnames.txt");
        i = 0;
        while(lastFile.getline(arr[i],50,' ')){
          i++;
        }
        random = rand() % 49;
        char* last = arr[random];

        //gen gpa
        double randF = (double)rand();
        double gpa = fmod(randF, 4.99);

        int id = getI(ii);
        int pos = hashf(id, HASH_LENGTH);
        Node* newStudent = new Node(new Student((char*)first, last, id, gpa));
        add(hashmap, newStudent, pos, HASH_LENGTH);
        print(hashmap, hashmap[pos], 1, id);
      }
    }else if(strcmp(input, "PRINT") == 0){
      cout << "Enter student ID:" << endl;
      int id = 0;
      cin >> id;
      if(hashmap[hashf(id, HASH_LENGTH)] != NULL){
        //if there's a student with that id
        int pos = hashf(id, HASH_LENGTH);
        print(hashmap, hashmap[pos], 1, id);
      }else{
        //if not
        cout << "No such student!" << endl;
      }
    }else if(strcmp(input, "QUIT") == 0){
      break;
    }else if(strcmp(input, "DLT") == 0){
      cout << "Input ID:" << endl;
      int id = 0;
      cin >> id;
      int pos = hashf(id, HASH_LENGTH);
      if(hashmap[pos]->getNext() != NULL){
        //if there's >1 things in the bucket
        //so that print() isn't extremely annoying:
        cout << "There may be more than 1 students with that ID! Please select which student you'd like to delete ('1', '2', or '3')" << endl;
        print(hashmap, hashmap[pos], 1, id);
        int toDlt = 0;
        cin >> toDlt;
        dlt(hashmap, hashmap[pos], toDlt, pos);
      }else{
        //if there's only 1 thing in the bucket
        hashmap[pos] = NULL;
        delete hashmap[pos];
      }
    }
  }
  return 0;
}

void add(Node** hashmap, Node* newStudent, int pos, int& HASH_LENGTH){
  //if statements basically go through ever possible bucket entry combination & edit linked list if needed
  newStudent->setNext(NULL);
  if(hashmap[pos] == NULL){
    hashmap[pos] = newStudent;
  }else if(hashmap[pos]->getNext() == NULL){
    hashmap[pos]->setNext(newStudent);
    newStudent->setNext(NULL);
  }else if(hashmap[pos]->getNext()->getNext() == NULL){
    hashmap[pos]->getNext()->setNext(newStudent);
    newStudent->setNext(NULL);
  }else{
    //if the bucket already has 3 entries
    cout << "REHASH" << endl;

    //makes a bunch of temp hashmap things, makes a new hashmap w double the size
    int OG_LENGTH = HASH_LENGTH;
    HASH_LENGTH = HASH_LENGTH*2;
    Node** newmap = new Node*[HASH_LENGTH];
    for(int i = 0; i < HASH_LENGTH; i++){
      newmap[i] = NULL;
    }

    for(int i = 0; i < OG_LENGTH; i++){
      //goes through og array and reassigns every item
      bool two = false;
      bool three = false;
      //again, if statements go through ever possible iteration of a bucket
      if(hashmap[i] != NULL){
        cout << hashmap[i]->getNext() << endl;
        cout << "1" << endl;
        int id = hashmap[i]->getStudent()->id;
        cout << "2" << endl;
        int pos2 = hashf(id, HASH_LENGTH);
        cout << "3" << endl;
        Node* newStudent = hashmap[i];
        cout << "4";
        add(newmap, newStudent, pos2, HASH_LENGTH);
        cout << newmap[1]->getStudent()->first << endl;
        cout << "5" << endl;

        Node* next = hashmap[i]->getNext();
        cout << "6: " << next << endl;
        if(next != NULL){
          cout << "2" << endl;
          two = true;
          id = next->getStudent()->id;
          int pos2 = hashf(id, HASH_LENGTH);
          Node* newStudent = hashmap[i];
          newStudent->setNext(NULL);
          add(newmap, newStudent, pos2, HASH_LENGTH);
        }

        if(next->getNext() != NULL){
          cout << "3" << endl;
          three = true;
          id = next->getNext()->getStudent()->id;
          int pos2 = hashf(id, HASH_LENGTH);
          Node* newStudent = hashmap[i];
          newStudent->setNext(NULL);
          add(newmap, newStudent, pos2, HASH_LENGTH);
        }
      }
      cout << "7" << endl;
    }
    cout << "8" << endl;
    hashmap = newmap;
    cout << "9" << endl;
  }
}


void dlt(Node** hashmap, Node* current, int num, int pos){
  //if the bucket has 1/2/3 items, does normal linked list node deletion stuff
  if(num == 1){
    Node* next = current->getNext();
    delete current;
    hashmap[pos] = next;
  }else if(num == 2){
    Node* toDelete = current->getNext();
    if(toDelete->getNext() != NULL){
      current->setNext(toDelete->getNext());
    }
    delete toDelete;
  }else if(num == 3){
    Node* next = current->getNext();
    Node* toDelete = next->getNext();
    next->setNext(NULL);
    delete toDelete;
  }
}

void print(Node** hashmap, Node* current, int i, int id){
  Student* student = current->getStudent();
  //prints entirety of bucket so that i don't have to account for errors resulting from 2 of the same ID
  cout << i << ":";
  if(student->id == id){
    cout << student->id << " " << student->first << " " << student->last << " " << student->gpa << endl;
   }else{
    cout << "N/A" << endl;
  }
    if(current->getNext() != NULL){
      i++;
      print(hashmap, current->getNext(), i, id);
   }
}

int hashf(int id, int HASH_LENGTH){
  //modulus hash function most obscure
  return id % HASH_LENGTH;
}

int getI(int& i){
  //needed for incrementing randomization
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
