#include <iostream>
#include <chrono>
#include <random>

class Random {
public:
	Random() {
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt_ = std::mt19937_64(seed);
	}

	unsigned long long GetRand() {
		return mt_();
	}
private:
	std::mt19937_64 mt_;
};

template<class KeyType>
struct DTreeNode {
	DTreeNode(KeyType newKey) {
		Random rnd;

		subtreeWeight_ = 1;
		priority_ = rnd.GetRand();
		key_ = newKey;

		l = nullptr, r = nullptr;
	}

	unsigned long long subtreeWeight_, priority_;
	KeyType key_;

	DTreeNode *l, *r;
};

template<class KeyType>
class DTree {
public:

	DTree() : 
		root_(nullptr),
		size_(0)
	{}

	~DTree() {
		Clear();
	}

	unsigned long long Size() {
		return size_;
	}

	void Clear() {
		Clear(root_);
	}

	void Dump() {
		Dump(root_);
	}

	KeyType& operator[](unsigned long long poz) {
		if (poz >= size_)
			throw std::out_of_range("");

		return Get(poz);
	}

	void Insert(KeyType key, unsigned long long poz) {
		if (poz > size_)
			throw std::out_of_range("");

		Insert(new DTreeNode<KeyType>(key), poz);
	}

	void Erase(unsigned long long poz) {
		if (poz >= size_)
			throw std::out_of_range("");

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

		size_--;
	}

private:
	DTreeNode<KeyType>* root_;
	unsigned long long size_;

	void Clear(DTreeNode<KeyType>*& cur) {
		if (cur == nullptr)
			return;

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

	KeyType& Get(unsigned long long poz) {
		if (poz >= size_)
			throw std::out_of_range("");

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
		if (ins == nullptr)
			throw std::invalid_argument("");

		if (poz > size_)
			throw std::out_of_range("");

		DTreeNode<KeyType> *l, *r;
		Split(root_, l, r, poz);
		Merge(l, l, ins);
		Merge(root_, l, r);

		size_++;
	}

	void EraseL(DTreeNode<KeyType>* delp) {
		if (delp == nullptr)
			throw std::invalid_argument("");

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