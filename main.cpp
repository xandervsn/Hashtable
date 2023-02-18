/*Xander Siruno-Nebel
  C++/Data Structures
  Galbraith
  Feb 17, 2023

  Hashtable: implementation of a hashtable (aka hashmap aka map) in C++
*/

#include <iostream>
#include <cstring>
#include "node.h"
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;
node** add(node**, int& currentID, int&);
node** inputAdd(node** hashtable, int& currentID, int&HASH_LENGTH);
void print(node** hashtable, int);
void dlt(node** hashtable, int);
void empty(node* hashtable[], int HASH_LENGTH);
node** rehash(node** hashtable, node** newmap, int&, int);

int main(){
  srand(time(0));
  int HASH_LENGTH = 100;
  node** hashtable = new node*[100]; //init
  char input[7];
  int currentID = 0; //globalish var needed for incrementation
  empty(hashtable, HASH_LENGTH); //sets all hashtable values as null
  while(true){
    cout << "Type a valid command(ADD, PRINT, DLT, QUIT)" << endl;
    cin >> input;
    if(strcmp(input,"ADD") == 0){
      cout << "Add by user input (INPUT) or randomization (RAND)?" << endl;
      cin >> input;
      if(strcmp(input,"RAND") == 0){
        hashtable = add(hashtable, currentID, HASH_LENGTH);
      }else if(strcmp(input,"INPUT") == 0){
        hashtable = inputAdd(hashtable, currentID, HASH_LENGTH);
      }
    }else if(strcmp(input,"PRINT") == 0){
      print(hashtable, HASH_LENGTH);
    }else if(strcmp(input,"DLT") == 0){
      dlt(hashtable, HASH_LENGTH);
    }else if(strcmp(input,"QUIT") == 0){
      break;
    }
  }
  return 0;
}

node** add(node** hashtable, int& currentID, int& HASH_LENGTH){ //adds random to array
  int students;
  cout << "Input number of students to add:" << endl;
  cin >> students;
  for(int i = 0; i < students; i++){
    char input[100];
    char first[100];
    char last[100];
    fstream ffile("firstname.txt");
    fstream lfile("lastnames.txt");
    int count;
    int num = (rand() % 20) + 1;
    int num2 = (rand() % 20) + 1;
    node* newPoint = new node();
    count = 1;
    //1st name gen
    while (ffile.getline(input,100, '\n')) {
      if (count == num) {
        strcpy(first,input);
        count++;
      }
      count++;
    }
    ffile.close();
    count = 1;
    //last name gen
    while (lfile.getline(input,100, '\n')) {
      if (count == num2) {
        strcpy(last, input);
        count++;
      }
      count++;
    }
    lfile.close();
    //gpa gen
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    r *= 23;
    while(r > 4){
      r -= 4;
      while(r < 2){
        r += 1;
      }
    }

    strcpy(newPoint->first, first);
    strcpy(newPoint->last, last);
    newPoint->id = currentID;
    newPoint->gpa = r;
    //if statements basically go through every permutation of bucket fillability
    if(hashtable[(currentID)%HASH_LENGTH] == NULL){ //1 in bucket
      hashtable[(currentID%HASH_LENGTH)] = newPoint;
    }else{
      if(hashtable[(currentID)%HASH_LENGTH]->next == NULL){ //2 in bucket
        hashtable[currentID%HASH_LENGTH]->next = newPoint;
      }else{
        if(hashtable[(currentID)%HASH_LENGTH]->next->next == NULL){ //3 in bucket
          hashtable[currentID%HASH_LENGTH]->next->next = newPoint;
        }else{ //>3 in bucket (REHASH)
          cout << "REHASH" << endl;
          node** newmap = new node*[HASH_LENGTH*2];
          empty(newmap, HASH_LENGTH*2);
          hashtable = rehash(hashtable, newmap, HASH_LENGTH, currentID);
          hashtable[currentID%HASH_LENGTH]->next = newPoint;
        }
      }
    }
    currentID++;
  }
  return hashtable;
}

node** rehash(node** hashtable, node** newmap, int& HASH_LENGTH, int currentID){
  //makes a temp map 2x HASH_LENGTH, assigns all things in og map to temp map
  int oldHASH_LENGTH = HASH_LENGTH;
  HASH_LENGTH = HASH_LENGTH*2;
  for(int i = 0; i < currentID; i++){
    //if statements for 3 different possible node placements
    if(i < oldHASH_LENGTH){
      newmap[(i%HASH_LENGTH)] = hashtable[(i)%oldHASH_LENGTH];

    }else if(i < oldHASH_LENGTH*2){
      newmap[(i%HASH_LENGTH)] = hashtable[(i)%oldHASH_LENGTH]->next;
    }else{
      newmap[i%HASH_LENGTH]->next = hashtable[(i)%oldHASH_LENGTH]->next->next;
    }
  }
  for(int i = HASH_LENGTH/2; i < HASH_LENGTH; i++){
    newmap[(i%HASH_LENGTH)]->next = NULL;
  }
  return newmap;
}

void print(node** hashtable, int HASH_LENGTH){
  int i;
  node* current;
  cout << "Input student ID:" << endl;
  cin >> i;
  cin.clear();
  //rehashes/unhashes/whatever
  if(hashtable[i%HASH_LENGTH] != NULL && hashtable[i%HASH_LENGTH]->id == i){
    current = hashtable[i%HASH_LENGTH];
  }else if(hashtable[i%HASH_LENGTH]!= NULL && hashtable[i%HASH_LENGTH]->next != NULL && hashtable[i%HASH_LENGTH]->next->id == i){
    current = hashtable[i%HASH_LENGTH]->next;
  }else if(hashtable[i%HASH_LENGTH]!= NULL && hashtable[i%HASH_LENGTH]->next != NULL && hashtable[i%HASH_LENGTH]->next->next != NULL && hashtable[i%HASH_LENGTH]->next->next->id == i){
    current = hashtable[i%HASH_LENGTH]->next->next;
  }else{
    cout << "No such student!" << endl;
    return;
  }
  cout << current->first << " " << current->last << " GPA: " <<  fixed << setprecision(2) << current->gpa << " ID: " << current->id << endl;
}


void dlt(node** hashtable, int HASH_LENGTH){
  int i;
  cout << "Input student ID:" << endl;
  cin >> i;
  cin.clear();
  //finds student
  if(hashtable[i%HASH_LENGTH]->id == i){
    hashtable[i%HASH_LENGTH] = hashtable[i%HASH_LENGTH]->next;
  }else if(hashtable[i%HASH_LENGTH]->next->id == i){
    hashtable[i%HASH_LENGTH]->next = hashtable[i%HASH_LENGTH]->next->next;
  }else if(hashtable[i%HASH_LENGTH]->next->next->id == i){
    hashtable[i%HASH_LENGTH]->next->next = NULL;
  }
  return;
}

void empty(node** hashtable, int HASH_LENGTH){
  for(int i = 0; i < HASH_LENGTH; i++){
    hashtable[i] = NULL;
  }
}

node** inputAdd(node** hashtable, int&currentID, int& HASH_LENGTH){
  char input[100];
  char first[100];
  char last[100];
  float gpa;
  node* newPoint = new node();
  cout << "Input first name:" << endl;
  cin >> first;
  cin.clear();
  cout << "Input last name:" << endl;
  cin >> last;
  cin.clear();
  cout << "Input GPA: " << endl;
  cin >> gpa;
  cin.clear();
  strcpy(newPoint->first, first);
  strcpy(newPoint->last, last);
  newPoint->id = currentID;
  newPoint->gpa = gpa;
  //finds right place for student
  if(hashtable[(currentID)%HASH_LENGTH] == NULL){ //same thing as real add, go read comments there
    hashtable[(currentID%HASH_LENGTH)] = newPoint;
  }else{
    if(hashtable[(currentID)%HASH_LENGTH]->next == NULL){
      hashtable[currentID%HASH_LENGTH]->next = newPoint;
    }else{
      if(hashtable[(currentID)%HASH_LENGTH]->next->next == NULL){
        hashtable[currentID%HASH_LENGTH]->next->next = newPoint;
      }else{
        node** newmap = new node*[HASH_LENGTH*2];
        empty(newmap, HASH_LENGTH*2);
        hashtable = rehash(hashtable, newmap, HASH_LENGTH, currentID);
        hashtable[currentID%HASH_LENGTH]->next = newPoint;
      }
    }
  }
  currentID++;
  return hashtable;
}
