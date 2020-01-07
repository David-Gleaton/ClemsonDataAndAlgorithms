#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

//using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int myhash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

Stringset::Stringset()
{
  size = 4; // initial size of table    
  table = new Node *[size]; // allocate table, initialize head ptrs all to NULL
  for (int i=0; i<size; i++) 
    table[i] = NULL;
  num_elems = 0; 
}

Stringset::~Stringset()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}

/* Return true if key is in the set */
bool Stringset::find(string key)
{
  int h = myhash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key)
{
  assert (!find(key));
  num_elems++;
  Node *Insert = new Node(key,NULL);
 

  if (num_elems == size) {
    // TBD: Expand table -- allocate new table of twice the size,
    // re-insert all keys into new table, and de-allocate old table.
    // (you may want to wait and add this code last, once everything
    // else is working, since the class will still function properly,
    // albeit slowly, without this part)
	Node **temptable = table;
	table = new Node *[size*2];
	//Initialize the new list
	for (int i=0; i<size*2; i++) 
	    table[i] = NULL;

	int loophash;
	for (int i=0; i<size; i++) {
	    while (temptable[i] != NULL) {
		//Save the old pointer
	      Node *temp = temptable[i]->next;
		//New hash with new size and key
		loophash = myhash(temptable[i]->key,size*2);
		//Insert the Old value into the new table with the updated hash
		temptable[i]->next = table[loophash];
		table[loophash] = temptable[i];
		//Iterate the old table
	      temptable[i] = temp;	      
	    }
	  }
	//Chage size and delete the old table
	size *= 2;
	delete[] temptable;
  }

  // TBD: Insert new element
	int hash = myhash(key, size);   

	Insert->next = table[hash];
	table[hash] = Insert;
  


}

/* Removes a key.  It is an error if key isn't in the set */
void Stringset::remove(string key)
{
  assert (find(key));
  num_elems--;

  // TBD: Delete element


  for(int i = 0; i<size; i++){
	Node *Delete = new Node;
	Node *temp = new Node;
	if(table[i] != NULL){
		//This takes care of the case where the head has the key
		if(table[i]->key == key){
			Delete = table[i];
			table[i] = table[i]->next;
			delete Delete;		
			return;
		}else{	
			Delete = table[i];
			while(Delete != NULL){
				//If we are at the next to the end of the list and the end node has the key, we remove the end of the list
				if(Delete->next == NULL && Delete->key == key){
					delete Delete;
					return;
				}
				if(Delete->next != NULL){
					if(Delete->next->next == NULL){
						if(Delete->next->key == key){
							delete Delete->next;
							Delete->next = NULL;
							return;
						}
					}else{
					//this will take care of the middle linked list cases
						if(Delete->next->key == key){
							temp = Delete->next;
							Delete->next = Delete->next->next;
							delete temp;
							return;									
						}		


					}
				}
				Delete = Delete->next;
			}
		}
	}


  }



}

void Stringset::print(void)
{
  // TBD: Print contents of table
  Node *Print = new Node;
  for(int i = 0; i<size; i++){
	if(table[i] != NULL){
		Print = table[i];
		while(Print != NULL){
			cout << Print->key << endl;
			Print = Print->next;
		}
	}
  }
}
