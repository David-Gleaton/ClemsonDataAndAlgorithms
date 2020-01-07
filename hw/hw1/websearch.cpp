#include <iostream>
#include <string.h>
#include <assert.h>
#include "websearch.h"

using namespace std;

/*
David Gleaton
Homework 1
9/28/2019
*/

//This method inserts the word into the wordarray
void Websearch::InsertWord(string webaddress, int urlhash, string word){

	numWelems++;
	//Like lab 2, this doubles the size of the wordarray
	if (numWelems == wordsize) {

		WordParent **tempwordarray = wordarray;
		wordarray = new WordParent *[wordsize*2];
	//Initialize the new list
		for (int i=0; i<wordsize*2; i++) 
		    wordarray[i] = NULL;
	
		int loophash;
		for (int i=0; i<wordsize; i++) {
		    while (tempwordarray[i] != NULL) {
			//Save the old pointer
				

			WordNode *temp = tempwordarray[i]->next;
			//New hash with new size and key
			loophash = myhash(tempwordarray[i]->word,wordsize*2);
			//Insert the Old value into the new table with the updated hash

			wordarray[loophash] = tempwordarray[i];
			wordarray[loophash]->next = temp;			

			tempwordarray[i] = tempwordarray[i]->wordnext;

		    }
		  }
		//Chage size and delete the old table
		wordsize *= 2;
		delete[] tempwordarray;
  	}





	int wordhash = myhash(word, wordsize);
	//If there is a collision in the wordarray, I would chain them together
	if(wordarray[wordhash] == NULL){
		//Base case creation of node
		WordNode *temp = new WordNode(webaddress, word, urlhash, NULL);
		wordarray[wordhash] = new WordParent(word, temp, NULL);
	}else if(wordarray[wordhash]->word != word){
		//Usage of chaining to avoid collisions
		WordParent *head = wordarray[wordhash];
		if(head->wordnext == NULL){
			WordNode *temp = new WordNode(webaddress, word, urlhash, NULL);
			WordParent *newWord = new WordParent( word, temp, NULL);
			wordarray[wordhash]->wordnext = newWord;
		}else{
			//Iterate thru the word's chain to find/insert the node
			while(head->wordnext != NULL){
				if(head->word == word){
					WordNode *temp = new WordNode(webaddress, word, urlhash, head->next);
					head->next = temp;
					break;
				}
				head = head->wordnext;
				if(head->wordnext == NULL && head->word != word){
					WordNode *temp = new WordNode(webaddress, word, urlhash, NULL);
					WordParent *newWord = new WordParent(word, temp, NULL);
					wordarray[wordhash]->wordnext = newWord;
				}
			}


		}

	}else{

		WordNode *temp = new WordNode(webaddress, word, urlhash, wordarray[wordhash]->next);
		wordarray[wordhash]->next = temp;	
	}





}
 
//This method will build the page array and pass the word onto the Insertword function
void Websearch::Insert(int urlhash,string webaddress, string word, size_t findurl){
	
	//Block that deals with inserting words
	if(findurl == string::npos){
		if(pagearray[urlhash] == NULL){
			test++;
			Word *temp = new Word(word, NULL);
			pagearray[urlhash] = new Page(webaddress, 1/pagesize, 0.0, NULL, temp, NULL);
		}else if(pagearray[urlhash]->url !=webaddress){
			Page *head = pagearray[urlhash];
			//If the Page is pointing to no one, insert a page in that list
			if(head->webnext == NULL){
					//Create the link node, the first of its kind
					Word *temp = new Word(word, NULL);
					//Create the new page node, holding its own address and pointing to the parent page node's page linked list	
					Page *newPage = new Page(webaddress, 1/pagesize, 0.0, NULL, temp, pagearray[urlhash]->webnext);
					//Place the newpage at the head of the page's page linked list
					pagearray[urlhash]->webnext = newPage;			
			}else{
				//This will deal with walking down the page linked list
				while(head->webnext != NULL){
					//If the page already has a node created
					if(head->url == webaddress){
						//Here we hope that it will work
						//This will create a new page node and have the head next point to it
						Word *temp = new Word(word, head->wordnext);
						head->wordnext = temp;
						break;
					}
					head = head->webnext;
					//This will be if we reach the end of the list and the page node is not there
					if(head->webnext == NULL && head->url != webaddress){
						//This essentially does the same as if the list was empty, but appends the node at the top of the list
						//Create the link node, the first of its kind
						Word *temp = new Word(word, NULL);
						//Create the new page node, holding its own address and pointing to the parent page node's page linked list	
						Page *newPage = new Page(webaddress, 1/pagesize, 0.0, NULL, temp, pagearray[urlhash]->webnext);
						//Place the newpage at the head of the page's page linked list
						pagearray[urlhash]->webnext = newPage;
						break;
					}
				}
			}
		//This will deal with where we are using the same node, and adding a link
		}else{
			Word *temp = new Word(word, pagearray[urlhash]->wordnext);
			pagearray[urlhash]->wordnext = temp;	

		}
		
		InsertWord(webaddress,urlhash, word);
	//This will indicate that a link need to be inserted
	}else{

		int pageurl = myhash(word, pagesize);

		if(pagearray[urlhash] == NULL){
			test++;
			PageNode *temp = new PageNode(webaddress,pageurl, NULL);
			pagearray[urlhash] = new Page(webaddress, 1/pagesize, 0.0, temp, NULL, NULL);
		}else if(pagearray[urlhash]->url !=webaddress){
			Page *head = pagearray[urlhash];
			//If the Page is pointing to no one, insert a page in that list
			if(head->webnext == NULL){
					//Create the link node, the first of its kind
					PageNode *temp = new PageNode(webaddress,pageurl, NULL);
					//Create the new page node, holding its own address and pointing to the parent page node's page linked list	
					Page *newPage = new Page(webaddress, 1/pagesize, 0.0, temp, NULL, pagearray[urlhash]->webnext);
					//Place the newpage at the head of the page's page linked list
					pagearray[urlhash]->webnext = newPage;			
			}else{
				//This will deal with walking down the page linked list
				while(head->webnext != NULL){
					//If the page already has a node created
					if(head->url == webaddress){
						//Here we hope that it will work
						//This will create a new page node and have the head next point to it
						PageNode *temp = new PageNode(webaddress,pageurl, head->pagenext);
						head->pagenext = temp;
						break;
					}
					head = head->webnext;
					//This will be if we reach the end of the list and the page node is not there
					if(head->webnext == NULL && head->url != webaddress){
						//This essentially does the same as if the list was empty, but appends the node at the top of the list
						//Create the link node, the first of its kind
						PageNode *temp = new PageNode(webaddress, pageurl, NULL);
						//Create the new page node, holding its own address and pointing to the parent page node's page linked list	
						Page *newPage = new Page(webaddress, 1/pagesize, 0.0, temp, NULL, pagearray[urlhash]->webnext);
						//Place the newpage at the head of the page's page linked list
						pagearray[urlhash]->webnext = newPage;
						break;
					}
				}
			}
		//This will deal with where we are using the same node, and adding a link
		}else{
			PageNode *temp = new PageNode(webaddress,pageurl, pagearray[urlhash]->pagenext);
			pagearray[urlhash]->pagenext = temp;	

		}
	}


}


/*Unfortunately I couldn't quite figure out Pangrank
	Also, as a guide, this is a pretty messy function
	So, the pagearray has elements of chaining, which are reflected in the pagerank implementation
	Basically, I run down the page array, but if there are any collision spots, indicated by a pagearray[i]->webnext != NULL,
	I run down those lists to give them their due as well

*/
void Websearch::Pagerank(){


	for(int z = 0; z<50; z++){
		//Implementation of the first loop
		for(int a = 0; a<pagesize; a++){
			if(pagearray[a] != NULL){ 
				pagearray[a]->new_weight = 0.1/pagesize;
				Page *head = pagearray[a]->webnext;
				while(head != NULL){
					head->new_weight = 0.1/pagesize;
					head = head->webnext;
				}
			}
		}
		//Implementation of the second loop
		for(int i = 0; i<pagesize; i++){
			if(pagearray[i] == NULL) continue;
			int t = 0;
			Page *Rank = pagearray[i];
			while(Rank != NULL){
				PageNode *head = pagearray[i]->pagenext;
				while(head !=NULL){
					t++;
					head = head->next;
				}	
				//Walk down the first list		
				head = Rank->pagenext;
				while(head != NULL){
					//Walk down the second list
					Page *otherhead = pagearray[head->urlhash];
					while(otherhead != NULL){
						if(otherhead->url == head->webaddress){
							otherhead->new_weight += ((0.9*Rank->weight)/t);
							break;
						}				
						otherhead = otherhead->webnext;
					}
					head = head->next;
				}			




				Rank = Rank->webnext;		
			}

		}
		//Implementation of the third loop
		for(int b = 0; b<pagesize; b++){
			if(pagearray[b] == NULL) continue;
			Page *Rank = pagearray[b];
			while(Rank != NULL){
				Rank->weight = Rank->new_weight;	
				Rank = Rank->webnext;
			}	
		}

	}



}



/* Return a hash for the string s in the range 0..table_size-1 */
int Websearch::myhash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

Websearch::Websearch(int numpages)
{

  pagesize = numpages;
  wordsize = 10000;
  pagearray = new Page *[pagesize];
  wordarray = new WordParent *[wordsize];
  for(int i = 0; i < pagesize; i++)   
	pagearray[i] = NULL;//new Page(pagesize);
  for(int i = 0; i < wordsize; i++)
	wordarray[i] = NULL;
  numWelems = 0;

}

Websearch::~Websearch()
{

	for(int i = 0; i<pagesize; i++){
		Page *PageWalker = pagearray[i];
		while(PageWalker != NULL){
			PageNode *Linkwalker = PageWalker->pagenext;
			while(Linkwalker != NULL){
				if(Linkwalker->next == NULL){
					PageNode *temp = Linkwalker;
					delete temp;
					Linkwalker = PageWalker->pagenext;
				}

			 	Linkwalker = Linkwalker->next;
			}
			delete Linkwalker;
			Word *WordWalker = PageWalker->wordnext;
			while(WordWalker != NULL){
				if(WordWalker->next == NULL){
					Word *temp = WordWalker;
					delete temp;
					WordWalker = PageWalker->wordnext;
				}

				WordWalker = WordWalker->next;
			}
			delete WordWalker;
			if(PageWalker->webnext == NULL){
				Page *temp = PageWalker;
				delete temp;
				PageWalker = pagearray[i];
			}

			PageWalker = PageWalker->webnext;
		}
		delete PageWalker;
	}
	delete [] pagearray;

	for(int i = 0; i< wordsize; i++){
		WordParent *Pare = wordarray[i];
		while(Pare != NULL){
			WordNode *Child = Pare->next;
			while(Child !=NULL){
				WordNode *temp = Child;
				delete temp;
				Child = Pare->next;
			}
			delete Child;
			if(Pare->wordnext == NULL){
				WordParent *temp = Pare;
				delete temp;
				Pare = wordarray[i];
			}
			Pare = Pare->wordnext;
		}
		delete Pare;

	}
	delete [] wordarray;
}


//Prints out the typed in words, and returns a statement if the word is not found
void Websearch::printpages(string input){
	int location = myhash(input, wordsize);
	if(wordarray[location] == NULL){
		 cout << "Can't Find that word!" << endl;
		 return;
	}
	double printweight = 0.0;

	if(wordarray[location]->word == input){
		WordNode *head = wordarray[location]->next;
		while(head !=NULL){
			Page *otherhead = pagearray[head->urlhash];
			while(otherhead != NULL){
				if(otherhead->url == head->webaddress){
					printweight = otherhead->weight *100*pagesize;
					cout << printweight << " " << otherhead->url << endl;
					break;
				}
				otherhead = otherhead->webnext;
			}	

			head = head->next;
		}		
	}else{
		WordParent *temp = wordarray[location];
		while(temp != NULL){
			if(temp->word == input){
				WordNode *head = wordarray[location]->next;
				while(head !=NULL){
					Page *otherhead = pagearray[head->urlhash];
					while(otherhead != NULL){
						if(otherhead->url == head->webaddress){
							printweight = otherhead->weight *100*pagesize;
							cout << printweight << " " << otherhead->url << endl;
						break;
						}
					otherhead = otherhead->webnext;
					}	

				head = head->next;
				}
			}
			temp = temp->wordnext;
		}
	}

	

}


