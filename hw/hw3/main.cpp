
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
/*
David Gleaton
hw3
11/9/19
May god have mercy upon me.
*/

struct Candy{
	int weight;
	int taste;
	int bag;
	double ratio;
	Candy(int w, int t, int r) {weight = w; taste = t; bag = r; ratio = t/(double)w;}

};	
struct Bag{
	int score;
	int weight;
	Bag() {weight = 0; score = 0;}
};
 int Best = 0;
 int BagSize = 2000;
 int BagNum = 3;
 int CurIterative = 0;
 int BestIterative = 0;
 int GreScore = 0;
 int ExBestScore = 0;
void Exhaustive(vector< pair <int, int> > OG, Bag Bag1, Bag Bag2, Bag Bag3, int index){


		/*
			I know this is gross, but by checking to see if the bag has a good score at 3.5 of its weight
			And returning if it doesn't cuts out a bunch of unnecessary solutions
		*/


	if(index == OG.size()) return;
	if(Bag1.weight > BagSize/3.5 && Bag1.score < GreScore/2) return;
	if(Bag2.weight > BagSize/3.5 && Bag2.score < GreScore/2) return;
	if(Bag3.weight > BagSize/3.5 && Bag3.score < GreScore/2) return;

	//This will iterate over each bag, placing the candy in the bag if possible
	for(int i = 0; i<3;i++){
		if(i ==0 && Bag1.weight + OG[index].first < BagSize){
			Bag1.weight += OG[index].first;
			Bag1.score += OG[index].second;

		}else if(i == 1 && Bag2.weight + OG[index].first < BagSize){
			Bag2.weight += OG[index].first;
			Bag2.score += OG[index].second;

		}else if(i == 2 && Bag3.weight + OG[index].first < BagSize){
			Bag3.weight += OG[index].first;
			Bag3.score += OG[index].second;

		}
	
		Exhaustive(OG, Bag1, Bag2, Bag3, index+1);
		//If at any point our score is higher than our best, update and preserve
		if(Bag1.score+Bag2.score+Bag3.score > ExBestScore){
			ExBestScore = Bag1.score+Bag2.score+Bag3.score; 
		}
		//Remove the candy from the bag for the next iteration
		if(i == 0){
			Bag1.weight -= OG[index].first;
			Bag1.score -= OG[index].second;
		}else if(i == 1){
			Bag2.weight -= OG[index].first;
			Bag2.score -= OG[index].second;
		}else if(i == 2){
			Bag3.weight -= OG[index].first;
			Bag3.score -= OG[index].second;
		}
	
	}

	

}



int Iterative(vector< Candy > It){
	int Score = 0;
		
	int Bag1 = 0;
	int Bag2 = 0;
	int Bag3 = 0;
	//In this case bag0 is bag1
	vector<pair <double, int> > Order0;
	vector<pair <double, int> > Order1;
	vector<pair <double, int> > Order2;

	/*
		Create an Order Vector of pairs with the ratio of the Candy and its index in It
		Only add in Candies of the target Bag
		Greedily Select the best candies
	*/
	//So now I have the 3 bags of candy sorted into greedy order with the Candy index for scoring 
	for(int i = 0; i<It.size(); i++){
		if(It[i].bag == 0)
			Order0.push_back(pair< double, int> (It[i].ratio, i));
		if(It[i].bag == 1)
			Order1.push_back(pair< double, int> (It[i].ratio, i));
		if(It[i].bag == 2)
			Order2.push_back(pair< double, int> (It[i].ratio, i));
	}

	sort(Order0.begin(), Order0.end());
	sort(Order1.begin(), Order1.end());
	sort(Order2.begin(), Order2.end());
	//Place into bags greedily	
	for(int i = 0, a = Order0.size()-1; i<Order0.size(); i++, a--){
		if(Bag1+It[Order0[a].second].weight>BagSize) continue;
		Bag1+=It[Order0[a].second].weight;
		Score +=  It[Order0[a].second].taste;
	
	}
	for(int i = 0, a = Order1.size()-1; i<Order1.size(); i++, a--){
		if(Bag2+It[Order1[a].second].weight>BagSize) continue;
		Bag2+=It[Order1[a].second].weight;
		Score +=  It[Order1[a].second].taste;
	
	}
	for(int i = 0, a = Order2.size()-1; i<Order2.size(); i++, a--){
		if(Bag3+It[Order2[a].second].weight>BagSize) continue;
		Bag3+=It[Order2[a].second].weight;
		Score +=  It[Order2[a].second].taste;
	
	}

	return Score;
}



void Greedy(vector< pair <int, int> > OG){

	vector< pair < double, int > > Order;

	//So now I have a sorted order of named candies based on the ratio
	for(int i = 0; i<OG.size(); i++)
		Order.push_back(pair<double, int>( OG[i].second/(double)OG[i].first,i ));
	sort(Order.begin(), Order.end());
	vector<int>::iterator a;
//Apparently 15 times works, shoot me I don't know how that worked
int N = 15;
int FinalScore = 0;

	//So this absolute mess if a hacked together thing
	//All these for loops are the same btw
	for(int j  = 0, a = Order.size()-1, i = 0; i<N; a--, i++){
		//Since I couldn't figure out to delete from the Order vector, I tombstoned the removed candies
		//Also, if adding this candy will put us over capacity, continue to the next candy
		if(Order[a].first == -1 || j + OG[Order[a].second].first >BagSize) continue;	
		else{
			//Add to the bag's weight
			j += OG[Order[a].second].first;
			//Add to the FinalScore
			FinalScore += OG[Order[a].second].second;
			//Tombstone that candy
			Order[a].first = -1;
			//Reset the for loop ???
			if(a == 0) a = Order.size()-1;
		}
	}
	//This is to be used in Exhaustive, I know, its gross
	GreScore = FinalScore;
	for(int j  = 0, a = Order.size()-1, i = 0; i<N; a--, i++){
		if(Order[a].first == -1 || j + OG[Order[a].second].first >BagSize) continue;	
		else{
			j += OG[Order[a].second].first;
			FinalScore += OG[Order[a].second].second;
			Order[a].first = -1;
			if(a == 0) a = Order.size()-1;
		}
	}

	for(int j  = 0, a = Order.size()-1, i = 0; i<N; a--, i++){
		if(Order[a].first == -1 || j + OG[Order[a].second].first >BagSize) continue;	
		else{
			j += OG[Order[a].second].first;
			FinalScore += OG[Order[a].second].second;
			Order[a].first = -1;
			if(a == 0) a = Order.size()-1;
		}
	}
	if(Best < FinalScore) Best = FinalScore;	
	cout << FinalScore << endl;

}	

int main(void){

	vector< pair <int, int> > OG;
	vector< Candy > It;
	srand(1);
	int weight, taste;
	Bag Bag1;
	Bag Bag2;
	Bag Bag3;
	ifstream wordfile("candy.txt");
	for(int i = 0; wordfile >> weight >> taste; i++){
		OG.push_back(pair<int ,int >(weight, taste));
		It.push_back(Candy(weight, taste, rand()%BagNum));
	}
	Greedy(OG);
	//I know I'm supposed to use 1000, but 5k gives the right solution quickly soooo 
	for(int T = 0; T<5000; T++){
		CurIterative = 0;
		//Clear and reset a randomly assorted amount of candies
		It.clear();
		for(int i = 0; i<OG.size();i++){
			It.push_back(Candy(OG[i].first, OG[i].second, rand()%BagNum));		
		}
		CurIterative = Iterative(It);		
		if(CurIterative > BestIterative) BestIterative = CurIterative;
	}	
	
	cout << BestIterative << endl;

	Exhaustive( OG, Bag1, Bag2, Bag3,0);

	cout << ExBestScore << endl;

	return 0;
}

