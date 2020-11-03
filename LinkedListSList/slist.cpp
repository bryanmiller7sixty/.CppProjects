// CS311 Yoshii Complete all functions with their comments

// ====================================================
//HW#: HW3P1 slist  inheriting from llist
//Your name: Bryan Miller
//Complier:  g++
//File type: slist.cpp implementation file
//=====================================================
/************************************************************************************************************
 * Algorithim:
 * Demonstrate inheriatnce and access to protected class variables to the child class
 * of llist: slist. The slist objects will have access to all of the the parents functions and class variables,
 * while the client of slist will only have access to the functions. 
 * Three additional methods are implemented:
 * SEARCH : searches list for an element and returns the position found, if found.
 * REPLACE : replaces the element in list specified by user, if that position exists.
 * == OVERLOAD : overload to equals operator to check if two lists are the same.
 * ************************************************************************************************************/
using namespace std;
#include<iostream>
#include"slist.h" 

//Slist constructor will get called last while the destructor will get called first.
slist::slist()
{ cout << "***In slist constructor***" << endl;}
slist::~slist(){
  cout<<"***In slist destructor, this one will get called first***"<<endl;
}
//Search function has paramaters of el_t type.
//The key corresponds with the element to be searched.
//Create temp node that points to the front of the list, set initial account to 1.
//While what temp is pointing to isn't null, traverse the list until until the key is found.
//If the key isn't found the loop will break and a statement not found will be printed following returning the int 0.
int slist::search(el_t key){
  Node *temp = Front;
  int count = 1;
  while(temp != NULL){
    if(temp->Elem == key){
      return count;
    }else{
      temp = temp->Next;
      count++;
    }
  }
  cout<<key<<" not found."<<endl;
  return 0;
}
//Replace function has parameters of el_t type element and int position.
//Declare temp node, then check condition if the position is greater than the callers count or position is less than 1.
//In both cases throw out of range
//Otherwise call utility function moveTo to move the node to the corresponding position requested.
//Finally set temps element to to the element passed in.
void slist::replace(el_t element, int pos){
  Node *temp;
  if(pos > this->Count || pos < 1){
    throw OutOfRange();
  }else{
    moveTo(pos, temp);
    temp->Elem = element;
  }
}
//Overload the == operator
//Parameters consist of const slist type reference to another list
//First check if the counts are not equal, which will clearly tell if the list are not the same, if so return false.
//Otherwise set two temporary nodes to the front of the each list.
//For the second condition you can choose to set the null condition to either list since they are both the same size.
//If the element both of the nodes are looking at are not the same return false, otherwise keep traversing the list.
//If it gets to the end of the list and breaks the loop then it means the lists are the same so return true.
bool slist::operator==(const slist& OtherOne)
{
  if(OtherOne.Count != this->Count){
    return false;
  }else{
    Node *callP = this->Front;
    Node *otherP = OtherOne.Front;
    while(callP != NULL){
      if(callP->Elem != otherP->Elem){
        return false;
      }else{
        callP = callP->Next;
        otherP = otherP->Next;
      }
    }
  }
  return true;
}
