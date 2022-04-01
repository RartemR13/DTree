#include "DTree.hpp"

int main() {

	DTree<std::string> t;

	for (int i = 0; i < 10; ++i) 
		t.Insert("A", i);

	for (int i = 0; i < 10; ++i)
		std::cout << t[i] << std::endl;

	return 0;
}