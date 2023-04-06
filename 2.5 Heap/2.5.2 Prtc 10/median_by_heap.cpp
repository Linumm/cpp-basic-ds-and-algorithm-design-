#include <iostream>
#include <queue>
#include <vector>

// We use two heaps, max and min.
// If new data is bigger than existing data's median, save to Min. If not, to Max.
// And then we can easily get median by using two heap's top element.

struct median {

    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    void insert(int data) { //O(log N)
        if (maxHeap.size() == 0) {
            maxHeap.push(data);
            return;
        }

        if (maxHeap.size() == minHeap.size()) {
            if (data <= get()) // get() returns median from elements.
                maxHeap.push(data);
            else
                minHeap.push(data);
        }

        if (maxHeap.size() < minHeap.size()) {
            if (data > get()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(data);
            }
            else
                maxHeap.push(data);
            
            return;
        }

        if (data < get()) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            maxHeap.push(data);
        }
        else
            minHeap.push(data);
    }

    double get() {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / 2.0;
        
        if (maxHeap.size() < minHeap.size())
            return minHeap.top();
        
        return maxHeap.top();
    }
};


int main() {
    median med;

    med.insert(1);
    std::cout << "1 inserted , median: " << med.get() << std::endl;
    med.insert(5);
    std::cout << "5 inserted , median: " << med.get() << std::endl;
    med.insert(2);
    std::cout << "2 inserted , median: " << med.get() << std::endl;
    med.insert(20);
    std::cout << "20 inserted , median: " << med.get() << std::endl;

    return 0;
}

/*
-Compared with Median, bigger one to Min, smaller one to Max 
1. At first, insert to MaxHeap
2. If MinHeap is empty or smaller element than Minheap.top comes, Push to Max
3. Equalize size of both heaps
    1) if Max's size >= Min's size +2, Push Max.top to Min
    2) vice versa
*/