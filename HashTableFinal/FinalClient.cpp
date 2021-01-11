using namespace std;
#include "htable.h"
#include <iostream>
#include <fstream>
#include <string>
/*
Algorithim:
User enters in a variety of choices to load, display, output and alter that hashtable data structure.

Choice 1.) The user can choose to enter a text file and will read from that file, if valid, otherwise the loop will be exited
The data in the file must contain the data in the right order, seperated by spaces for the data to be read correctly.

Choice 2.) Calls the display method to output the data, the slist element with their data will be displayed, otherwise and empty list 
will be displayed.

Choice 3.) Searches by the ticker symbol, the string is turned into a key, and the key is searched for. If the ticker
isn't all caps or not a valid string of characters, the loop will be exited. If the ticker doesn't exist, the user will be informed.

Choice 4.) Adds a new ticker to the list. The user must enter a valid ticker, as explained above. The user must also enter a valid double,
if the not a integer or decimal, the loop will be broken. The user will also enter the category, if not alphabetical, the loop will be broken.

Choice 5.) Removes a stock from the watchlist. Same idea as the search option except instead of searching, if valid the 
ticker will be deleted.

Choice 6.) Same idea as choice 1, where the text will be outputted to the specified text file, if valid.
*/
int main(){
  //variables/objects that will be utilized during the execution of the loop
  string str;
  double price;
  string category;
  htable watchList;
  int choice;
  string fname;
  string tickerSymbol;
  bool finalFlag = true;
  //choices the user can enter from
  cout << "Enter a file name: ";  //prompt the user to enter a file name
  cin >> fname;
  ifstream fin (fname.c_str(), ios::in);
  //std::ifstream fin(fname); //create the fin object, if the file name isn't valid break the loop and inform the user
  while(finalFlag){
  while(true){
    cout<<""<<endl;
    cout<<"Enter your choice:"<<endl;
    cout<<"1.) Load the data file"<<endl;
    cout<<"2.) Display your Watchlist"<<endl;
    cout<<"3.) Search by ticker"<<endl;
    cout<<"4.) Add a new stock to your watchlist"<<endl;
    cout<<"5.) Remove stock from watchlist"<<endl;
    cout<<"6.) Output watchlist to text file"<<endl;
    cout<<"7.) Exit"<<endl;      
    cin>>choice;
      if(choice == 1){
        if(fin.fail()){
          cout<<"There was an error with the file"<<endl;
          break;
        }else{
        while(fin >> tickerSymbol){  // While we can read the next ticker
          //get the percent change
          fin >> price;
          //then get the category
          fin >> category;
          int key = 0;
          //get a unique int representation of each character, add them toegther and your key is created.
          for(int i = 0; i < tickerSymbol.length();i++){
            char let = tickerSymbol[i];
            int num = (let - 64);
            key += num;
          }
          el_t inputElem(key, tickerSymbol, price, category); //pass in the key, ticker symbol, percent change, and stock catgeory in the constructor.
          watchList.add(inputElem); //add to the table
          
        }
        cout<<"Successfully loaded the data."<<endl;
        }
      }else if(choice == 2){
        watchList.displayTable(); //Simply call the display table function
      }else if(choice == 3){
        cout<<"Enter your ticker symbol to be search, i.e. APPL."<<endl;  //Enter the symbol to be searched
        cin>>tickerSymbol;
        int key = 0;
        //Do the same protocal of finding the key
        for(int i = 0; i < tickerSymbol.length();i++){
          if(tickerSymbol[i] < 65 || tickerSymbol[i] > 90){
            cout<<"The ticker symbol must be in uppercase"<<endl; //if the ticker symbol isn't an uppercase character, break the loop.
            break;
          }
          char let = tickerSymbol[i]; //use the corresponding formula to create the key
          int num = (let - 64);
          key += num;
        }
        el_t elem = watchList.find(key);  //search for the key
        //if the elements key is -1, this means no element currently exists at that key
        if(elem.getkey() ==  -1){
          cout<<"There's no element associated with that key."<<endl;
        }else{
          cout<<elem<<endl; //otherwise the overloaded ostream operator will dislay the key and value of the corresponding element
        }
      }else if(choice == 4){  //step 4 is adding a ticker to your watchlist
        //same protocal as adding the element in case 1, except the user will be inputting all the info.
        cout<<"Enter the name of your ticker"<<endl;
        bool flag = true;
        cin>>tickerSymbol;
        int key = 0;
        for(int i = 0; i < tickerSymbol.length();i++){
          char let = tickerSymbol[i];
          if(let < 65 || let > 90){   //if the letter is not uppercase A-Z break the loop
            cout<<"The ticker symbol must be in uppercase"<<endl;
            flag = false;
            break;  //create a false flag then break the for loop
          }
          int num = (let - 64); //otherwise continue with the key formula
          key += num;
        }
        if(!flag){ break; } //break the loop completely if user entered in a wrong character
        cout<<"Enter the stock price"<<endl;   //otherwise prompt the user to enter a stock price
        cin>>price;
        string testString = to_string(price); //cast the double to a string
        for(int i = 0; i < testString.size(); i++){ //loop through the string checking any of the characters contain a non-integer
          if(testString[i] != '.' && !isdigit(testString[i])){  //however, there may be a decimal place so check for that as well
            cout<<"Not a valid stock price"<<endl;
            flag = false;  //follow the same protocal for breaking the loop as above
            break;
          }
        }
         if(!flag){ break; }
        cout<<"Enter the category, for example: tech; financial; etc."<<endl;
        cin>>category;
        for(int i = 0; i < category.size(); i++){
          if(!isalpha(category[i])){  //Finally check any characters in the string are not alphabetical
            cout<<"Not a valid category"<<endl; //if not, then follow the same steps as above to break the loop
            flag = false;
            break;
          }
        }
        if(!flag){ break; } 
        el_t element(key,tickerSymbol,price,category);  //create a new element object passing in the arguments
        watchList.add(element); //then add to the watchlist
      }else if(choice == 5){  //step 5 is deleting a ticker from your watchlist
        cout<<"Enter a ticker symbol you would like to delete, i.e. APPL"<<endl;
        cin>>tickerSymbol;
        for(int i = 0; i < tickerSymbol.length();i++){
          if(tickerSymbol[i] < 65 || tickerSymbol[i] > 90){ //check if the ticker is all uppercase letters, if not then break the loop
            cout<<"The ticker symbol must be in uppercase"<<endl;
            break;
          }
        }
        bool state = watchList.deleteIt(tickerSymbol);  //otherwise call the deleteit function
        if(state){  //inform the user if the delete was successful or not
          cout<<tickerSymbol<<" has been successfully deleted"<<endl;
        }else{
          cout<<"Ticker symbol"<< tickerSymbol<< "doesn't exist in your watchlist"<<endl;
        }
      }else if(choice == 6){  //Step 6 is writing to a text file
        cout<<"What text file would you like to write to? "<<endl;
        cin>>fname;
        //std::fstream fout(fname); //Create the fout object the pass in the file name
        ofstream fout (fname, ios::out);
        if(fout.fail()){  //if the file name isn't valid break the loop
          cout<<"There was an error with the file"<<endl;
          break;
        }
        watchList.writeToFile(fout);  //otherwise write to the file
        watchList.displayTable();
        cout<<"Sent data to: "<<fname<<endl;
      }else{
        //breaks the outer while loop, this way we can keep looping when the user enters something wrong
        //as well as break when the user wants to exit
        finalFlag = false;
        break;
      }
  }
}
}