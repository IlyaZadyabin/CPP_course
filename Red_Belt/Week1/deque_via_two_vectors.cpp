#include <vector>
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() = default;

	bool Empty() const {
		return firstPart.empty() && secondPart.empty();
	}
	size_t Size() const {
		return firstPart.size() + secondPart.size();
	}
	const T& operator[](size_t index) const {
		if (index < firstPart.size()) {
			return firstPart[firstPart.size() - 1 - index];
		} else {
			return secondPart[index - firstPart.size()];
		}
	}
	T& operator[](size_t index) {
		if (index < firstPart.size()) {
			return firstPart[firstPart.size() - 1 - index];
		} else {
			return secondPart[index - firstPart.size()];
		}
	}
	const T& At(size_t index) const {
		if (index >= firstPart.size() + secondPart.size()) {
			throw std::out_of_range("index");
		} else {
			if (index < firstPart.size()) {
				return firstPart[firstPart.size() - 1 - index];
			} else {
				return secondPart[index - firstPart.size()];
			}
		}
	}
	T& At(size_t index) {
		if (index >= firstPart.size() + secondPart.size()) {
			throw std::out_of_range("index");
		} else {
			if (index < firstPart.size()) {
				return firstPart[firstPart.size() - 1 - index];
			} else {
				return secondPart[index - firstPart.size()];
			}
		}
	}
	const T& Back() const {
		if (!secondPart.empty()) {
			return secondPart.back();
		} else {
			return firstPart.front();
		}
	}
	T& Back(){
		if (!secondPart.empty()) {
			return secondPart.back();
		} else {
			return firstPart.front();
		}
	}
	const T& Front() const {
		if (!firstPart.empty()) {
			return firstPart.back();
		} else {
			return secondPart.front();
		}
	}
	T& Front(){
		if (!firstPart.empty()) {
			return firstPart.back();
		} else {
			return secondPart.front();
		}
	}
	void PushFront(const T& element) {
		firstPart.push_back(element);
	}
	void PushBack(const T& element) {
		secondPart.push_back(element);
	}

public:
	vector<T> firstPart;
	vector<T> secondPart;
};