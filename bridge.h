#include <iostream>
#include  <vector>
#include <string>
using namespace std;

class bridge
{
public:
	bridge();
	~bridge();

	bridge(string str){
		// sample str = "B1: A G B"
		name = str.substr(0,2);
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
	string name;
	vector< vector<string> > LAN_connected;
};