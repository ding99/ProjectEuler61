#pragma once
#include <iostream>
#include <set>
#include <vector>

class Cubes {
private:
	unsigned int digits;
	std::vector<std::set<unsigned long long>> candidates;

	std::set<unsigned long long> cubes;
	std::set<unsigned long long> permutes;
	std::vector<char> bas;

	bool valid(unsigned long long);

	bool Search(unsigned long long, unsigned int);
	void Increase(std::vector<char>, std::vector<char>, bool);

public:
	Cubes() : digits(0) {};
	void Start();
};