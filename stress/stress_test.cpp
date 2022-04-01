#include "../DTree.hpp"
#include <string>
using namespace std;

int main() {

	DTree<int> tree;

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		string req;
		cin >> req;

		if (req == "add") {
			int poz, val;
			cin >> poz >> val;

			tree.Insert(val, poz);
		} else if (req == "rm") {
			int poz;
			cin >> poz;

			tree.Erase(poz);
		} else if (req == "get") {
			int poz;
			cin >> poz;

			cout << tree[poz] << endl;
		} else if (req == "set") {
			int poz, val;
			cin >> poz >> val;

			tree[poz] = val;
		}
	}

	return 0;
}