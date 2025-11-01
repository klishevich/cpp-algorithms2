#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <cmath>

#include <algorithm>
#include <stdexcept>
#include <iostream>

// template<size_t MAX_SIZE = 10000000>
const int MAX_SIZE = 10000000;

class ArrayContainer {
private:
    int data[MAX_SIZE];
    size_t current_size;

public:
    ArrayContainer() : current_size(0) {}

    // Add element to the end
    void push(int x) {
        if (current_size >= MAX_SIZE) {
            throw std::runtime_error("Container is full");
        }
        data[current_size] = x;
        current_size++;
    }

    // Get element at index i
    int get(int i) {
        if (i < 0 || i >= current_size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[i];
    }

    // Delete element at index i
    void delete_element(int i) {
        if (i < 0 || i >= current_size) {
            throw std::out_of_range("Index out of bounds");
        }
        
        // Shift all elements after i one position to the left
        for (size_t j = i; j < current_size - 1; j++) {
            data[j] = data[j + 1];
        }
        current_size--;
    }

    // Remove and return the last element
    int pop() {
        if (current_size == 0) {
            throw std::runtime_error("Cannot pop from empty container");
        }
        current_size--;
        return data[current_size];
    }

    // Find the index of element x, returns -1 if not found
    int find(int x) {
        for (size_t i = 0; i < current_size; i++) {
            if (data[i] == x) {
                return i;
            }
        }
        return -1;
    }

    // Additional utility methods
    size_t size() const {
        return current_size;
    }

    bool empty() const {
        return current_size == 0;
    }

    bool full() const {
        return current_size >= MAX_SIZE;
    }

    // Clear all elements
    void clear() {
        current_size = 0;
    }

    // Display all elements (for debugging)
    void display() const {
        std::cout << "[";
        for (size_t i = 0; i < current_size; ++i) {
            std::cout << data[i];
            if (i < current_size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    // Get maximum capacity
    size_t capacity() const {
        return MAX_SIZE;
    }
};

int main(int argc, char const *argv[])
{
    ArrayContainer container; // Container with max size 10

    // Test push method
    container.push(10);
    container.push(20);
    container.push(30);
    container.push(40);
    
    std::cout << "After pushing 10, 20, 30, 40: ";
    container.display();

    // Test get method
    std::cout << "Element at index 1: " << container.get(1) << std::endl;

    // Test find method
    int index = container.find(30);
    std::cout << "Index of 30: " << index << std::endl;
    
    index = container.find(100);
    std::cout << "Index of 100: " << index << std::endl;

    // Test delete method
    container.delete_element(1);
    std::cout << "After deleting element at index 1: ";
    container.display();

    // Test pop method
    int popped = container.pop();
    std::cout << "Popped element: " << popped << std::endl;
    std::cout << "After popping: ";
    container.display();

    // Test utility methods
    std::cout << "Size: " << container.size() << std::endl;
    std::cout << "Capacity: " << container.capacity() << std::endl;
    std::cout << "Is empty: " << (container.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Is full: " << (container.full() ? "Yes" : "No") << std::endl;

    return 0;
}


