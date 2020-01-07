#ifndef WEBSEARCH_H /* Prevent multiple inclusion... */
#define WEBSEARCH_H

#include <string>
using namespace std;
/*
David Gleaton
Homework 1
9/28/2019
*/


class Websearch {

 private: 
  struct PageNode{
    string webaddress;
    int urlhash;
    PageNode *next;
    PageNode(string web,int url, PageNode *n) {webaddress = web; urlhash = url; next = n;}
  };

  struct Word{
    string word;
    Word *next;
    Word(string w, Word *n) {word = w; next = n;}
  };


  struct Page {
    string url;
    double weight;
    double new_weight;
    Word *wordnext;
    PageNode *pagenext;
    Page *webnext;
    Page(string u, double w, double nw, PageNode *pn, Word *wn, Page *ppn) { url = u; weight = w; new_weight = nw; pagenext = pn ;wordnext = wn; webnext = ppn;}
    Page(int pagesize) { url = ""; weight = 1/pagesize; new_weight = 0.0; wordnext = NULL; pagenext = NULL;  }
  };

  struct WordNode{
    string word;
    string webaddress;
    int urlhash;
    WordNode *next;
    WordNode(string web, string w, int urlh, WordNode *n) {webaddress = web; word = w;urlhash = urlh; next = n;}
  };

  struct WordParent{ 
    string word;
    WordNode *next;
    WordParent *wordnext;
    WordParent(string w, WordNode *n, WordParent *temp) { word = w; next = n; wordnext = temp; }
  };

  
  Page **pagearray;
  WordParent **wordarray;
  int pagesize;
  int wordsize;
  int numWelems;

 public:
  Websearch(int numpages);
  ~Websearch();
  void Insert(int urlhash, string webaddress, string word, size_t findurl);
  void printpages(string input);  
  int myhash(string s, int table_size);
  void InsertWord(string webaddress, int urlhash, string word);
  void Pagerank();
};
#endif
