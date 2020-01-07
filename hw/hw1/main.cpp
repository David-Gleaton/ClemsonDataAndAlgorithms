#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "websearch.h"

//using namespace std;

/*
David Gleaton
9/22/2019
Homework 1
*/

int PageCount(void)
{
   string word;
   int pagecount = 0;
   ifstream wordfile("webpages.txt");
   while(wordfile >> word){
	if(word == "NEWPAGE") pagecount++;
   }
   wordfile.close();
   return pagecount;
}

int main(void)
{
   int numpages = PageCount();
   Websearch S(numpages);

  string word, webaddress;
  int urlhash;
  size_t findurl;
  int pages = 0;
  ifstream wordfile("webpages.txt");
  while (wordfile >> word){
	findurl = word.find("http://");
	//If a new Webpage is discovered
	if(word == "NEWPAGE"){
		wordfile >> webaddress;
		urlhash = S.myhash(webaddress,numpages);
		pages++;
		continue;
	//If http:// is there
	}else if(findurl != string::npos){
		size_t findclemson = word.find("clemson.edu/");
		if(findclemson == string::npos){
			continue;
		}else{
			S.Insert(urlhash, webaddress, word, findurl);
			continue;
		}
	}
    S.Insert(urlhash, webaddress, word, findurl);
  }

  wordfile.close();
  S.Pagerank();

  int yup = 0;
  while(yup == 0){
	  cout << "Press ctrl+C to exit." << endl;
	  cout << "Type in a word to find the pagerank and the websites it is on:" << endl;
	  string input;
	  cin >> input;
	  S.printpages(input);
  }

  return 0;
}

