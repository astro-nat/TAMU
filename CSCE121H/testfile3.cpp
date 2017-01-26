#include "std_lib_facilities_4.h"

struct Set {
private:
	vector<int> elts;
public:
	vector<int> getelts() { return elts; }
	void insert(int a) { elts.push_back(a);}
	
	const bool is_in(int a) {
		for (int i = 0; i < elts.size(); ++i)
			if (elts[i] == a) return true;
		return false;
}
};

Set union_op(Set s1, Set& s2) {
	Set s3 = s1;
	vector<int> temp = s2.getelts();
	for(int i = 0; i < temp.size(); ++i){
		int cur = temp[i];
	if (!s1.is_in(cur)) s3.insert(cur);
}
return s3;
}

int main(){
Set set1;
set1.insert(2);
set1.insert(4);
set1.insert(6);
Set set2;
set2.insert(3);
set2.insert(6);
set2.insert(9);
Set set3;
set3 = union_op(set1,set2);
}
