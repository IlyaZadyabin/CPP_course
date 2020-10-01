#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate() {
		if (!deallocatedObjects.empty()) {
			auto tmp = deallocatedObjects.front();
			allocatedObjects.insert(tmp);
			deallocatedObjects.pop_front();
			return tmp;
		} else {
			auto ptr = new T;
			allocatedObjects.insert(ptr);
			return ptr;
		}
	}
	T* TryAllocate() {
		if (!deallocatedObjects.empty()) {
			auto tmp = deallocatedObjects.front();
			allocatedObjects.insert(tmp);
			deallocatedObjects.pop_front();
			return tmp;
		} else {
			return nullptr;
		}
	}

	void Deallocate(T* object) {
		auto ptr = allocatedObjects.find(object);
		if (ptr != allocatedObjects.end()) {
			deallocatedObjects.push_back(*ptr);
			allocatedObjects.erase(ptr);
		} else {
			throw std::invalid_argument("");
		}
	}

	~ObjectPool() {
		for (auto & item : deallocatedObjects) {
			delete item;
		}
		for (auto & item : allocatedObjects) {
			delete item;
		}
	}

private:
	deque<T*> deallocatedObjects;
	set<T*> allocatedObjects;
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}