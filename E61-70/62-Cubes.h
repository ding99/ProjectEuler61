#pragma once
#include <iostream>
#include <set>
#include <vector>

class Cubes {
private:
	std::set<unsigned long> cubes;
	std::set<unsigned long> permutes;
	std::vector<char> bas;
	int digits;

	std::set<unsigned long> Search(unsigned long);
	void Increase(std::vector<char>, std::vector<char>, bool);

public:
	Cubes() : digits(0) {};
	void Start();
};