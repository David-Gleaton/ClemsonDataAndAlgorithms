
#include "greedy.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;


Greedy::Greedy(vector< pair <int, int> > OG){

	Best = 0;
	//Take in the candies and place them into Bag0 for now
	//TODO
	Bag Bag1;
	Bag Bag2;
	Bag Bag3; 

	Sort(OG,Bag1, Bag2, Bag3);
	//Will do this in the main
	

}



//Sort the candies based on weight and then place them in Bag0...May not be the best deal
void Greedy::Sort(vector< pair <int, int> > OG, Bag Bag1, Bag Bag2, Bag Bag3){
	vector< pair < int, int > > Order;

	//So now I have a sorted order of named candies based on the ratio
	for(int i = 0; i<OG.size(); i++)
		Order.push_back(pair<int, int>( OG[i].second/OG[i].first,i ));
	sort(Order.begin(),Order.end());
	int a = Order.size() - 1;
	for(int j = 0; j<2000; a--){
		if(!OG[Order[a].second].first + Bag1.CurrentWeight > BagSize){
			Bag1.B.push_back(Candy(OG[Order[a].second].first,OG[Order[a].second].second));
		}
		j += OG[Order[a].second].first;
	}	
	for(int j = 0; j<2000; a--){
		if(!OG[Order[a].second].first + Bag1.CurrentWeight > BagSize){
			Bag2.B.push_back(Candy(OG[Order[a].second].first,OG[Order[a].second].second));
		}
		j += OG[Order[a].second].first;
	}
	for(int j = 0; j<2000; a--){
		if(!OG[Order[a].second].first + Bag1.CurrentWeight > BagSize){
			Bag3.B.push_back(Candy(OG[Order[a].second].first,OG[Order[a].second].second));
		}
		j += OG[Order[a].second].first;
	}
	int FinalScore = 0;
	for(int i = 0; i<Bag1.size(); i++)
		FinalScore += Bag1[i].second;
	for(int i = 0; i<Bag2.size(); i++)
		FinalScore += Bag2[i].second;
	for(int i = 0; i<Bag3.size(); i++)
		FinalScore += Bag3[i].second;
	cout << FinalScore << endl;



}


















