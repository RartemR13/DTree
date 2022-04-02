#include "../DTree.hpp"
#include <iostream>

void EraseVoidTest() {
	DTree<int> tree;

	try {
		tree.Erase(0);
		throw std::runtime_error("");
	} catch(std::exception) {
		std::cout << "EraseVoidTest: OK" << std::endl;
	}
}

void UseVoidTest() {
	DTree<int> tree;

	try {
		tree[0] = 0;
		throw std::runtime_error("");
	} catch(std::exception) {
		std::cout << "SetVoidTest: OK" << std::endl;
	}
}

void OutSizeTest() {
	DTree<int> tree;

	try {
		tree.Insert(0, 0);
		tree.Insert(0, 0);
		tree.Insert(0, 0);

		tree[3] = 0;

		throw std::runtime_error("");
	} catch(std::exception) {
		std::cout << "OutSizeTest: OK" << std::endl;
	}
}

int main() {

	try {
		EraseVoidTest();
	} catch(std::exception) {
		std::cout << "EraseVoidTest: ERROR" << std::endl;
	}

	try {
		UseVoidTest();
	} catch(std::exception) {
		std::cout << "UseVoidTest: ERROR" << std::endl;
	}	

	try {
		OutSizeTest();
	} catch(std::exception) {
		std::cout << "OutSizeTest: ERROR" << std::endl;
	}

	std::cout << std::endl;

	return 0;
}