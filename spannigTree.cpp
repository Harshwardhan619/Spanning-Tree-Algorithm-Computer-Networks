#include <iostream>
#include <string>
#include <vector>
#include "bridge.h"
using namespace  std;


bool checkspanning(string msg, string prevmsg){
	if( msg != "" && msg == prevmsg){
		return true;
	}
	else return false;
}

int find_bridge(string bridge_name, vector<bridge*> v){
	for(int i = 0; i < v.size(); i++){
		if(bridge_name == v[i]->name)return i;
	}
	return -1;
}

int get_dist_from_msg(string token){
	string dist = token.substr(8);
	std::stringstream ss;
	// convert to string
	ss << dist;
	int num;
	ss >> num;
	return num;
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
 	string msg = "", prevmsg = "";
	while(not(checkspanning(msg,prevmsg))) {
		prevmsg = msg;
		msg = "";

		// For message generations.
		for(int i = 0; i < bridgenumber; i++){
			msg = msg +  bridgearray[i]->generate_msg() + "|"; 
		}
		msg = msg.substr(0,msg.length() - 1 );
		cout <<msg<<endl;
		simnum++;
		
		// For processing message at some host.
		// step-1 tokenize the string.
		size_t p = 0;
		string message = msg;
		string token;
		vector<string> v;
		while ((p = message.find("|")) != string::npos) {
		    token = message.substr(0, p);
		    v.push_back(token);
		    message = message.substr(p + 1);
		}

		message = message.substr(p + 1);
		v.push_back(message);

		// now v is a vector of all messages. Doing processing at all HOSTS.

		for(int i = 0; i<v.size(); i++){
			for(int j = i + 1; j < v.size();j++){
				// if messages are for same host.
				if(v[i].substr(6,1) == v[j].substr(6,1)){
					if(v[j].substr(0,2) == v[i].substr(0,2) && get_dist_from_msg(v[i]) != get_dist_from_msg(v[j])){
						if(get_dist_from_msg(v[i]) < get_dist_from_msg(v[j])){
							int num = find_bridge(v[j], bridgearray); 
							if(num != -1){
								bridgearray[num]->change_port_status(v[j].substr(6,1), "NP");
								v[j][0] = 'C';
							}
						}
						else {
							int num = find_bridge(v[i], bridgearray);
							if(num != -1){
								bridgearray[num]->change_port_status(v[i].substr(6,1), "NP");
								v[i][0] = 'C';
							}
						}
					}
					else if(v[j].substr(0,2) == v[i].substr(0,2) && get_dist_from_msg(v[i]) == get_dist_from_msg(v[j]) && int(v[i][4]) != int(v[j][4])){
						if(int(v[i][4]) < int(v[j][4])){
							int num = find_bridge(v[j], bridgearray);
							bridgearray[num]->change_port_status(v[j].substr(6,1), "NP");
							v[j][0] = 'C';
						}
						else {
							int num = find_bridge(v[i], bridgearray);
							bridgearray[num]->change_port_status(v[i].substr(6,1), "NP");
							v[i][0] = 'C';
						}
					}
				}
			}
		}

		// For message processing at bridge.
		for(int i = 0; i < bridgenumber; i++){
			bridgearray[i]->process_message(msg);
		}
		// break;

		for (int i = 0 ; i < bridgearray.size() ;i++){
			bridgearray[i]->printbridge();
		}
	}

	for (int i = 0 ; i < bridgearray.size() ;i++){
		bridgearray[i]->printbridge();
	}
}