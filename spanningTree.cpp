#include <iostream>
#include <string>
#include <vector>
#include "bridge.h"
#include <algorithm>
using namespace  std;


bool checkspanning(string msg, string prevmsg){
	if( msg != "" && msg == prevmsg){
		return true;
	}
	else return false;
}

int find_bridge(string message, vector<bridge*> v){
	for(int i = 0; i < v.size(); i++){
		if(message.substr(3,2) == v[i]->name)return i;
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

bool if_present(vector< vector<string> >host, string temp){
	for(int i = 0;i<host.size();i++){
		if(host[i][0] == temp) return true;
	}
	return false;
}

// string LAN(vector< vector<string> >host, string s){
// 	for(int i = ; i < host.size();i++){
// 		for(int j = 1; j < host[i].size; j++){
// 			if(host[i][j] == s) return host[i][0];
// 		}
// 	}
// }


// // SOME functions I was doing for part 2 of the assignment.

// void transfers_message(vector< vector<string> > host, vector<bridge*> bridgearray, string sender, string reciever, string from, string host_send, string host_recieve){
// 	for(int i = 0; i < bridgearray; i++){
// 		bool x = false;
// 		for(int i = 0; i < bridgearray->LAN_connected.size();i++){
// 			if(sender == bridgearray->LAN_connected[0]) x = true;
// 		}

// 		if(x){
// 			// bridgearray[i]->make_entry(sender, host_send);
// 		}
// 	}
// }

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

	std::sort(bridgestrings.begin(), bridgestrings.end());

	string root_port = bridgestrings[0].substr(0,2);

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

		while(msg[msg.length() - 1] == '|')
			msg = msg.substr(0,msg.length() - 1 );

		// cout <<msg<<endl;
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

		// now v is a vector of all messages. Doing processing at all LANs.

		for(int i = 0; i<v.size(); i++){
			for(int j = i + 1; j < v.size();j++){

				//if messages are for same host.
				if(v[i].substr(6,1) == v[j].substr(6,1)){
					if(v[j].substr(0,2) == root_port && v[j].substr(0,2) == v[i].substr(0,2) && get_dist_from_msg(v[i]) != get_dist_from_msg(v[j])){
						if(get_dist_from_msg(v[i]) < get_dist_from_msg(v[j]) && v[i][6] != '*'){
							int num = find_bridge(v[j], bridgearray); 
							if(num != -1){
								bridgearray[num]->change_port_status(v[j].substr(6,1), "NP");
								v[j][6] = '*';
							}
						}
						else if(get_dist_from_msg(v[i]) > get_dist_from_msg(v[j]) && v[i][6] != '*'){
							int num = find_bridge(v[i], bridgearray);
							if(num != -1){
								bridgearray[num]->change_port_status(v[i].substr(6,1), "NP");
								v[i][6] = '*';
							}
						}
					} else if(v[j].substr(0,2) == root_port && v[j].substr(0,2) == v[i].substr(0,2) && get_dist_from_msg(v[i]) == get_dist_from_msg(v[j]) && v[i].substr(3,2) != v[j].substr(3,2)){

						if(int(v[i][4]) < int(v[j][4]) && v[i][6] != '*'){
							int num = find_bridge(v[j], bridgearray); 
							if(num != -1){
								bridgearray[num]->change_port_status(v[j].substr(6,1), "NP");
								v[j][6] = '*';
							}
						}
						else if(int(v[i][4]) > int(v[j][4]) && v[i][6] != '*'){
							int num = find_bridge(v[i], bridgearray);
							if(num != -1){
								bridgearray[num]->change_port_status(v[i].substr(6,1), "NP");
								v[i][6] = '*';
							}
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
		// cout<<endl;
	}

	vector< vector<string> > host;
	for (int i = 0 ; i < bridgearray.size() ;i++){

		bridgearray[i]->printbridge();

		// ========================================================================
		// Part 1 of the assignment ends here
		// ========================================================================

		// vector< vector<string> > temp = bridgearray[i]->LAN_connected;
		// for(int j = 0; j < temp.size(); j++){
		// 	if(!if_present(host, temp[j][0])){
		// 		vector<string> temp2 (1,temp[j][0]);
		// 		host.push_back(temp2);
		// 	}
		// }
	}
	// std::sort(host.begin(), host.end());

	// std::vector<string> hoststrings (host.size());
	// for(int i = 0; i < host.size(); i++){
	// 	//input line of bridge
	// 	std::getline(cin, hoststrings[i]);
	// 	// cout<<hoststrings[i]<<" ";
	// }

	// for(int i = 0; i< hoststrings.size();i++){
	// 	 for (int i = 4; i < hoststrings[i].length();i = i+2){ 
	// 		host[i].push_back(hoststrings[i].substr(i,1));
	// 	}
	// }

	// int no_of_transfers;
	// cin >> no_of_transfers;
	
	// string transfers[no_of_transfers][2];

	// for(int i = 0; i< no_of_transfers; i++){
	// 	string temp1, temp2;
	// 	cin >> temp1 >> temp2;
	// 	transfers[i][0] = temp1;
	// 	transfers[i][1] = temp2;
	// }


	// for(int i = 0; i < no_of_transfers;i++){
	// 	for (int i = 0 ; i < bridgearray.size() ;i++){
	// 		transfers_message(host, bridgearray, LAN(host, transfers[i][0]), LAN(host, transfers[i][1]), "ALL", transfers[i][0], transfers[i][1]);
	// 	}
	// }
}