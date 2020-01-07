// This is a sketch you can use for your "bad1" .. "bad3" programs...

#include <iostream>
#include <cstdlib>
using namespace std;
/*
David Gleaton
10/6/2019
This program breaks the hash table in prog2 by giving in inputs scaled to be one magintude smaller than the table size
*/
int main(int argc, char *argv[])
{
  if (argc != 2) {
    cout << "Usage: bad2 <input size>\n";
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
//  for (int i=0; i<N; i++)
//    cout << rand() % 1000000 << "\n";
  
	//TODO
	//Overload hashtable
	//Formula they use is: 
	// ((unsigned int)x * 3 + 17) % table_size;
	//It seems that, when inserting large numbers proportionate to the size of the N, the hash table takes around 14 seconds to read in the data
	for(int i = 0; i<N;i++){
		cout << i*(N/10) << '\n';
	}
  return 0;
}
