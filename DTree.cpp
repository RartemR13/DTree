#include "DTree.hpp"

Random::Random() {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	mt_ = std::mt19937_64(seed);
}

unsigned long long Random::GetRand() {
	return mt_();
}
