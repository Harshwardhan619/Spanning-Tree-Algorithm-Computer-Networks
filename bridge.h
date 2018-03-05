#include <iostream>
#include  <vector>
#include <string>
#include <sstream>
using namespace std;

class bridge
{
public:
	bridge();
	~bridge();

	bridge(string str){
		// sample str = "B1: A G B"
		name = str.substr(0,2);
		distance = 0;
		root = name;
		from_bridge = name;
		for (int i = 4; i < str.length();i = i+2){ 
			vector<string> v (2, "DP");
			v[0] = str.substr(i,1);
			LAN_connected.push_back(v);
		}
	}

	void printbridge (){
		cout<<name<<": ";
		for(int i = 0 ; i < LAN_connected.size() ;i++){
			cout<<LAN_connected[i][0]<<"-"<<LAN_connected[i][1]<<" ";
		}
		cout << endl;
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

	string get_msg_host_from_msg(string token){
		return token.substr(6,1);
	}

	int find_LAN(string LAN_name){
		for(int i = 0; i < LAN_connected.size(); i++){
			if(LAN_name == LAN_connected[i][0]) return i;
		}
		return -1;
	}

	// for generating and forwarding msg
	string generate_msg(){

		std::stringstream ss;
		// convert to string
		ss << distance;
		string dist;
		ss >> dist;
		string message = "";

		if (root == name){
			for(int i = 0 ; i < LAN_connected.size() ;i++){
				if(LAN_connected[i][1] == "DP"){

					message = message + root + "," + name + "," + LAN_connected[i][0] + "," + dist + "|";
				}
				else if(LAN_connected[i][1] == "RP"){
					message = "";
					break;
				}
			}
			message = message.substr(0,message.length() - 1 );
		} else {
			message = bridge_msg;
		}
		return message;
	}

	// check if msg is for given bridge 
	bool msgfor(string str){	
		if(str != ""){
			for(int i = 0 ; i < LAN_connected.size() ;i++){
				if(LAN_connected[i][0] == get_msg_host_from_msg(str) && name != str.substr(0,2) && name != str.substr(3,2) && LAN_connected[i][1] != "NP") return true;
			}
		}
		return false;
	}

	void change_port_status(string LAN, string status){
		if(status == "RP"){
			for(int i = 0 ; i < LAN_connected.size() ;i++){
				if(LAN_connected[i][1] == "RP") LAN_connected[i][1] = "DP";
			}
		}
		for(int i = 0 ; i < LAN_connected.size() ;i++){
			if(LAN_connected[i][0] == LAN) LAN_connected[i][1] = status;
		}
	}

	void do_operations(vector<string> v){
		int temp = distance;

		for(int i = 0; i < v.size(); i++){
			// rule 1: if msg root smaller then assign than to root;
			if(int(v[i][1]) < int(root[1])){
				root = v[i].substr(0,2);
				distance = get_dist_from_msg(v[i]) + 1;
				change_port_status(get_msg_host_from_msg(v[i]), "RP");
				from_bridge = v[i].substr(3,2);
			}
			// rule 2: same root -> smaller distance
			else if(root == v[i].substr(0,2) && get_dist_from_msg(v[i]) < temp){
				distance = get_dist_from_msg(v[i]) + 1;
				change_port_status(get_msg_host_from_msg(v[i]), "RP");
				from_bridge = v[i].substr(3,2);
			} 
			// rule 3: same root | same distance -> smaller sender
			else if(root == v[i].substr(0,2) && get_dist_from_msg(v[i]) == temp && int(v[i][4]) < int(from_bridge[1])) {
				distance = get_dist_from_msg(v[i]) + 1;
				change_port_status(get_msg_host_from_msg(v[i]), "RP");
				from_bridge = v[i].substr(3,2);
			}
			
		}
	}

	void process_message(string message){ 
		cout<<name<<endl;
		size_t p = 0;
		string token;
		vector<string> v;

		while ((p = message.find("|")) != string::npos) {
		    token = message.substr(0, p);
		    if(msgfor(token)){
		    	v.push_back(token);
		    }
		    message = message.substr(p + 1);
		}
		if(msgfor(message)){
		    cout << message << endl;
		   	v.push_back(message);
		}

		for(int i =0 ;i<v.size();i++){
			cout<<v[i]<<"  --  ";
		}
		cout << root<<endl;
		do_operations(v);

		// process and store next message.
		bridge_msg = "";

		for(int i = 0 ; i < v.size() ;i++){
			v[i][4] = name[1];

			std::stringstream ss;
			// convert to string
			ss << distance;
			string dist;
			ss >> dist;

			v[i] = v[i].substr(0,8) + dist;
			int num = find_LAN(get_msg_host_from_msg(v[i]));

			if(LAN_connected[num][1] == "RP"){
				// Logic for forwarding

				for(int j = 0 ;j < LAN_connected.size();j++){
					if(LAN_connected[j][1] == "DP"){
						string temp = v[i];
						temp[6] = LAN_connected[j][0][0];
						bridge_msg = bridge_msg + temp + "|";
					}
				}
			}
		}
		bridge_msg = bridge_msg.substr(0,bridge_msg.length() - 1 );
		printbridge();
		cout<<bridge_msg<<endl;
		// cout << message << endl;
	}

	string name;
	string bridge_msg;
	int distance;
	string root;
	string from_bridge;
	vector< vector<string> > LAN_connected;
};