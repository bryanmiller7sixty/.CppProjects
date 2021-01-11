// CS311 Yoshii - Hash Table - complete all ** parts.
// Note: this class does not know the parts of element except for key
// so that it would work even if each element in the hash table changed
//-----------------------------------------------------

// ============================================
// HW#: HW8 Hash Table
// Name: Bryan Miller
// File Type: implementation htable.cpp
// =============================================

/******************************************************************************
Algorithim:
First change slist and llist to use the el_t class type instead of typedef
Second change the search function to return an el_t element instead of integer
Constructor: Initialize each slot in the array with an slist
hash(): hashes the key specified by user to a corresponding slot which the slist will be stored
add(): uses the hash function to hash the key specified, adds the element to the rear of the list, then returns the slot #
find(): attempts to find the element associated with the key specified, by searching the slist at the hashed 
keys position, if no such element exists an element with key -1 will be returned
displayTable(): calls display all on each index in the hash table
deleteIt(): Deletes an element object from the list
writeToFile(): Loops through the whole htable and writes every element of a non empty list to the text file 
*******************************************************************************/
using namespace std;
#include <iostream>
#include <string>
#include "htable.h"

htable::htable()
{
  //constructor will fill each slot in the table with an slist
  for(int i = 0; i < TSIZE; i++){
    slist newList;
    table[i] = newList;
  }
}
htable::~htable()
{}
// parameter: integer containing a key 
int htable::hash(int key)
{ 
  //need a count variable to start from beginning of the string
  int count = 0;
  int size;
  //convert the key into a string
  string keyStringCopy = to_string(key);
  //if the size of the string is 2 digits (99% of the time will be this case)
  if(keyStringCopy.size() % 2 == 0){
    size = (keyStringCopy.size() - 1) / 2;

  }else{
    //otherwise reverse the string in case with an odd size 
    size =  ((keyStringCopy.size() - 1) + 1)/ 2;
  }
  for(int i = keyStringCopy.size() - 1; i >= size; i--){
    char let = keyStringCopy[count];
    keyStringCopy[count] = keyStringCopy[i];
    keyStringCopy[i] = let;
    count++;
  }
  //add the keys together after reversed
  key = key + stoi(keyStringCopy);
  //take the new key % table size to get the slot we will be adding to
  int slot = key % TSIZE;
  //return the slot in the array the list will be stored
  return slot;
}

// adds the element to the table and returns slot#
//parameter: el_t type 
int htable::add(el_t element)
{
  int slot = hash(element.getkey());  // hash with the key part
  table[slot].addRear(element);   //at the corresponding slot where the slist is contained, add the element to the rear of the list
  return slot;    //return the slot which the slist is stored
  //** Note that this means adding the element to a slist in the slot (addRear)
}

// finds element using the skey and returns the found element itself
// or a blank element  -- there is no cout in here
el_t htable::find(int skey)
{ 
 int slot = hash(skey); // hash with skey
 el_t selement;  // this is the element to look for in slist
 
// initialize selement with just the skey
 selement.setkey(skey);
 // call slist's search2 with selement which returns the found element 
 // return the found element from here (it could be blank)
 //call search 2 with the selement being searched for with the hashed key index searched in the table
 return table[slot].search2(selement);
}
//Delete function takes the ticker symbol string as an argument and deletes it from the corresponding list
bool htable::deleteIt(string ticker){
  int key = 0;  //go through the length of the string following the same protocal as the client generating the key from the string
  for(int i = 0; i < ticker.length();i++){
    char let = ticker[i];
    int num = (let - 64);
    key += num;
  }
  int slot = hash(key); //hash the key
  el_t elem = find(key);  //then call the find function and store in the corresponding element
  if(elem.getkey() == -1){  //if the key is -1 there was no element that existed, so return false
    return false;
  }else{
    int count = table[slot].search(elem); //otherwise search for the element and have the count in the list returned
    table[slot].deleteIth(count, elem); //delete the desired element at the slot
    return true;  //return true to the user signifying the element was deleted
  }
}
//write to file takes the ostream object as an argument then loops through
//the whole table writing each element of each list to the file
void htable::writeToFile(ostream& fout){   //have the function recieving an ostream object, containing the file
  for(int i = 0; i < TSIZE; i++){ //loop throught the whole table
    if(!table[i].isEmpty()){  //if the table slot is empty don't bother printing to the file
      int listSize = table[i].returnSize(); //call the return size function to get the size of the list
      for(int x = 0; x < listSize; x++){  //loop through the size of the list
        el_t obj;
        obj = table[i].returnIth(x, listSize);  //assign the objects data to the new object 
        fout<<obj<<endl;  //print the data to the file
      }
    }
  }
}
// }
// displays the entire table with slot#s too
//go through each index calling diplay all on the corresponding slist
void htable::displayTable()
{
  for (int i = 0; i < TSIZE; i++)
    { 
      cout << i << ":" <<"[";   
      // call slist's displayAll
      table[i].displayAll();
      cout<<" ]"<<endl;
    }
}
