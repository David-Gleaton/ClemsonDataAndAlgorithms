#include <string>
#include <fstream>
#include <iostream>
//#include "websearch.h"

using namespace std;

/*
David Gleaton
9/22/2019

*/
int PageCount()
{
   string word;
   string test = "school";
   int pagecount = 0;
   int fuck = 0;
   ifstream wordfile("webpages.txt");
   while(wordfile >> word){
	if(word == "NEWPAGE") pagecount++;
	if(test == word && pagecount == 1){
		fuck++;
	}
   }
   if(fuck>1) cout << "Yup it doubles" << endl;
   else cout << "NVM we good" << endl;
   wordfile.close();
   return pagecount;
}

int main(void)
{
  int pages = PageCount();
  cout << "There are " << pages << " pages. Damn." << endl;

  return 0;
}


