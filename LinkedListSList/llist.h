//CS311 Yoshii
//INSTRUCTION:
//Llist class - header file template 

// =======================================================
// HW#: HW3P1 llist
// Your name: Bryan Miller
// Compiler:  g++ 
// File type: headher file  llist.h
//=======================================================

// alias el_t : element type definition
typedef int el_t;

//a list node is defined here as a struct Node for now
//Internal struct as a node
struct Node
{
  el_t Elem;   // elem is the element stored
  Node *Next;  // next is the pointer to the next node
};
//---------------------------------------------------------

class llist
{
//Make inaccessible to childeren client classes
 protected:
  Node *Front;       // pointer to the front node
  Node *Rear;        // pointer to the rear node
  int  Count;        // counter for the number of nodes

// untility function to move to a specified node position
void moveTo(int, Node*&);
  
 public:

  // Exception handling classes 
  class Underflow{};
  class OutOfRange{};  // thrown when the specified Node is out of range

  llist ();     // constructor to create a list object
  ~llist();     // destructor to destroy all nodes
  
  //Declaration of empty function, return true or false if of list empty status.
  bool isEmpty();
    
  //Declare display function, void return type. Display all elements
  void displayAll();

  //Add front function requires el_t data to be passed, void return type.
  //Add to front of list
  void addFront(el_t);
    
  //Add rear function requires el_t data to be passed, void return type.
  //Add to rear of list
  void addRear(el_t);

  //Delete front function requires el_t data to be passed, void return type.
  //Delete front of list.
  void deleteFront(el_t&);
    
  //Delete rear function requires el_t data to be passed, void return type.
  //Delete rear of list
  void deleteRear(el_t&);
    
  //Delete ith function requires el_t data to be passed, void return type.
  //Delete specified index
  void deleteIth(int, el_t&);  // calls moveTo

  //Insert Ith function requires el_t data to be passed, void return type.
  //Insert at specified index.  
  void insertIth(int, el_t);   // calls moveTo

  //Copy Constructor to allow pass by value and return by value of a llist
  llist(const llist&);
  
  //Overloading of = (returns a reference to a llist)
  llist& operator=(const llist&); 

};
