#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	string input;
	cout << "Enter a string: " << endl;
	getline(cin,input);

	stringstream ss(input);
	string tempString;
	vector<string> words;
	while (ss >> tempString)
	{
		words.push_back(tempString);
	}

	reverse(words.begin(),words.end());
	
	for(int i = 0; i < words.size(); i++)
	{
		cout << words[i] << " ";
	}

	cin.ignore();
	return 0;

}
