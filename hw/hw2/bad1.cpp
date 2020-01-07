// This is a sketch you can use for your "bad1" .. "bad3" programs...

#include <iostream>
#include <cstdlib>
using namespace std;

/*
David Gleaton
10/6/2019
This program breaks LoS by givng prog1 a reverse sorted array, then a sorted array
This maximizes the amounts of array reads
*/
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
//  for (int i=0; i<N; i++)
//    cout << rand() % 1000000 << "\n";
  
	//TODO
	//This is LoS, so we need a U shaped input to max its reads
	//Creation of reverse sorted output of N/2 size for first half
	for(int i = N/2; i>=0; i--){
		cout << i << '\n';
	}
	for(int i = 0; i<N/2; i++){
		cout << i << '\n';
	}



  return 0;
}
