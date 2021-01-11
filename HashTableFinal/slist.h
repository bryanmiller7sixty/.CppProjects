// CS311 Yoshii
// HW3P2 Instruction: Inherit everything publicly from llist
//=================================================
// HW#: HW3P2 slist
// Name: Bryan Miller
// File: slist.h
//=================================================
#include "llist.h"
/*******************************************************************************************
Algorithim:
Note here we need to include the llist header file.
Make access public here to inherit everything publicly from llist
but change class variables access specifier in llist to protected.
********************************************************************************************/
class slist : public llist
{
 public:
  //slist contructor and destructor
  //I created the destructor to see the hierarchy of how the deletion of objects.
  slist();   
  ~slist();

  el_t search2(el_t);
    // search through the list to see if any node contains the key.
    // If so, return its position (>=1). Otherwise, return 0.
    
  void replace(el_t,  int);
    // go to the Ith node (if I is between 1 and Count) and 
    // replace the element there with the new element. 
    // If I was an illegal value, throw OutOfRange 
    
  bool operator==(const slist&);
    // checks to see of the two lists look the 
    
  int search(el_t); //search method previously used in the first version of the slist

  el_t returnIth(int stopNum, int count); //Returns the ith element in the list
};
