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

	string generate_msg(){
		int RP = 0;
		std::stringstream ss;
		// convert to string
		ss << distance;
		string dist;
		ss >> dist;
		string message = "";
		for(int i = 0 ; i < LAN_connected.size() ;i++){
			if(LAN_connected[i][1] == "DP"){

				message = message + root + "," + name + "," + LAN_connected[i][0] + "," + dist + "|";
			}
			else if(LAN_connected[i][1] == "RP"){
				RP = 1;
				message = "";
				break;
			}
		}
		message = message.substr(0,message.length() - 1 );
		return message;
	}

	// check if msg is for given bridge 
	bool msgfor(string str){	
		for(int i = 0 ; i < LAN_connected.size() ;i++){
			if(LAN_connected[i][0] == get_msg_host_from_msg(str) && name != str.substr(0,2)) return true;
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
		for(int i = 0; i < v.size(); i++){
			// rule 1: if msg root smaller then assign than to root;
			if(int(v[i][1]) < int(root[1])){
				root = v[i].substr(0,2);
				distance = get_dist_from_msg(v[i]) + 1;
				change_port_status(get_msg_host_from_msg(v[i]), "RP");
				from_bridge = v[i].substr(3,2);
			}
			// rule 2: 
			else if(root == v[i].substr(0,2) && get_dist_from_msg(v[i]) < distance){
				distance = get_dist_from_msg(v[i]) + 1;
				change_port_status(get_msg_host_from_msg(v[i]), "RP");
				from_bridge = v[i].substr(3,2);
			} 
			// rule 3: 
			else if(root == v[i].substr(0,2) && get_dist_from_msg(v[i]) == distance && int(v[i][4]) < int(from_bridge[1])) {
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
		    	cout << token << endl;
		    	v.push_back(token);
		    }
		    message = message.substr(p + 1);
		}
		if(msgfor(message)){
		    cout << message << endl;
		   	v.push_back(message);
		}

		do_operations(v);
		printbridge();
		// cout << message << endl;
	}

	string transfer_message(){
		return "";
	}

	string name;
	string bridge_msg;
	int distance;
	string root;
	string from_bridge;
	vector< vector<string> > LAN_connected;
};