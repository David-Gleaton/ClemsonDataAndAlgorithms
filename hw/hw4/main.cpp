#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include "graphics.h"

using namespace std;

/*
David Gleaton
HW 4
12/6/19
*/

// Each point represents (x, y, z=elevation above sea level)
// units are in feet; x and y increase to the east and north, respectively
struct Point {
  double x, y, z;
};


//Kd Tree Node
struct Node{
	double x, y, z;
	int index;
	Node *left;
	Node *right;
	Node(double xx, double yy, double zz, int i){
		x = xx;
		y = yy;
		z = zz;
		index = i;
		left = NULL;
		right = NULL;
	}	

};
//Inserts a new node into the kd tree
//bool X says Are we in the X dimension? If not, compare on Y.
Node* KdBuild(Node *root, double xx, double yy, double zz, bool X, int i){
	//Like the old BST inserts
	if(root == NULL) return new Node(xx, yy, zz, i);
	//If on the X dimension, compare on the X dimension. Else, Y
	if(X){
		if(root->x > xx) root->left = KdBuild(root->left, xx, yy, zz, false, i);
		else root->right = KdBuild(root->right, xx, yy, zz, false, i);
	}else{
		if(root->y > yy) root->left = KdBuild(root->left, xx, yy, zz, true, i);
		else root->right = KdBuild(root->right, xx, yy, zz, true, i);
	}

	return root;
}

// All the points in our LIDAR data set
vector<Point> all_points;

Point mins, maxes; // highest and lowest values in dataset
Point winmin, winmax; // corners of window being displayed on screen

// Size of our window on screen
double window_xsize = 1000, window_ysize = 800;

// Source and destination nodes for shortest path calculation
int source_node = -1;
int destination_node = -1;

priority_queue<pair<double, int> > Neighbors;
Node *root;
//TODO
//Nearest Neighbor function takes in two values and finds the nearest neighbors 
void NN(Node *root, double xx, double yy, bool X){

	if(root == NULL) return;
	//Based on only x and y characteristics
	double distance = sqrt((pow((xx - root->x), 2.0) + pow((yy - root->y), 2.0)));
	Neighbors.push(make_pair(distance,root->index));

	//If the queue is over 10, pop off the worst
	if(Neighbors.size() > 10) Neighbors.pop();
	//bool to say if we went to the right or left so the recursive layers know where they went before
	bool right;
	if(X){
		//Recurse left or right depending
		if(root->x > xx){
			 NN(root->left, xx, yy, false);
			 right = false;
		}else{
			NN(root->right, xx, yy, false);
			right = true;
		}
		//If it is worth it to recurse on the other subtree, do so
		if(Neighbors.top().first > abs(xx - root->x)){
			if(right) NN(root->left, xx, yy, false);
			else NN(root->right, xx, yy, false);
		}

	}else{
		if(root->y > yy){
			NN(root->left, xx, yy, true);
			right = false;
		}
		else{
			NN(root->right, xx, yy , true);
			right = true;
		}
		if(Neighbors.top().first > abs(yy - root->y)){
			if(right) NN(root->left, xx, yy, true);
			else NN(root->right, xx, yy, true);
		}

	}
	

}
//Helper functions that return the distance between points and a slopecheck
double Distance(double xx, double yy, double zz, double x, double y, double z){
	return sqrt((pow((xx - x), 2.0) + pow((yy - y), 2.0) + pow((zz - z),2.0 )));

}

double SlopeCheck(double xx, double yy, double zz, double x, double y, double z){
	return ((zz - z)/(sqrt(pow((xx-x),2.0)+pow((yy-y),2.0))));
}



map<int, double> dists;
map<int, int> Pred;
bool Path;

//Modified Dijkstra
bool dijkstra(){
	//Bool of Path to say if we found one
	Path = false;
	//Set to store points
	set<pair<int, double> > S;
	double infinity = 999999999;
	for(int i = 0; i < all_points.size(); i++) dists[i] = infinity;
	dists[source_node] = 0.0;
	S.insert(make_pair(0.0, source_node));
	
	while(!S.empty()){
		int to_visit = S.begin()->second;

		NN(root, all_points[to_visit].x, all_points[to_visit].y,true);
		S.erase(S.begin());
		if(to_visit == destination_node){ 
			Path = true;
			return true;
		}
		//Go to each neighbor and see if the path is viable
		// Either if the slope is not too steep and the path is short
		while(!Neighbors.empty()){
			double x = all_points[to_visit].x;
			double y = all_points[to_visit].y;
			double z = all_points[to_visit].z;
			double xx = all_points[Neighbors.top().second].x;
			double yy = all_points[Neighbors.top().second].y;
			double zz = all_points[Neighbors.top().second].z;
			if(SlopeCheck(xx, yy, zz, x, y, z) > 1){
				Neighbors.pop();
				continue;
			}else if(dists[Neighbors.top().second] > dists[to_visit] + Distance(xx, yy, zz, x, y, z)){
				dists[Neighbors.top().second] = dists[to_visit] + Distance(xx, yy, zz, x, y, z);
 				S.insert(make_pair(dists[Neighbors.top().second], Neighbors.top().second));
				Pred[Neighbors.top().second] = to_visit;
			}
						
			Neighbors.pop();
		}
	}

	return false;
}

// Called whenever a key is pressed
void keyhandler(int key)
{
  double x_range = winmax.x - winmin.x;
  double y_range = winmax.y - winmin.y;  
  double x_center = winmin.x + x_range/2;
  double y_center = winmin.y + y_range/2;

  if (key == KEY_LEFT) { winmin.x -= x_range/10; winmax.x -= x_range/10; }
  if (key == KEY_RIGHT) { winmin.x += x_range/10; winmax.x += x_range/10; }
  if (key == KEY_UP) { winmin.y += y_range/10; winmax.y += y_range/10; }
  if (key == KEY_DOWN) { winmin.y -= y_range/10; winmax.y -= y_range/10; }

  if (key == '=') { // Zoom in
    winmin.x = x_center - x_range / 2 * 0.8;
    winmax.x = x_center + x_range / 2 * 0.8;
    winmin.y = y_center - y_range / 2 * 0.8;
    winmax.y = y_center + y_range / 2 * 0.8;
  }
  if (key == '-') { // Zoom out
    winmin.x = x_center - x_range / 2 / 0.8;
    winmax.x = x_center + x_range / 2 / 0.8;
    winmin.y = y_center - y_range / 2 / 0.8;
    winmax.y = y_center + y_range / 2 / 0.8;
  }

  if (key == 'n') {
    //TODO
    // TBD: find the 10 nearest neighbors of (x_center, y_center)
    // Then store them in a global structure so they can be highlighted in the rendering code
    NN(root, x_center, y_center, true);
  }
  
  if (key == 's') { // set source
    //TODO
    // TBD: set source_node = nearest neighbor in (x,y) plane to (x_center, y_center)
    NN(root, x_center, y_center, true);

    while(!Neighbors.empty()){
	source_node = Neighbors.top().second;   
        Neighbors.pop();
    }
    cout << "Set source node = " << source_node << "\n";
  }
  if (key == 'd') { // set destination and compute shortest path
     //TODO
     // TBD: set destination_node = nearest neighbor in (x,y) plane to (x_center, y_center)
     NN(root, x_center, y_center, true);
     while(!Neighbors.empty()){
	destination_node = Neighbors.top().second;   
        Neighbors.pop();
    }    
    cout << "Set destination node = " << destination_node << "\n";
  }
  if ((key == 's' || key == 'd') && source_node != -1 && destination_node != -1) {
    cout << "Computing shortest path from source to destination...\n";
    //TODO
    // TBD: compute shortest path from source to destination and record it so it can be visualized
    // if no path (e.g., all paths would require stepping at more than a 45 degree incline, print "No path"
    // if there is a path, print its length in feet
	if(dijkstra()){
		cout << "Path found: distance is: "<<dists[destination_node] << endl;

	}else{	cout << "NOOOOOOOOOO PAAAAAATH" << endl;}

 
  if (key == 'q') exit(0);
}
}



// Returns where on the screen to plot a point, offsetting it slightly based on elevation
// from its usual (x,y) location to make tall things look tall
pair<double,double> get_point_screen_location(Point &p)
{
  double x = (p.x - winmin.x) / (winmax.x - winmin.x) * window_xsize;
  double y = window_ysize - (p.y - winmin.y) / (winmax.y - winmin.y) * window_ysize;
  double offset = (p.z - 700) / 5; // how much we offset pixel to emphasize its height
  return make_pair(x-offset, y-offset);
}

// Called whenever we need to re-render the current window
void render(void)
{
  // Feel welcome to turn off this message if you want...
  cout << "Rendering (" << winmin.x << "," << winmin.y << ") - (" << winmax.x << "," << winmax.y << ")\n";

  for (Point &p : all_points) {
    pair<double, double> loc = get_point_screen_location(p);
    double x = loc.first, y = loc.second;
    if (x >= 0 && y >= 0 && x < window_xsize && y < window_ysize) {
      double color = min(1.0, max(0.0, (p.z - 700) / 80.0)); // color in range [0,1] based on height
      set_color (color, 0.8, 0.5);
      draw_pixel (x, y);
    }
  }

  // Draw small crosshairs at center of window
  set_color(1,1,1);
  draw_line(window_xsize/2-3, window_ysize/2, window_xsize/2+3, window_ysize/2);
  draw_line(window_xsize/2, window_ysize/2-3, window_xsize/2, window_ysize/2+3);

  // TBD: highlight the points that were returned in response to asking for nearest neighbors
  set_color(0,0,255);
  while(!Neighbors.empty()){

	pair<double, double> Pony = get_point_screen_location(all_points[Neighbors.top().second]);	

	draw_line(Pony.first-5, Pony.second-5, Pony.first+5, Pony.second+5);
	draw_line(Pony.first-5, Pony.second+5, Pony.first+5, Pony.second-5);
 	Neighbors.pop();
  }
  //TODO
  // TBD: plot a sequence of line segments depicting the shortest path, if one has been computed
	if(Path && source_node != -1 && destination_node != -1){
			pair<double, double> SS = get_point_screen_location(all_points[source_node]);
			pair<double, double>  DD = get_point_screen_location(all_points[destination_node]);
		draw_line(SS.first-5, SS.second-5, SS.first+5, SS.second+5);
		draw_line(SS.first-5, SS.second+5, SS.first+5, SS.second-5);		
		draw_line(DD.first-5, DD.second-5, DD.first+5, DD.second+5);
		draw_line(DD.first-5, DD.second+5, DD.first+5, DD.second-5);		
		int current = destination_node;
		while(current != source_node){
			pair<double, double> Previously = get_point_screen_location(all_points[Pred[current]]);
			pair<double, double>  Cur = get_point_screen_location(all_points[current]);
			set_color(0,0,255);
			draw_line(Cur.first, Cur.second, Previously.first, Previously.second);
			current = Pred[current];
		}
	}


}

int main(int argc, char *argv[])
{
  // Read in all the data
  ifstream fin ("points.txt");
  Point p;
  int count = 0;
  while (fin >> p.x >> p.y >> p.z)
    all_points.push_back(p);
    
  // Find initial view window corner points
  mins = maxes = all_points[0];
  for (auto &p : all_points) {
    mins.x = min(mins.x, p.x);
    mins.y = min(mins.y, p.y);
    mins.z = min(mins.z, p.z);
    maxes.x = max(maxes.x, p.x);
    maxes.y = max(maxes.y, p.y);
    maxes.z = max(maxes.z, p.z);
  }
  // Re-adjust y to match aspect ratio of window
  winmin = mins; winmax = maxes;
  winmax.y = winmin.y + (winmax.x - winmin.x) * window_ysize / window_xsize;

  //TODO
  // TBD... build kd-tree here
  // Normally you'd want to insert them in random order but they are already randomly shuffled, so no need to shuffle again
  
  //So, we need to alt between comparing x and comparing y. Maybe pass a bool for each?
  root = NULL;
  int size = all_points.size();
  for(int i = 0; i < size; i++)
	root = KdBuild(root, all_points[i].x,all_points[i].y,all_points[i].z, true, i);

  

  // Launch graphics; all remaining interaction is via callback to render and keyhandler function
  init_graphics(argc, argv, window_xsize, window_ysize, render, keyhandler);
  return 0;
}
