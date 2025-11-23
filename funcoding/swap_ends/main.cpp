#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <cmath>

class Sequence {
private:
    std::vector<int> data;
    int startIndex = 0;

public:
    void create(int n) {
        for (int i=0; i<n; i++) {
            data.push_back(i);
        }
    }

    int get(size_t i) const {
        if (i < 0 || i >= data.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        size_t curIndex = (startIndex + i) % data.size();
        return data[curIndex];
    }

    void swapEnds(int k) {
        startIndex = (startIndex + k) % data.size();
    }

    void clear() {
        data.clear();
        startIndex = 0;
    }

    void display() const {
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << this->get(i) << " ";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Sequence sec;
    sec.create(10);
    sec.display();

    sec.swapEnds(5);
    sec.display();

    return 0;
}


