// CS311 : This is the BST implementation file template by Rika Yoshii

// Each node has an Up link to make it easy to go up the tree.  It must be set as nodes are inserted.  Some deletion
// cases require Up link to be updated.  Couts are there to test to make sure
// you set the Up links correctly!!!! (Fall 19)
//
// INSTRUCTIONS:
// Look for ** comments to complete this file for HW4
// Try not to delete the ** comments, but add the code next to them
// Make sure all { } match. Doing Tab on each line helps.
// Draw pictures as you complete each **

// =========================================================
//HW#: HW4 BST
//Your name: Bryan Miller
//Complier:  g++
//File type: implementation file binstree.cpp
//================================================================

/*****************************************************************
 * Algorithim: 
 * Define the following binary search tree methods:
 * 
 * (Display): Calls inordersearch function.
 * (Preordersearch): Traverses tree preorder and returns true if found, false if not. 
 * (Search): Calls preordersearch.
 * (Inordersearch) Recursively traverses down tree and displays each corresponding element.
 * (Insertvertex): Inserts the vertex corresponding with its relationship with the root, 
 * less than will be on the left subtree, greater than will be on the right subtree.
 * (Deletevertex): Deletes the vertex if it's the root with no subtrees or only one subtree on either sie,
 * otherwise call remove function.
 * (Remove): Removes according to the three cases: it is a leaf, delete it, if it has just one child, 
 * bypass it, it has two children, replace it with the max of the left subtree, this will contain another call to 
 * FindMax function.
 * (FindMax): Finds the max of the left subtree, which first goes to the left subtree of vertex called, then traverses
 * down the right subtree to find the max.
 * ****************************************************************/

using namespace std;
#include <iostream>
#include "binstree.h"

// constructor  initializes Root
BST::BST()
{
  Root = NULL;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;    
}
// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
// Recursive call to itself passing in the next vertex down the left and right side of the tree.
void BST::dtraverse(Vertex *V)  // recursive post order traversal
{   
  if (V != NULL) 
    {
      dtraverse(V->Left);         // destroy left sub tree of V
      dtraverse(V->Right);       //  destroy right sub tree of V
      delete V;                  //  delete V
    }
}

// PURPOSE: Show vertices in IN order traversal from the Root
// Calls inorder traversal passing in the root
void BST::Display()
{
  cout << "Elements in the IN order: " << endl;
  INorderTraversal(Root);  // start in-order traversal from the root
}
// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC, the height and balance will always be 0 
// If the element is not null the function calls itself passing in the left.
// After the left reaches a null case (Reaches a leaf) print the element and try to go right 
// If right isn't null keep going until null case is hit, then return back to the previous call.
// After the function finishes the whole tree will have been traveresed.
void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
    {
      // ** traverse left sub-tree of V recursively
      INorderTraversal(V->Left);
      // ** display V's element, height and balance and do endl; 
      cout<<V->Elem<<endl;
      cout<<"Height:0 Balance:0"<<endl; 
      // ** traverse right sub-tree of V recursively
      INorderTraversal(V->Right);
    }
}

// PURPOSE: Searches for an element in PRE-order traversal
// PARAM: el_t defined type 
// This is the same as Depth First Traversal
// If preorder search call returns true (the element is found) return true
// Otherwise return false 
bool BST::Search(el_t K)
{
  if(PREorderSearch(Root, K)){
    return true;
  }
  return false;
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
// K is what we are looking for
// Read comments within the function
bool BST::PREorderSearch(Vertex *V, el_t K)
{
  //This null case will resolve the previous call if the element is not found in the tree.
  if(V == NULL){
    return false;
  }
    //If this case is hit and returns true
    //propogate back up the tree passing the true value back until returning
    //to the caller
    //this is the resolve case
  else if(K == V->Elem){ 
    return true;
  }
  //if the value was found in a left subtree 
  //the value will be propogated through this recursive call, then will return
  //the last true back to the caller
  else if(PREorderSearch(V->Left, K)){
    return true;
  }
  //traverse the right subtree
  //if the value was found on a right subtree this call will be the return that returns back to the caller
  return PREorderSearch(V->Right, K);
}
  

// ------ The following are for adding and deleting vertices -----


// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E)
{
  // Set up a new vertex first
  Vertex *N;         // N will point to the new vertex to be inserted
  N = new Vertex;    // a new vertex is created
  N->Left  = NULL;   // make sure it does not
  N->Right = NULL;   // point to anything
  N->Elem  = E;      // put element E in it
  N->Height = 0;
  N->Balance = 0;
  N->Up = NULL;      // no parent for now
  cout << "Trying to insert " << E << endl;

  if (Root == NULL){  // Special case: we have a brand new empty tree
    Root = N;      // the new vertex is added as the root
    cout << "...adding " << E << " as the root" << endl; 
    // end of the special case
  }else{  // the tree is not empty
    Vertex *V;       // V will point to the current vertex
    Vertex *Parent;  // Parent will always point to V's parent
    V = Root;        // start with the root as V
    Parent = NULL;   // above V so it does not point to anything  
	  // go down the tree until you cannot go any further        
	  while (V != NULL){
	    if (N->Elem == V->Elem){ // the element already exists
        cout << "...error: the element already exists" << endl;
		    return;  
      }else{
	      if (N->Elem < V->Elem){  // what I have is smaller than V
		      cout << "...going to the left" << endl; 
		      // ** change Parent to be V to go down
          Parent = V; 
		      // ** change V to be V's Left 
          V = V->Left;
		    }else{ // what I have is bigger than V
		      cout << "...going to the right" << endl;
		      // ** change Parent to be V to go down
          Parent = V;
		      // ** change V to be V's Right 
          V = V->Right;
		    }
      }
	  }
    //end of while, reached NULL -- Must add N as the Parent's child
    if (N->Elem < Parent->Elem){  
	    // ** Parent's Left should point to the same place as N 
      Parent->Left = N;
	    cout << "...adding " << E << " as the left child of " << Parent->Elem << endl;
      // ** N must point UP to the Parent
      N->Up = Parent; 
      cout << N->Elem  << " now points UP to " << N->Up->Elem << endl;   
      // *** EC call here to adjust height and BF
    }else{
	    // ** Parent's Right should point to the same place as N
      Parent->Right = N;
      cout << "...adding " << E << " as the right child of "<< Parent->Elem << endl;
      N->Up = Parent;
      // ** N must point UP to the Parent 
      cout << N->Elem << " now points UP to " << N->Up->Elem << endl;   
	     // *** EC call here to adjust height and BF
  	}
  }// end of normal case
}// end of InsertVertex


// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove
// Covers cases where there is just a root (no childeren), and if there's a root with only one subtree.
// Otherwise call the remove function.   
void BST::DeleteVertex(el_t E){
  cout << "Trying to delete " << E << endl;
  Vertex *V;       // the current vertex
  Vertex *Parent;  // Parent will always point to V's parent
  // case 1: Lonely Root  --------------------
  if ((E == Root->Elem) && (Root->Left == NULL) && (Root->Right == NULL)){ 
    // only the Root was there and deleted it
    cout << "...deleting the lonely root" << endl;
    delete Root; 
    Root = NULL;
    return; 
  }  
  // case 2:  One Substree Root ----------------
  // ** if what you want to delete is the root
  if(((E == Root->Elem) && (Root->Left == NULL)) || ((E == Root->Elem) && (Root->Right == NULL))){ 
    cout << "... deleting the root with just one child" << endl; 
    // ** and it has only the left subtree
    if((Root->Right == NULL)){  
      //** change the root to the left child and return
      Root = Root->Left;
      //delete the parent node
      delete Root->Up;
      Root->Up = NULL;
       //   making sure the old root has been deleted and the new root's UP is NULL 
    }else{
      //it has only the right subtree, change the root to the right child and return
      //making sure the old root has been deleted and the new root's UP is NULL
      Root = Root->Right;
      delete Root->Up;
      Root->Up = NULL;
    }
    return;
  }// end of deleting the root with one subtree
  // ---- Otherwise deleting something else  --------------
  V = Root;  // start with the root to look for E
  Parent = NULL;  // above the V so does not point to anything yet
  // going down the tree looking for E
  while (V != NULL){ 
    if (E == V->Elem){   // found it
	    cout << "...removing " << V->Elem << endl;
	    // ** call remove here to remove V
      remove(V, Parent);
	    return; 
    }else if(E < V->Elem){  
      cout << "...going to the left" << endl;
	    // ** update Parent and V here to go down
      Parent = V;
      V = V->Left; 
	  }else{  
      cout << "...going to the right" << endl;
	    // ** update Parent and V here to go down
      Parent = V;
      V = V->Right;
	  }
  }// end of while
  // reached NULL  -- did not find it
  cout << "Did not find the key in the tree." << endl;
}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P){
  // ** if V is a leaf (case 1)
  if(V->Right == NULL && V->Left == NULL){
	  cout << "removing a leaf" << endl;
	  // ** if V is a left child of P
    if(P->Left == V){
	    // ** delete V and also make Parent's left NULL 
      delete V;
      P->Left = NULL;
      // *** EC call here from P to adjust height and BF  
	  }else{ // V is a right child of the Parent
      // ** delete V and also make Parent's right NULL
      delete V;
      P->Right = NULL; 
      // *** EC call from P to adjust height and BF
    }
  //end of leaf case
  }else if(V->Right == NULL && V->Left != NULL){ // ** if V has just the left child so bypass V (case 2)
    Vertex* C = V->Left; // the left child
	  cout << "removing a vertex with just the left child" << endl;
    // ** You need if then else to determine Parent's left or right
    if(P->Left == V){//V is the left leaf of the parent
      P->Left = C;
    }else{ //V is the right child of parent
      P->Right = C;
    }
	  //    should point to V's left child; 
    // ** Make V's left child point UP to the parent;
    C->Up = P;
    cout << C->Elem << " points up to " << C->Up->Elem << endl;
	  // ** Be sure to delete V
    delete V;
    // *** EC call from P to adjust height and BF
	  // end of V with left child 
  }else if(V->Left == NULL && V->Right != NULL){ // ** if V has just the right child so bypass V (case 2)
    Vertex* C = V->Right;  // the right child
	  cout << "removing a vertex with just the right child" << endl;
	  if(P->Left == V){//V is the left leaf of the parent
      P->Left = C;
    }else{ //V is the right child of parent
      P->Right = C;
    }
	  //    should point to V's left child; 
    // ** Make V's left child point UP to the parent;
    C->Up = P;
    cout << C->Elem << " points up to " << C->Up->Elem << endl;
	  // ** Be sure to delete V
    delete V;
    // *** EC call from P to adjust height and BF
	  // end of V with right child
  }   
  else{ // V has two children (case 3)
    cout << "removing an internal vertex with children" << endl;
	  cout << "..find the MAX of its left sub-tree" << endl;
	  el_t Melem;
	  // find MAX element in the left sub-tree of V
    Melem = findMax(V);
    cout<<"the number"<<Melem<<endl;
    cout << "..replacing " << V->Elem << " with " << Melem << endl;
    // ** Replace V's element with Melem here
    V->Elem = Melem;
  }//end of V with two children    
}// end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
el_t BST::findMax(Vertex *V){
  Vertex *Parent = V;
  V = V->Left;          // start with the left child of V
  // ** while the right child of V is still available
  if(V->Right != NULL){
    while(V != NULL){
      // ** update Parent and V to go to the right
      Parent = V;
      V = V->Right;
    }
  }
  // reached NULL Right  -- V now has the MAX element
  el_t X = V->Elem;
  cout << "...Max is " << X << endl;
  remove(V, Parent);    // remove the MAX vertex 
  return X;             // return the MAX element
}// end of FindMax

