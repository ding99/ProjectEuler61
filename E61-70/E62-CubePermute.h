#pragma once

#include <set>
#include <vector>

typedef struct Cube{
	unsigned long long base;
	unsigned long long cube;
	int numbers[10];
	bool check;
};

class CubePermute{
private:
	unsigned int digits;
	std::set<unsigned long long> result;
	std::vector<Cube> cubes;

	bool Same(Cube, Cube);
	bool Search(unsigned long long, int);

public:
	CubePermute(): digits(0){};
	void Start();
};
