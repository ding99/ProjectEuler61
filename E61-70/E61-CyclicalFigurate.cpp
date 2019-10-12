#include <iostream>
#include <list>
#include "E61-CyclicalFigurate.h"

using namespace std;

list<int> SearchLine(list<int> line, int key) {
	list<int> found;
	list<int>::iterator i;
	for (i = line.begin(); i != line.end(); i++)
		if ((*i) / 100 == key)
			found.push_back(*i);
	return found;
}

list<list<int>> SearchElse(list<list<int>> lines, list<int> got, int key) {
	list<list<int>> result, sub;
	list<list<int>>::iterator ii1, ii2;
	list<int> doing;
	list<int>::iterator i;
	
	for (ii1 = lines.begin(); ii1 != lines.end(); ii1++) {
		if ((doing = SearchLine(*ii1, key)).size() > 0) {

			list<list<int>> linesNext;
			for (ii2 = lines.begin(); ii2 != lines.end(); ii2++)
				if (ii2->size() != ii1->size())
					linesNext.push_back(*ii2);

			for (i = doing.begin(); i != doing.end(); i++) {
				list<int> got2 = list<int>(got);
				got2.push_back(*i);
				if (lines.size() == 1)
					result.push_back(got2);
				else
					for (ii2 = (sub = SearchElse(linesNext, got2, (*i) % 100)).begin(); ii2 != sub.end(); ii2++)
						result.push_back(*ii2);
			}
		}
	}
			
	return result;
}

int Polygonal(int order, int n) {
	switch (order) {
	case 3:
		return n * (n + 1) / 2;
	case 4:
		return n * n;
	case 5:
		return n * (3 * n - 1) / 2;
	case 6:
		return n * (2 * n - 1);
	case 7:
		return n * (5 * n - 3) / 2;
	case 8:
		return n * (3 * n - 2);
	default:
		return 0;
	}
}

void Cyclic() {
	std::cout << "Problem 61 : Cyclical figurate numbers" << std::endl;

	const int max = 6;

	list<int> first, *line;
	list<list<int>> lists, looped;
	int v, sum = 0;

	for(int n = 10; (v = Polygonal(3, n)) < 10000; n++)
		if (v > 999)
			first.push_back(v);

	for (int k = 0; k < 5; k++) {
		line = new list<int>;
		for (int n = 10; (v = Polygonal(k + 4, n)) < 10000; n++)
			if (v > 999)
				(*line).push_back(v);
		lists.push_back(*line);
		if (line != NULL) delete line;
	}

	list<int>::iterator i, j;
	list<list<int>>::iterator ii;
	bool finish = false;

	for (i = first.begin(); i != first.end(); i++){
		for (ii = (looped = SearchElse(lists, list<int>{*i}, (*i) % 100)).begin(); ii != looped.end(); ii++) {
			for (j = ii->begin(); j != ii->end(); j++)
				v = *j;
			if ((v % 100) == (*i) / 100) {
				for (j = ii->begin(); j != ii->end(); j++)
					sum += *j;
				finish = true;
				break;
			}
		}
		if (finish)
			break;
	}

	cout << sum << endl; //28684
}