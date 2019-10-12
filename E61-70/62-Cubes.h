#pragma once
#include <iostream>
#include <set>
#include <vector>

class Cubes {
private:
	std::set<unsigned long> cubes;
	std::set<unsigned long> permutes;
	int digits;

	std::set<unsigned long> Search(unsigned long);
	void Increase(std::vector<char>, std::vector<char>);

public:
	Cubes() : digits(0) {};
	void Start();
};