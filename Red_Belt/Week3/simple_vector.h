#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
	SimpleVector() {
		data = new T[capacity];
	}
	explicit SimpleVector(size_t size) : size_(size) {
		data = new T[size];
		capacity = size;
	}
	~SimpleVector() {
		delete[] data;
	}

	T& operator[](size_t index) {
		return data[index];
	}

	T* begin() {
		return data;
	}
	T* end() {
		return data + size_;
	}

	size_t Size() const {
		return size_;
	}
	size_t Capacity() const {
		return capacity;
	}
	void PushBack(const T& value) {
		if (size_ + 1 >= capacity) {
			size_++;
			capacity = size_ * 2;
			T* tmp_data = new T[capacity];
			std::copy(this->begin(), this->end(), tmp_data);
			delete[] data;
			data = tmp_data;
			data[size_ - 1] = value;
		} else {
			data[size_++] = value;
		}
	}

private:
	T* data;
	size_t size_{};
	size_t capacity = 0;
};