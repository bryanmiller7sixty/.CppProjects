//CS311 Yoshii
//=========================================================
//HW#: HW3P2 slist
//Your name: Bryan Miller
//Complier:  g++
//File type: client program (tester) HW3P2client.cpp
//===========================================================
/******************************************************************************************
Algorithim:
Part 1: 
Test replace and search functions of slist in the first test to demonstrate 
proper coverage of all cases for slist, to ensure the function is coded properly.
Part 2:
Do the same for the == overload function.
***********************************************************************************************/
using namespace std;
#include <iostream>
#include "slist.h"
#include <stdlib.h>

//PURPOSE: Testing search and replace functions
void testOne()
{ slist L;  // the list 
  int foundPos; // to hold the found position from Search  
  int counter = 1; // used to display test line number
    //  1)add to front once (element 4)
    cout << "Step " << counter << " addFront" << endl; counter++;
    L.addFront(4);

    //  2)add to rear 3 times (elements 6,7,8)
      cout << "Step " << counter << " addRear" << endl; counter++;
    L.addRear(6);
    L.addRear(7);
    L.addRear(8);
    //  3)displayAll    - 4 6 7 8
    cout << "Step " << counter << endl; counter++;
    L.displayAll();

    //  4)search for 6, report the result  - found in pos 2
    cout << "Step " << counter << endl; counter++;
    foundPos = L.search(6);
    cout << "Found 6 in location " << foundPos << endl;

    //  5)replace the 6 with 0 using the search result (foundPos)
    try{
    cout << "Step " << counter << " replace 6" << endl; counter++;
    L.replace(0, foundPos); 
    }catch(slist::OutOfRange){ cerr << "ERROR: Bad position was given" << endl;}
    // 6)displayAll - 4 0 7 8
    cout << "Step " << counter << endl; counter++;
    L.displayAll();

    // 7)search for 8 and report the result - found in pos 4
    cout << "Step " << counter << endl; counter++;
    foundPos = L.search(8);
    cout << "Found 8 in location " << foundPos << endl;

    // 8)replace the 8 with 2 using the search result (foundPos)
    cout << "Step " << counter << " replace 8" << endl; counter++;
    L.replace(2, foundPos);

    // 9)displayAll                       - 4 0 7 2
    cout << "Step " << counter << endl; counter++;
    L.displayAll();

    // 10)search for 5 and report the result   - not found
    cout << "Step " << counter << endl; counter++;
    foundPos = L.search(5);
    cout << "Found 5 in location " << foundPos << endl;

    // 11) replace postion 7 with 10
    try{
      cout << "Step " << counter << " replace 7" << endl; counter++;
      L.replace(10, 7); 
    }catch(slist::OutOfRange){ cerr << "ERROR: Bad position was given" << endl;}
}//end of testOne

// PURPOSE: Testing overloading of ==
void testTwo()
{ 
    slist L1, L2;

  //1. L1 is empty and L2 is empty 
    if (L1 == L2) cout << "true" << endl; else cout << "false" << endl;

  //2. L1 is empty and L2 with 4, 5 
    L2.addRear(4); L2.addRear(5);
    if (L1 == L2) cout << "true" << endl; else cout << "false" << endl;

  //3.  The opposite 
    if (L2 == L1) cout << "true" << endl; else cout << "false" << endl;

  //4. L1 with 1,2,3 and L2 with  1,2,3
    L1.addRear(1); L1.addRear(2); L1.addRear(3);
    int x;
    L2.deleteFront(x);
    L2.deleteFront(x);
    L2.addRear(1); L2.addRear(2); L2.addRear(3);
    if (L1 == L2) cout << "true" << endl; else cout << "false" << endl;

  //5. L1 with 1,2,3 and L2 with  1,2
    L2.deleteRear(x);
    if (L1 == L2) cout << "true" << endl; else cout << "false" << endl;

  //6. L1 has 1,2,3 and L2 has 1,2,3,4
    L2.addRear(3);
    L2.addRear(4);
    if (L1 == L2) cout << "true" << endl; else cout << "false" << endl;

  //7. L1 has 1,2,3 and L2 has 1,2,4
    L2.deleteRear(x);
    L2.deleteRear(x);
    L2.addRear(4);
    if (L1 == L2) cout << "true" << endl; else cout << "false" << endl;

 }//end of testTwo


//PURPOSE: to test slist thoroughly
int main()
{
  testOne(); // for search and replace

  cout << "---- First Part testing done ----- " << endl;

  testTwo();  // for testing ==

}// end of program

