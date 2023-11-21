#include <iostream>
#include <stdexcept>
#include <algorithm>

#ifndef _Vector_cpp_
#define _Vector_cpp_

template <class T>
class Vector {
private:
    T* data;
    int size;
    int capacity;

public:
    Vector() {
        capacity = 10;
        size = 0;
        data = new T[capacity];
    }

    ~Vector() {
        delete[] data;
    }

    void pushFront(const T& element) {
        if (size == capacity) {
            T* newData = new T[capacity * 2];
            for (int i = 0; i < size; i++) {
                newData[i + 1] = data[i];
            }
            delete[] data;
            data = newData;
            capacity *= 2;
        } else {
            for (int i = size; i > 0; i--) {
                data[i] = data[i - 1];
            }
        }


        data[0] = element;
        size++;
    }

    void pushBack(const T& element) {
        if (size == capacity) {
            T* newData = new T[capacity * 2];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity *= 2;
        }
        data[size] = element;
        size++;
    }

    void popBack() {
        if (size > 0) {
            size--;
            if (size < capacity / 2 && capacity > 10) {
                T* newData = new T[capacity / 2];
                for (int i = 0; i < size; i++) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
                capacity /= 2;
            }
        }
    }
    void Insert(int position, const T& value) {
        if (position < 0 || position > size) {
            std::cerr << "Invalid insertion position." << std::endl;
            return;
        }


        if (size == capacity) {
            T* newData = new T[capacity * 2];
            for (int i = 0; i < position; i++) {
                newData[i] = data[i];
            }
            newData[position] = value;
            for (int i = position; i < size; i++) {
                newData[i + 1] = data[i];
            }
            delete[] data;
            data = newData;
            size++;
            capacity *= 2;
        } else {
            for (int i = size; i > position; i--) {
                data[i] = data[i - 1];
            }
            data[position] = value;
            size++;
        }
    }
     void Clear() {
        delete[] data;
        size = 0;
        capacity = 10;
        data = new T[capacity];
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Chi muc nam ngoai pham vi");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void heapSort() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
        for (int i = size - 1; i > 0; i--) {
            std::swap(data[0], data[i]);
            heapify(0, i);
        }
    }

    void quickSort() {
        quickSort(0, size - 1);
    }

    int binarySearch(const T& target) const {
        int low = 0;
        int high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (data[mid] == target) {
                return mid;
            } else if (data[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }

private:
    void heapify(int index, int heapSize = -1) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (heapSize == -1) {
            heapSize = size;
        }

        if (left < heapSize && data[left] > data[largest]) {
            largest = left;
        }
        if (right < heapSize && data[right] > data[largest]) {
            largest = right;
        }

        if (largest != index) {
            std::swap(data[index], data[largest]);
            heapify(largest, heapSize);
        }
    }

    void quickSort(int low, int high) {
        if (low < high) {
            T pivot = data[low];
            int i = low - 1;
            int j = high + 1;

            while (true) {
                do {
                    i++;
                } while (data[i] < pivot);

                do {
                    j--;
                } while (data[j] > pivot);

                if (i >= j) {
                    break;
                }

                std::swap(data[i], data[j]);
            }

            quickSort(low, j);
            quickSort(j + 1, high);
        }
    }
};

#endif // _Vector_cpp
