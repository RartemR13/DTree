#include "DTree.hpp"

Random::Random() {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	mt_ = std::mt19937_64(seed);
}

unsigned long long Random::GetRand() {
	return mt_();
}

DTreeNode::DTreeNode(std::string newKey) {
	Random rnd;

	subtreeWeight_ = 1;
	priority_ = rnd.GetRand();
	key_ = newKey;

	l = nullptr, r = nullptr;
}

DTree::DTree() : 
	root_(nullptr)
{}

DTree::~DTree() {
	Clear();
}

void DTree::Clear() {
	Clear(root_);
}

void DTree::Clear(DTreeNode *&cur) {
	if (cur->l != nullptr)
		Clear(cur->l);

	if (cur->r != nullptr)
		Clear(cur->r);

	delete cur;
	cur = nullptr;
}

void DTree::Dump() {
	Dump(root_);
}

void DTree::Dump(DTreeNode *cur) {
	if (cur == nullptr)
		return;

	if (cur->l != nullptr)
		Dump(cur->l);

	std::cout << cur->key_ << " " << cur->subtreeWeight_ << " " << cur->priority_ << " " << std::endl;

	if (cur->r != nullptr)
		Dump(cur->r);
}

std::string& DTree::operator[](unsigned long long poz) {
	return Get(poz);
}

std::string& DTree::Get(unsigned long long poz) {
	DTreeNode *l, *r;
	Split(root_, l, r, poz);

	DTreeNode *ret = r;

	while (ret->l != nullptr)
		ret = ret->l;

	Merge(root_, l, r);
	return ret->key_;
}

void DTree::Insert(std::string str, unsigned long long poz) {
	Insert(new DTreeNode(str), poz);
}

void DTree::Erase(unsigned long long poz) {
	DTreeNode *l, *r;
	Split(root_, l, r, poz);

	if (r->l == nullptr) {
		DTreeNode *r_son = r->r;
		delete r;
		r = r_son;
		Rebalance(r);
	} else {
		EraseL(r);
		Rebalance(r);
	}

	Merge(root_, l, r);
}

void DTree::Rebalance(DTreeNode *node) {
	if (node == nullptr)
		return;

	node->subtreeWeight_ = ((node->l == nullptr) ? 0 : node->l->subtreeWeight_) +
						   ((node->r == nullptr) ? 0 : node->r->subtreeWeight_) +
						   1;
}

void DTree::Split(DTreeNode *cur, DTreeNode *&l, DTreeNode *&r, unsigned long long countLeft) {
	if (cur == nullptr) {
		l = r = nullptr;
		return;
	}

	if (cur->subtreeWeight_ <= countLeft) {
		l = cur;
		r = nullptr;
		return;
	}

	if (cur->r == nullptr || countLeft == 0) {
		r = cur;
		Split(cur->l, l, r->l, countLeft);
		Rebalance(cur);
		return;
	}

	if (cur->l == nullptr) {
		l = cur;
		Split(cur->r, l->r, r, countLeft-1);
		Rebalance(cur);
		return;
	}

	if (cur->l->subtreeWeight_ + 1 > countLeft) {
		r = cur;
		Split(cur->l, l, r->l, countLeft);
		Rebalance(cur);
	} else {
		l = cur;
		Split(cur->r, l->r, r, countLeft - (cur->l->subtreeWeight_ + 1));
		Rebalance(cur);
	}
}

void DTree::Merge(DTreeNode *&cur, DTreeNode *l, DTreeNode *r) {
	if (l == nullptr) {
		cur = r;
		return;
	}

	if (r == nullptr) {
		cur = l;
		return;
	}

	if (l->priority_ >= r->priority_) {
		Merge(l->r, l->r, r);
		cur = l;
	} else {
		Merge(r->l, l, r->l);
		cur = r;
	}

	Rebalance(cur);
}

void DTree::EraseL(DTreeNode *delp) {
	if (delp->l->l != nullptr)
		EraseL(delp->l);
	else {
		DTreeNode *r_son = delp->l->r;
		delete delp->l;
		delp->l = r_son;
	}

	Rebalance(delp);
}

void DTree::Insert(DTreeNode *ins, unsigned long long poz) {
	DTreeNode *l, *r;
	Split(root_, l, r, poz);
	Merge(l, l, ins);
	Merge(root_, l, r);
}