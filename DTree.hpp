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

template<class KeyType>
struct DTreeNode {
	DTreeNode(std::string newKey) {
		Random rnd;

		subtreeWeight_ = 1;
		priority_ = rnd.GetRand();
		key_ = newKey;

		l = nullptr, r = nullptr;
	}

	unsigned long long subtreeWeight_, priority_;
	std::string key_;

	DTreeNode *l, *r;
};

template<class KeyType>
class DTree {
public:

	DTree() : 
		root_(nullptr)
	{}

	~DTree() {
		Clear();
	}

	void Clear() {
		Clear(root_);
	}

	void Dump() {
		Dump(root_);
	}

	std::string& operator[](unsigned long long poz) {
		return Get(poz);
	}

	void Insert(std::string str, unsigned long long poz) {
		Insert(new DTreeNode<KeyType>(str), poz);
	}

	void Erase(unsigned long long poz) {
		DTreeNode<KeyType> *l, *r;
		Split(root_, l, r, poz);

		if (r->l == nullptr) {
			DTreeNode<KeyType> *r_son = r->r;
			delete r;
			r = r_son;
			Rebalance(r);
		} else {
			EraseL(r);
			Rebalance(r);
		}

		Merge(root_, l, r);
	}

private:
	DTreeNode<KeyType>* root_;

	void Clear(DTreeNode<KeyType>*& cur) {
		if (cur->l != nullptr)
			Clear(cur->l);

		if (cur->r != nullptr)
			Clear(cur->r);

		delete cur;
		cur = nullptr;
	}

	void Dump(DTreeNode<KeyType>* cur) {
		if (cur == nullptr)
			return;

		if (cur->l != nullptr)
			Dump(cur->l);

		std::cout << cur->key_ << " " << cur->subtreeWeight_ << " " << cur->priority_ << " " << std::endl;

		if (cur->r != nullptr)
			Dump(cur->r);
	}

	std::string& Get(unsigned long long poz) {
		DTreeNode<KeyType> *l, *r;
		Split(root_, l, r, poz);

		DTreeNode<KeyType> *ret = r;

		while (ret->l != nullptr)
			ret = ret->l;

		Merge(root_, l, r);
		return ret->key_;
	}

	void Rebalance(DTreeNode<KeyType>* node) {
		if (node == nullptr)
			return;

		node->subtreeWeight_ = ((node->l == nullptr) ? 0 : node->l->subtreeWeight_) +
							   ((node->r == nullptr) ? 0 : node->r->subtreeWeight_) +
							   1;
	}

	void Split(DTreeNode<KeyType>* cur, DTreeNode<KeyType>*& l, DTreeNode<KeyType>*& r, unsigned long long countLeft) {
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


	void Merge(DTreeNode<KeyType>*& cur, DTreeNode<KeyType>* l, DTreeNode<KeyType>* r) {
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

	void Insert(DTreeNode<KeyType>* ins, unsigned long long poz) {
		DTreeNode<KeyType> *l, *r;
		Split(root_, l, r, poz);
		Merge(l, l, ins);
		Merge(root_, l, r);
	}

	void EraseL(DTreeNode<KeyType>* delp) {
		if (delp->l->l != nullptr)
			EraseL(delp->l);
		else {
			DTreeNode<KeyType> *r_son = delp->l->r;
			delete delp->l;
			delp->l = r_son;
		}

		Rebalance(delp);
	}
};