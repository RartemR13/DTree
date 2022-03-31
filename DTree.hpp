#include <iostream>
#include <chrono>
#include <random>
#include <string>

class Random {
public:
	Random();
	unsigned long long GetRand();
private:
	std::mt19937_64 mt_;
};

struct DTreeNode {
	DTreeNode(std::string);

	unsigned long long subtreeWeight_, priority_;
	std::string key_;

	DTreeNode *l, *r;
};

class DTree {
public:

	DTree();
	~DTree();

	void Clear();

	void Clear(DTreeNode*&);

	void Dump();

	void Dump(DTreeNode*);

	std::string& operator[](unsigned long long);

	std::string& Get(unsigned long long);

	void Insert(std::string, unsigned long long);

	void Erase(unsigned long long);

	DTreeNode* root_;

	void Rebalance(DTreeNode*);

	void Split(DTreeNode*, DTreeNode*&, DTreeNode*&, unsigned long long);

	void Merge(DTreeNode*&, DTreeNode*, DTreeNode*);

	void Insert(DTreeNode*, unsigned long long);

	void EraseL(DTreeNode*);
};