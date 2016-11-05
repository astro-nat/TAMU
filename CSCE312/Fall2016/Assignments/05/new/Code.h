#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <bitset>
#include <map>

using namespace std;

class Code {

	const map<string,int> dest_table = {
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
	
public:
	bitset<3> dest(string mnem) {
		return bitset<3>(dest_table.at(mnem));
	}

	bitset<7> comp(string mnem) {
		// change with a = 0 or 1
		//return bitset<7>(comp_table.at(mnem));
	}

	bitset<3> jump(string mnem) {
		//return bitset<3>(jump_table.at(mnem));
	}
};

#endif