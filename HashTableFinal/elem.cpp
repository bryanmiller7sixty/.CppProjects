// CS311 Yoshii - el_t for HW8 Hash Table
// Element type of a list node is defined here
// el_t can be changed by the client to fit its needs
//----------------------------------------------------

#include "elem.h"
/*
Class goal: Create a class to have it's instances be used directly as elements in a hash table.
The members can be changed based on its application, and the members of the slist, and llist class.
Which are used for chaining in the hash table, also accept this class type. 
*/
// blank element
el_t::el_t()
{
  key = -1;  // cannot be 0 because 0 is a valid key
  name = "";
  stockPrice = 0.0;
  category = "";
}
// initializing constructor to create an el_t object 
el_t::el_t(int akey, string aname, double price, string cat)  //new arguments are the key, stock symbol name, price of the stock, and the stock category
{
  key = akey;
  name = aname;
  stockPrice = price;
  category = cat;
}
int el_t::getkey()
{
  return key;
}
void el_t::setkey(int akey)
{
  key = akey;
} 
string el_t::returnName(){
  return name;
}

bool el_t::operator==(el_t OtherOne)  // overload comparison operator for search based on the key part only, since this is the only case we are using to for.
{
  if (key == OtherOne.key) return true; else return false;
}

bool el_t::operator!=(el_t OtherOne)  //comparison operator will only check keys, since that's the only case we are using it for
{
  if (key != OtherOne.key) return true; else return false;
}
void el_t::operator=(const el_t& OtherOne)  //overload assignment operator to assign all values to the new object
{
  name = OtherOne.name;
  key = OtherOne.key;
  stockPrice = OtherOne.stockPrice;
  category = OtherOne.category;
}
// overload output operator now with changed output to represent the name, price and category
ostream& operator<<(ostream& os, const el_t& E)  //Since we will also be reading from the text file being read to, 
                                                 //output the data the same way as how it was read in
{  
  os  << E.name <<" "<< E.stockPrice << " "<< E.category ;
  return os;  
}  
