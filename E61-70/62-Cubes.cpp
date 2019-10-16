#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <chrono>

#include "62-Cubes.h"

using namespace std;

void Cubes::Increase(vector<char> target, vector<char> source, bool equal) {
	vector<char>::iterator i;
	int size = source.size();

	if (size == 1) {
		vector<char> targetNew(target);
		targetNew.push_back(source[0]);
		string str(targetNew.begin(), targetNew.end());
		unsigned long value = atol(str.c_str());

		if (permutes.find(value) == permutes.end() && (!equal || bas[bas.size() - 1] != source[0]))
			permutes.insert(value);
	}
	else
		for (int n1 = 0; n1 < size; n1++) {

			if(target.size() < 1 && source[n1] == '0')
				continue;
			if(equal && source[n1] > bas[target.size()])
				continue;

			vector<char> targetNew(target);
			targetNew.push_back(source[n1]);
			vector<char> sourceNew;
			for(int n2 = 0; n2 < size; n2++)
				if (n2 != n1)
					sourceNew.push_back(source[n2]);
			Increase(targetNew, sourceNew, equal && source[n1] == bas[target.size()]);
		}
}

bool Cubes::valid(unsigned long long cube){
	return cube > 1080000000 && cube < 1090000000 || cube > 3200000000 && cube < 3230000000;
}

bool Cubes::Search(unsigned long long n, unsigned int range) {
	unsigned long long cube = n * n * n;
	set<unsigned long long> sets;
	set<unsigned long long>::iterator i;

	if (!permutes.empty())
		permutes.clear();

	//1084731223 1240872313 1382321704 1383120472 3217138024, //wrong 1752
	//stringstream ss;
	//ss << cube;
	//string s = ss.str();// to_string((unsigned long)cube);
	string s = to_string(cube);
	if(valid(cube))
		cout << "HERE_1(" << n << "," <<  cube << ") s(" << s << ") ";

	if (s.length() > digits) {
		int num = candidates.size();

		cout << "<digits_1 " << digits << "-" << cubes.size() << ", num " << num << "> ";

		if(num > 0){

			cout << "candidates_1 " << num << " ";
			for(int k = 0; k < num; k++){
				cout << "[" << candidates[k].size();
				for(i = candidates[k].begin(); i != candidates[k].end(); i++)
					cout << " " << *i;
				cout << "] ";
			}

			vector<set<unsigned long long>> cand2;
			vector<set<unsigned long long>>::iterator i1, i2;
			for(i1 = candidates.begin(); i1 != candidates.end(); i1++)
				cand2.push_back(*i1);

			for(i1 = candidates.begin(); i1 != candidates.end(); i1++)
				for(i2 = cand2.begin(); i2 != cand2.end(); i2++)
					if((*i1).size() < (sets = (*i2)).size() && sets.find(*((*i1).begin())) != sets.end())
						i1 = candidates.erase(i1);

			num = candidates.size();
			cout << "candidates_2 " << num << " ";
			for(int k = 0; k < num; k++){
				cout << "[" << candidates[k].size();
				for(i = candidates[k].begin(); i != candidates[k].end(); i++)
					cout << " " << *i;
				cout << "] ";
			}

			if(candidates.size() > 0)
				return true;
		}

		cout << "<digits_2 " << digits << "-" << cubes.size() << ", num " << num << "> ";

		candidates.clear();
		cubes.clear();
		digits = s.length();
	}

	vector<char> v(s.begin(), s.end());
	vector<char> vectors;

	vector<char>::iterator iv;
	bas.clear();
	for(iv = v.begin(); iv != v.end(); iv++)
		bas.push_back(*iv);

	Increase(vectors, v, true);

	if(sets.size() > 0)
		sets.clear();

	for(i = permutes.begin(); i != permutes.end(); i++)
		if(cubes.find(*i) != cubes.end())
			sets.insert(*i);

	//if(n == 345 || n == 384 || n == 405)
	//	cout << "{" << n << "/" << cube << ", permutes " << permutes.size()	<< ", sets " <<  sets.size() << ", cubes " << cubes.size() << "} ";

	if(sets.size() + 1 >= range){
		sets.insert(cube);
		candidates.push_back(sets);
	}

	cubes.insert(cube);
	if(valid(cube))
		cout << "HERE_2(" << cube << ") ";

	return false;
}

void Cubes::Start() {
	unsigned int range = 5;//4; //5;
	cout << "Problem 62 : Cubic permutations, search range " << range << "." << endl;

	chrono::steady_clock sc;
	auto startt = sc.now();

	if(candidates.size() > 0)
		candidates.clear();

	bool found = false;
	for (unsigned long long n = 1; n < 100000; n++) {
		if ((n % 100) == 0) cout << n << " ";
		if(found = Search(n, range))
			break;
	}

	cout << "search end: " << (found ? "" : "not ") << "found." << endl;

	set<unsigned long long> result = candidates[0];
	set<unsigned long long>::iterator i;
	for (i = result.begin(); i != result.end(); i++)
		cout << *i << " ";
	cout << endl;

	//search minimum
	bool start = true;
	unsigned long long cube = 0;
	for (i = result.begin(); i != result.end(); i++) {
		if (start) {
			cube = *i;
			start = false;
		}
		else if (*i < cube)
			cube = *i;
	}
	cout << cube << endl;

	auto time_span = static_cast<chrono::duration<double>>(sc.now() - startt);
	
	cout << "finish " << time_span.count() << " secodes" << endl; //1084731223 for 5? //1189740352 for 6?
}
/***
1084731223 1240872313 1382321704 1383120472 3217138024
1084731223
***/