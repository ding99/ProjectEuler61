#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <chrono>

#include "E62-CubePermute.h"

using namespace std;

bool CubePermute::Same(Cube c1, Cube c2){
	for(int i = 0; i < 10; i++)
		if(c1.numbers[i] != c2.numbers[i])
			return false;
	return true;
}

bool CubePermute::Search(unsigned long long n, int range){
	Cube cube;
	cube.cube = n * n * n;
	string s = to_string(cube.cube);

	if(s.length() > digits){
		
		int len = cubes.size(), count = 0;
		cout << "<digits-" << digits << "," << len << "> ";

		for(int k = 0; k + range < len + 1; k++){

			if(cubes[k].check)
				continue;

			result.clear();
			result.insert(cubes[k].cube);
			count = 1;

			for(int l = k + 1; l < len; l++)
				if(!cubes[l].check && Same(cubes[k], cubes[l])){
					count++;
					cubes[l].check = true;
					result.insert(cubes[l].cube);
				}
			
			if(count == range)
				return true;
		}

		cubes.clear();
		digits = s.length();
	}

	vector<char> v(s.begin(), s.end());
	int count;
	for(int j = 0; j < 10; j++){
		count = 0;
		for(unsigned int k = 0; k < s.length(); k++)
			if((int)v[k] == '0' + j)
				count++;
		cube.numbers[j] = count;
	}

	cube.base = n;
	cube.check = false;
	cubes.push_back(cube);

	return false;
}

void CubePermute::Start(){
	unsigned int range = 5;
	cout << "Problem 62 : Cubic permutations, search range " << range << endl;

	chrono::steady_clock sc;
	auto startt = sc.now();

	bool found = false;
	for(unsigned long long n = 1; n < 50000; n++){
		if((n % 100) == 0) cout << n << " ";
		if(found = Search(n, range))
			break;
	}
	cout << endl << "Search end: " << (found ? "" : "not ") << "found" << endl;

	set<unsigned long long>::iterator i;

	//min
	unsigned long long cube = *(i = result.begin());
	for(; i != result.end(); i++)
		if(*i < cube)
			cube = *i;

	auto time_span = static_cast<chrono::duration<double>>(sc.now() - startt);
	cout << "Finish " << time_span.count() << " secodes" << endl << cube << endl; //127035954683
}

// range=3: 41063625 56623104 66430125 -> 41063625