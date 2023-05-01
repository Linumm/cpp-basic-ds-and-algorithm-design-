#include <iostream>
#include <algorithm>
#include <list>
#include <cstdlib>

struct Task
{
    int id;
    int start_time;
    int finish_time;

    Task(int _id, int st, int ft) : id(_id), start_time(st), finish_time(ft) {}
};

bool TCompare(const Task t1, const Task t2)
{
    if (t1.finish_time < t2.finish_time)
        return true;
    else
        return false;
}

auto TaskScheduling(std::list<Task> task_list)
{
    // Sort the task_list by ascending order about finish time
    task_list.sort(TCompare);
    // Remove every task whose start_time is faster than the first element's finish_time
    for (auto i = task_list.begin(); i != task_list.end(); i++) {
        auto next_task = std::next(i, 1);
        while (next_task != task_list.end() && next_task->start_time < i->finish_time)
            next_task = task_list.erase(next_task);
        }
    return task_list;
}

int main(int argc, char* argv[])
{
    std::list<Task> task_list;
    int num_of_task = 10;
    int task_start_time[] = {5, 6, 16, 7, 9, 10, 6, 2, 10, 4};
    int task_finish_time[] = {9, 20, 19, 10, 19, 19, 12, 17, 13, 7}; 

    for (int i=0; i<num_of_task; i++) {
        task_list.push_back(Task(i+1, task_start_time[i], task_finish_time[i]));
    }

    // Print out current given tasks info
    std::cout << "[Entire Task]" << std::endl;
    for (auto& i: task_list) {
        std::cout << "[" << i.id << "] " << i.start_time << " -> " << i.finish_time << std::endl;        
    }

    // Task scheduling
    task_list = TaskScheduling(task_list);
    
    // Print out the rescheduled task
    std::cout << "[Re-scheduled Task]" << std::endl;
    for (auto& i : task_list) {
        std::cout << "[" << i.id << "] " << i.start_time << " -> " << i.finish_time << std::endl;
    }

    return 0;
}