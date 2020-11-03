//CS311 Yoshii Linked List class

//INSTRUCTION:
//Must use the provided HW3P1_help.doc to create llist.cpp
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes

//EMACS HINT:
//  You can copy from a Word document to emacs (contrl-right click)
//  cntr-K cuts and cntr-Y pastes
//  Esc x replace-str does string replacements
//  Esc > goes to the end of the file; Esc < to the beginning
//  Tab on each line will indent perfectly for C++

// ====================================================
//HW#: HW3P1 llist
//Your name: Bryan Miller
//Complier:  g++
//File type: llist.cpp implementation file
//=====================================================

/*******************************************************
 * Algorithim: See detailed documenation above function header.
 
 * Goal:
 * Definitions of functions declared in header file.
 * Contains properties of basic functionalities of 
 * a linked list: (delete/add front), (delete/ add rear),
 * (delete/add specified position), (empty function),
 * (display function), (pointer mover utility function),
 * (copy constructor and assignmnet overload functions).
********************************************************/
using namespace std;
#include <iostream>
#include"llist.h" 

//Constructor initalizes llist data members.
//Front points to the first element of the list, rear points the last element of the list.
//count is used to keep track of the total amount of nodes in the list.
llist::llist(){ 
  cout << "... in llist constructor..." << endl; 
  Front = NULL; Rear = NULL; Count = 0;
}
//Inform the list desructor is being called, while the list isnt empty delete every node. 
//Use deleteIth as a utility function to delete each node until the list is empty.
llist::~llist(){
  cout << ".... in llist destructor..." << endl;
  int x = 0;
  while(!isEmpty()){
    deleteIth(Count, x);
  }
}

//PURPOSE: Function to check if list is empty.
//PARAMETER: No parameters.
//Check all three data members (front, rear count) to precisely identify if list is empty.
//If so then return true, otherwise return false.
bool llist::isEmpty(){
if(Front == NULL && Rear == NULL){
    if(Count == 0){
      return true;
    }
  }
  return false;
}

// PURPOSE: Display all elements in the list.
// PARAMETER: No parameters.
//Display each node in the list until null case is reached.
//Temp is a temporary node pointing to the fist element in the list.
void llist::displayAll(){
  if(isEmpty()){
    cout<<"[ ]"<<endl;
  }else{
    Node *temp = Front;
    cout<<"[ ";
    while(temp != NULL){
      cout<<temp->Elem<<" ";
      temp = temp->Next;
    }
    cout<<"]"<<endl;
  } 
}  
  
// PURPOSE: Add node to the back of the list.
// PARAMETER: el_t type data you want to pass in for the associated node.
//if the list is empty just call addFront, otherwsie make the last nodes next node equal to the new node, make the new node now the
//new rear, make the next position equal to null.
//newNode is the node being added
void llist::addRear(el_t NewNum) {
  if(isEmpty()){
    addFront(NewNum);
  }else{
    Node *newNode = new Node;
    newNode->Elem = NewNum;
    Rear->Next = newNode;
    Rear = Rear->Next;
    Rear->Next = NULL;
    Count++;
  }
 }
  
// PURPOSE: Add node to the front of the list
// PARAMETER: el_t type data you want to pass in for the associated node.
//If the list is empty set the front equal to the new node, the rear equal to the front, and rears next element equal to null.
//Otherwise create the connection by making the new nodes next equal to front, and now let the new node be front.
//newNode is the node being added
void llist::addFront(el_t NewNum){
  Node *newNode = new Node;
  newNode->Elem = NewNum;
  if(isEmpty()){
    Front = newNode;
    Rear = Front;
    Rear->Next = NULL;
  }else{
    newNode->Next = Front;
    Front = newNode;
  }
  Count++;
}

// PURPOSE: Delete the front node
// PARAMETER: el_t type data you want to pass in for the associated node passed by reference, 
//the lvalue type passed will contain the deleted nodes data.
//If the list is empty delete throw underflow error, otherwise if the count is 1 the list will be going back to size 0,
//so rear and front data members will need to be set to null for the next value to be added properly.
//Final case the list isnt empty or size 1, so set the front equal to the next position.
//oldnum will be assigned the deleted elements data
void llist::deleteFront(el_t& OldNum) { 
  if(isEmpty()){
    throw Underflow();
  }else if(Count == 1){
    OldNum = Front->Elem;
    Rear = NULL;
    Front = NULL;
    Count--;
  }else{
    OldNum = Front->Elem;
    Front = Front->Next;
    Count--;
  }
} 

// PURPOSE: Delete the last node in the list
// PARAMETER: el_t type data you want to pass in for the associated node passed by reference, 
//the lvalue type passed will contain the deleted nodes data.
//If the list is empty delete throw underflow error, otherwise if the count is 1 the list will be going back to size 0,
//so rear and front data members will need to be set to null for the next value to be added properly.
//Final case the list isnt empty or size 1, so call utility pointer move function to node just 
//before the end, make the rear that new node, make the rears next null.
//oldnum will be assigned the deleted elements data
void llist::deleteRear(el_t& OldNum){
  if(isEmpty()){
    throw Underflow();
  }else if(Count == 1){
    OldNum = Rear->Elem;
    Rear = NULL;
    Front = NULL;
    Count--;
  }else{
    Node *temp = Front;
    moveTo((Count - 1), temp);
    OldNum = temp->Next->Elem;
    Rear = temp;
    Rear->Next = NULL;
    Count--;
  }
}
// PURPOSE: Utility Function to move a local pointer to the Jth node
// PARAMETER: Return index, node pointer passed by reference.
//If the index indicated is less than the size of the list or less than 1, throw out of range error.
//Otherwsie check if the position indicated is equal to the size of the list or 1, if so return the front or the rear.
//Finally if not the first two cases  scan the list until the Jth position is reached.
//temp2 traverses the list until the respective position is found, when the position is found, assign it to temp.
void llist::moveTo(int J, Node*& temp){ 
  Node *temp2 = Front;
  if(J < 1 || J > Count){ throw OutOfRange();}
  if(J == 1){ temp = Front; } 
  else if (J == Count){ temp = Rear;}
  else{
    for(int i = 1; i < J; i++){
      temp2 = temp2->Next;
    }
    temp = temp2;
  }
}

// PURPOSE: Delete a node that isn't the front or rear of the list
// PARAMETER: Index to delete and el_t type data you want to pass in for the associated node passed by reference, 
//the lvalue type passed will contain the deleted nodes data.
//Again check check cases of first and last index, if the count is out of range the range error.
//Otherwise call move to function to move the pointer to the position right before the position user wants to delete.
//Set the passed in variables data to the pointers next's data. Finally set the pointers next equal to the next nodes 
//next to break the connection.
//temp is a parameter called in utility function that is used to traverse list until position is found.
//oldnum is assigned the value of the deleted element.
void llist::deleteIth(int I, el_t& OldNum){
   Node *temp = Front;
   if(I == 1){ deleteFront(OldNum);}
   else if(I == Count){ deleteRear(OldNum);}
   else if(I < 1 || I > Count){ throw OutOfRange();}
   else{
     moveTo((I - 1), temp);
     OldNum = temp->Next->Elem;
     temp->Next = temp->Next->Next;
     Count--;
   }
} 

// PURPOSE: Insert into a position that isn't the front or rear of the list.
// PARAMETER: Index to insert
//Check if the user wants to enter an invalid position, if so throw out of range. Adding to the size of the list + 1 is okay.
//Otherwise if the position is the front or rear plus 1 perform the following actions.
//Finally if the index is not the front or the rear + 1, you will need two pointers: one for pointing to the index before the position 
//desired, and the another pointing at the index. The (I - 1)th position will point to the new node and the new node will point to the Ith 
//position.
//new node is the new node being added to the list, temp will be pointing at the preious element and otherP will be 
//pointing at the node in the current position desired. With these three pointers we can complete a successful addition
//to the list.
void llist::insertIth(int I, el_t newNum){
  if(I < 1 || I > Count + 1){ throw OutOfRange();}
  else{
    if(I == 1){
      addFront(newNum);
    }else if(I == Count + 1){ addRear(newNum);}
    else{
      Node *newN = new Node;
      newN->Elem = newNum;
      Node *temp = Front;
      Node *otherP = Front;
      moveTo((I-1), temp);
      moveTo(I, otherP);
      temp->Next = newN;
      newN->Next = otherP;
      Count++;
    }
  }
} 

// PURPOSE: User defined copy constructor
// PARAMETER: Original linked list passed by reference
//Initialize the calling lists data members, have another pointer pointing to the list to be copied front.
//Scan through the to be copied list until the end is reached, adding each nodes data to the new lists rear.
//Performs a deep copy, which is passed by value. The memory locations are different.
//When passing to a function and altering the list in that function, upon returning back to the caller the list will be unchanged.
//this references the calling object, P references the list being copied.
llist::llist(const llist& Original){
  //  this->'s data members need to be initialized here first
  this->Front = NULL; this->Rear = NULL; this->Count = 0;
  Node* P;  // local pointer for Original
  P = Original.Front;
  while (P != NULL){  //  this-> object has to be built up by allocating new cells
    // a loop which repeats until you reach the end of OtherOne. 
    this->addRear(P->Elem);    //P’s element is added to this->
    P = P->Next;                         // Go to the next node  
  }
} 
// PURPOSE: Assignment overload operator function.
// PARAMETER: Calling lists, list to be assigned to, passed by reference.
// Check to see if the calling list is equal to the other list, if so just return the list.
// Otherwise scan throught the list deleting each node until the list is empty.
// Perform the same steps as above. Return calling lists pointer.
//this references the calling object, P references the list being copied.
llist& llist::operator=(const llist& OtherOne){
  el_t x;
  if (&OtherOne != this){
    while (!this->isEmpty()){
      this->deleteRear(x);
    }
    Node* P;  // local pointer for OtherOne
    P = OtherOne.Front;
    while (P != NULL){  
      // a loop which repeats until you reach the end of OtherOne. 
      this->addRear(P->Elem);    //P’s element is added to this->
      P = P->Next;                         // Go to the next node in OtherOne   
    } 
  }            
  return *this;    // return the result unconditionally.  Note that the result is returned by reference.
} 
 

