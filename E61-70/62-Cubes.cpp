#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "62-Cubes.h"

using namespace std;

void Cubes::Increase(vector<char> target, vector<char> source) {
	vector<char>::iterator i;
	int size = source.size();

	if (size == 1) {
		vector<char> targetNew(target);
		targetNew.push_back(source[0]);
		string str(targetNew.begin(), targetNew.end());
		unsigned long value = atoi(str.c_str());
		if (permutes.find(value) == permutes.end())
			permutes.insert(value);
	}
	else
		for (int n1 = 0; n1 < size; n1++) {
			vector<char> targetNew(target);
			targetNew.push_back(source[n1]);
			vector<char> sourceNew;
			for(int n2 = 0; n2 < size; n2++)
				if (n2 != n1)
					sourceNew.push_back(source[n2]);
			Increase(targetNew, sourceNew);
		}
}

set<unsigned long> Cubes::Search(unsigned long n) {
	set<unsigned long> sets;
	set<unsigned long>::iterator i;

	if (!permutes.empty())
		permutes.clear();

	string s = to_string(n);
	if (s.length() > digits) {
		cout << " <digits " << digits << ", number " << cubes.size() << "> ";
		cubes.clear();
		digits = s.length();
	}

	vector<char> v(s.begin(), s.end());
	vector<char> vectors;

	Increase(vectors, v);

	for (i = permutes.begin(); i != permutes.end(); i++)
		if (cubes.find(*i) != cubes.end())
			sets.insert(*i);

	return sets;
}

void Cubes::Start() {
	int range = 5;
	cout << "Problem 62 : Cubic permutations. Search range " << range << "." << endl;

	set<unsigned long> result;
	unsigned long cube;

	for (unsigned long n = 1; n < 10000; n++) {
		if ((n % 100) == 0) cout << n << " ";
		if ((result = Search(cube = n * n * n)).size() == range) {
			result.insert(cube);
			break;
		}
		cubes.insert(cube);
	}

	set<unsigned long>::iterator i;
	cout << endl;
	for (i = result.begin(); i != result.end(); i++)
		cout << *i << " ";
	cout << endl;

	bool start = true;
	for (i = result.begin(); i != result.end(); i++) {
		if (start) {
			cube = *i;
			start = false;
		}
		else if (*i < cube)
			cube = *i;
	}
	cout << cube << endl;
	
	cout << "finish" << endl;
}