// This is a sketch you can use for your "bad1" .. "bad3" programs...

#include <iostream>
#include <cstdlib>
using namespace std;
/*
David Gleaton
10/6/2019
In this program, I took the code that I wrote/was provided in lab5 in order to build a rank based BST
By passing in values that are ranked based on the get_rand() function in prog3, I can maximize the amount
of partitions, hopefully getting it to around N^2
*/
struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = NULL; }
};

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

void print_inorder(Node *T)
{
  if (T == NULL) return;
  print_inorder(T->left);
  cout << T->key << "\n";
  print_inorder(T->right);
}

void split(Node *T, int r, Node **L, Node **R)
{
  // TBD: please fill in this function appropriately
  //TODO Check
    if (T == NULL) {
    *L = NULL;
    *R = NULL;
    return;
  }
    int rank_of_root = T->left ? T->left->size : 0; 
  if (r <= rank_of_root) {
    // recursively split left subtree
    split(T->left, r, L, &T->left);
    *R = T;
  } else {
    split(T->right, r-rank_of_root-1, &T->right, R);
    *L = T;
  }
  fix_size(T);
}

Node *insert_keep_balanced(Node *T, int v, int r)
{
  // TBD: fill this in
  //TODO

  if (T == NULL) return new Node(v);
  int rank_of_root = T->left ? T->left->size : 0;
  int N = T->size + 1;
  if (rand() % N != 0 ) {
    // insert at root
    Node *new_root = new Node(v);
    split(T, r, &new_root->left, &new_root->right);
    fix_size(new_root);
    return new_root;
  }
    if(r <= rank_of_root) T->left = insert_keep_balanced(T->left, v, r);
  if(r > rank_of_root) T->right = insert_keep_balanced(T->right,v, r - rank_of_root - 1);
  fix_size(T);
  return T;



}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cout << "Usage: bad1 <input size>\n";
    return 0;
  }

  int N = atoi(argv[1]);  // get first command-line argument
  if (N<1 || N>100000) {
    cout << "Invalid input size!\n";
    return 0;
  }
  
  // Generate and print bad input of size N for prog1
  // (currently just generates an input of N random numbers)
  cout << N << "\n";
  Node *T = NULL; 
	//TODO
	//Kill QuickSort
	//It uses a pivot of 123456789 % N;
	//Need to have the partion be 1 and n-1 for each step
	for(int i = 0; i<N; i++){
		int x = (123456789 % (i+1));
		T = insert_keep_balanced(T,i,x );	
	}
	print_inorder(T);

	
  return 0;
}
