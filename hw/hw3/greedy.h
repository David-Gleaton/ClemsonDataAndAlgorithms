#ifndef GREEDY_H
#define GREEDY_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Greedy{
  private:

	struct Candy{
		int weight;
		int taste;
		int bag;
		Candy(int w, int t) {weight = w; taste = t;}

	};	
	struct Bag{
		vector<Candy> B;
		int CurrentWeight;
		Bag() {CurrentWeight = 0;}
	};
  vector<Candy> Bag0;
  int Best;
  int BagSize = 2000;
  int BagNum = 3;
  public:
	Greedy(vector< pair <int,int> >);
	~Greedy();
	void Sort(vector< pair <int, int> > OG, Bag Bag1, Bag Bag2, Bag Bag3);


};
#endif
