#include <iostream>
#include <string>
#include <vector>
#include "bridge.h"
using namespace  std;


bool checkspanning(vector<bridge*> bridgearray){
	return true;
}

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

	// count for simulation number
	int simnum = 0;
 
	while(checkspanning(bridgearray)){
		string msg = "";
		for(int i = 0; i < bridgenumber; i++){
			msg = msg +  bridgearray[i]->generate_msg() + "|"; 
		}
		msg = msg.substr(0,msg.length() -1 );
		cout <<msg<<endl;
		simnum++;
		
		for(int i = 0; i < bridgenumber; i++){
			bridgearray[i]->process_message(msg);
		}
		break;
	}

	for (int i = 0 ; i < bridgearray.size() ;i++){
		bridgearray[i]->printbridge();
	}
}