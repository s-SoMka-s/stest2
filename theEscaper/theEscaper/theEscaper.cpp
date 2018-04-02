#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <cmath>
using namespace std;


pair<int, int> coord(int x, int y, int x1, int y1) {
	int min_x, min_y, distance1, distance2, distance3, distance4;
	distance1 = sqrt(pow(x1 - x - 1, 2) + pow(y1 - y, 2));
	distance2 = sqrt(pow(x1 - x + 1, 2) + pow(y1 - y, 2));
	distance3 = sqrt(pow(x1 - x, 2) + pow(y1 - y - 1, 2));
	distance4 = sqrt(pow(x1 - x, 2) + pow(y1 - y + 1, 2));
	if (distance1 < distance2)
		if (distance1 < distance3) {
			if (distance1 < distance4) {
				min_x = x + 1;
				min_y = y;
			}
			else {
				min_x = x;
				min_y = y - 1;
			}
		}

	if (distance2 < distance1)
		if (distance2 < distance3) {
			if (distance2 < distance4) {
				min_x = x - 1;
				min_y = y;
			}
			else {
				min_x = x;
				min_y = y - 1;
			}
		}

	if (distance3 < distance1)
		if (distance3 < distance2) {
			if (distance3 < distance4) {
				min_x = x;
				min_y = y-1;
			}
			else {
				min_x = x;
				min_y = y - 1;
			}
		}

	if (distance4 < distance1)
		if (distance4 < distance2) {
			if (distance4 < distance3) {
				min_x = x;
				min_y = y-1;
			}
			else {
				min_x = x;
				min_y = y + 1;
			}
		}


	return make_pair(min_y, min_x);
}

int main()
{
	srand(unsigned(time(NULL)));
	ifstream input("worldMap.txt");
	int n;
	input >> n;
	vector <vector <int>> world(n, vector<int>(n));
	input.close();
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			world[y][x] = 0;
	int catcher_x = rand() % (n - 2);
	int catcher_y = rand() % (n - 2);
	

	int escaper_x = rand() % (n - 1);
	int escaper_y = rand() % (n - 1);
	world[catcher_y][catcher_x] = 1;
	world[escaper_y][escaper_x] = 2;

	ofstream output("worldMap.txt");
	output.clear();
	output << n << endl;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			output << world[y][x] << " ";
		}
		output << endl;
	}

	while (escaper_x != catcher_x || escaper_y != catcher_y) {
		pair<int, int> yx;
		yx = coord(catcher_x, catcher_y, escaper_x, escaper_y);
		catcher_y = yx.first;
		catcher_x = yx.second;
	
		world[catcher_y][catcher_x] = 1;
		world[escaper_y][escaper_x] = 2;

		ofstream output("worldMap.txt");
		output.clear();
		output << n << endl;
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				output << world[y][x] << " ";
			}
			output << endl;
		}
	}
	return 0;
}