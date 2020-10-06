#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0) : size(a_size) {
		if (a_size > N) {
			throw invalid_argument("");
		}
	}

	T& operator[](size_t index) {
		return arr[index];
	}
	const T& operator[](size_t index) const {
		return arr[index];
	}

	auto begin() {
		return arr.begin();
	}
	auto end() {
		return arr.begin() + size;
	}
	auto begin() const {
		return arr.begin();
	}
	auto end() const {
		return arr.begin();
	}

	size_t Size() const {
		return size;
	}
	size_t Capacity() const {
		return N;
	}

	void PushBack(const T& value) {
		if (size == N) {
			throw overflow_error("");
		} else {
			arr[size++] = value;
		}
	}
	T PopBack() {
		if (size == 0) {
			throw underflow_error("");
		} else {
			return arr[--size];
		}
	}

private:
	size_t size{};
	array<T, N> arr;
};
