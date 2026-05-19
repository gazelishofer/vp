#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstddef>

template <typename T> class MyVector {
private:
  T *data;
  size_t size;
  size_t capacity;

  void resize() {
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
    T *newData = static_cast<T *>(operator new(newCapacity * sizeof(T)));
    for (size_t i = 0; i < size; ++i) {
      new (&newData[i]) T(data[i]);
    }
    for (size_t i = 0; i < size; ++i) {
      data[i].~T();
    }
    operator delete(data);
    data = newData;
    capacity = newCapacity;
  }

public:
  MyVector() : data(nullptr), size(0), capacity(0) {}

  ~MyVector() {
    if (data) {
      for (size_t i = 0; i < size; ++i) {
        data[i].~T();
      }
      operator delete(data);
    }
  }

  void push_back(const T &value) {
    if (size >= capacity)
      resize();
    new (&data[size]) T(value);
    ++size;
  }

  void erase(size_t index) {
    if (index >= size)
      return;
    data[index].~T();
    for (size_t i = index; i < size - 1; ++i) {
      new (&data[i]) T(data[i + 1]);
      data[i + 1].~T();
    }
    --size;
  }

  T &operator[](size_t index) { return data[index]; }
  const T &operator[](size_t index) const { return data[index]; }

  size_t getSize() const { return size; }
  bool empty() const { return size == 0; }

  T *getData() { return data; }
  const T *getData() const { return data; }

  T *begin() { return data; }
  T *end() { return data + size; }
  const T *begin() const { return data; }
  const T *end() const { return data + size; }

  void sort(bool (*compare)(const T &, const T &), bool ascending = true) {
    if (size < 2)
      return;
    for (size_t i = 0; i < size - 1; ++i) {
      for (size_t j = 0; j < size - i - 1; ++j) {
        bool needSwap = ascending ? compare(data[j + 1], data[j])
                                  : compare(data[j], data[j + 1]);
        if (needSwap) {
          T tmp = data[j];
          data[j] = data[j + 1];
          data[j + 1] = tmp;
        }
      }
    }
  }

  template <typename Predicate> MyVector<T> filter(Predicate predicate) const {
    MyVector<T> result;
    for (size_t i = 0; i < size; ++i) {
      if (predicate(data[i])) {
        result.push_back(data[i]);
      }
    }
    return result;
  }
};

#endif
