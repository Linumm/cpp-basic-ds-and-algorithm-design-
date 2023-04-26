#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
auto ComputeWaitingTime(std::vector<T>& service_times)
{
    std::vector<T> each_waiting(service_times.size()); // Elements : each one's waiting time <Sum of waiting time before the one>
    each_waiting[0] = 0;

    for (auto i=1; i<service_times.size(); i++)
        each_waiting[i] = each_waiting[i-1] + service_times[i-1];
    return each_waiting;
}

template<typename T>
void PrintVector(std::vector<T>& V)
{
    std::cout << std::endl;
    for (auto& i: V) {
        std::cout.width(2);
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void ComputeAndPrintTimes(std::vector<T>& service_times)
{
    auto waiting_times = ComputeWaitingTime<int>(service_times);

    std::cout << "-time required: ";
    PrintVector<T>(service_times);

    std::cout << "-waiting time: ";
    PrintVector<T>(waiting_times);

    auto avg_waiting_times = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();

    std::cout << "-avg waiting time: " << avg_waiting_times;
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector<int> service_times {8, 4, 9, 10, 3, 5, 1, 7};
    std::cout << "[Time before sfj]" << std::endl;
    ComputeAndPrintTimes<int>(service_times);
    
    // Sort service_times (shortest-job-first -> ascending order)
    std::sort(service_times.begin(), service_times.end());

    std::cout << std::endl;
    std::cout << "[After sort]" << std::endl;
    ComputeAndPrintTimes<int>(service_times);

    return 0;
}