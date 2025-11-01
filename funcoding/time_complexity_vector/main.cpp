#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <cmath>

class VectorContainer {
private:
    std::vector<int> data;

public:
    void push(int x) {
        data.push_back(x);
    }

    int get(int i) {
        if (i < 0 || i >= data.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[i];
    }

    void delete_element(int i) {
        // if (i < 0 || i >= data.size()) {
        //     throw std::out_of_range("Index out of bounds");
        // }
        data.erase(data.begin() + i);
    }

    int pop() {
        if (data.empty()) {
            throw std::runtime_error("Cannot pop from empty container");
        }
        int last_element = data.back();
        data.pop_back();
        return last_element;
    }

    int find(int x) {
        auto it = std::find(data.begin(), data.end(), x);
        if (it != data.end()) {
            return std::distance(data.begin(), it);
        }
        return -1;
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    void clear() {
        data.clear();
    }

    void display() const {
        std::cout << "[";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i];
            if (i < data.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    VectorContainer container;
    int CNT = 200000000;

    for (int i=0; i< CNT; i++) {
        container.push(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<CNT; i++) {
        auto res = container.get(i);
        // auto res = container.find(CNT/2);
        // container.delete_element(0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    // // Test push method
    // container.push(10);
    // container.push(20);
    // container.push(30);
    // container.push(40);
    
    // std::cout << "After pushing 10, 20, 30, 40: ";
    // container.display();

    // // Test get method
    // std::cout << "Element at index 1: " << container.get(1) << std::endl;

    // // Test find method
    // int index = container.find(30);
    // std::cout << "Index of 30: " << index << std::endl;
    
    // index = container.find(100);
    // std::cout << "Index of 100: " << index << std::endl;

    // // Test delete method
    // container.delete_element(1);
    // std::cout << "After deleting element at index 1: ";
    // container.display();

    // // Test pop method
    // int popped = container.pop();
    // std::cout << "Popped element: " << popped << std::endl;
    // std::cout << "After popping: ";
    // container.display();

    // // Test size and empty methods
    // std::cout << "Size: " << container.size() << std::endl;
    // std::cout << "Is empty: " << (container.empty() ? "Yes" : "No") << std::endl;

    return 0;
}


