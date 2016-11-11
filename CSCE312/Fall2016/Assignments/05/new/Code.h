#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <bitset>
#include <map>

using namespace std;

class Code {

	map<string,int> dest_table = {
		{"null",0},
		{"M",1},
		{"D",2},
		{"MD",3},
		{"A",4},
		{"AM",5},
		{"AD",6},
		{"AMD",7}
	};
	
	map<string,int> comp_table_if_1 = {
		{"M",16+32},
			{"!M",1+16+32},
				{"-M",1+2+16+32},
					{"M+1",1+2+4+16+32},
						{"M-1",2+16+32},
							{"D+M",2},
								{"D-M",1+2+16},
									{"M-D",1+2+4},
										{"D&M",0},
											{"D|M",1+4+16}
	};
	
	map<string,int> comp_table_if_0 = {
		{"0",42},
		{"1",63},
		{"-1",32+16+8+2},
		{"D",4+8},
		{"A",16+32},
		{"!D",1+4+8},
		{"!A",1+16+32},
		{"-D",1+2+4+8},
		{"-A",1+2+16+32},
		{"D+1",1+2+4+8+16},
		{"A+1",1+2+4+16+32},
		{"D-1",2+4+8},
		{"A-1",2+16+32},
		{"D+A",2},
		{"D-A",1+2+16},
		{"A-D",1+2+4},
		{"D&A",0},
		{"D|A",1+4+16}
	};
	
	map<string, int> jump_table = {
		{"null",0},
		{"JGT",1},
		{"JEQ",2},
		{"JGE",3},
		{"JLT",4},
		{"JNE",5},
		{"JLE",6},
		{"JMP",7}
	};
	
	int a = 0;
	
public:
	bitset<3> dest(string mnem) {
		cout << "dest : " << dest_table.at(mnem);
		return bitset<3>(dest_table.at(mnem));
	}

	bitset<7> comp(string mnem) {
		// change with a = 0 or 1
		if(comp_table_if_1.find(mnem) != comp_table_if_1.end()) {
			return bitset<7>(64+comp_table_if_1[mnem]);
		}
		else if (comp_table_if_0.find(mnem) != comp_table_if_0.end()) {
			return bitset<7>(comp_table_if_0[mnem]); 
		}
		else return 0000000;
	}

	bitset<3> jump(string mnem) {
		if(jump_table.find(mnem) != jump_table.end()) {
			return bitset<3>(jump_table.at(mnem));
		}
		else return 000;
	}
};

#endif