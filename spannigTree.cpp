#include <iostream>
#include <string>
#include <vector>
#include "bridge.h"
using namespace  std;

int main(){
	int trace,bridgenumber;
	string temp;
	cin >> trace >> bridgenumber;
	vector<string> bridgestrings (bridgenumber);

	vector<bridge*> bridgearray;
	// temp for the newline // no use
	std::getline(cin, temp);
	for(int i = 0; i < bridgenumber; i++){
		//input line of bridge
		std::getline(cin, bridgestrings[i]);

		bridge * tempbridge = new bridge(bridgestrings[i]);
		bridgearray.push_back(tempbridge);
	}

	for (int i = 0 ; i < bridgearray.size() ;i++){
		bridgearray[i]->printbridge();
	}
}