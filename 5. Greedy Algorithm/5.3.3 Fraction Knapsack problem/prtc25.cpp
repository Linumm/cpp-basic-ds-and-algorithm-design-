#include <iostream>
#include <algorithm>
#include <vector>

struct Object
{
    int id;
    int weight;
    double value;
    double value_per_unit_weight;

    Object(int i, int w, double val) : id(i), weight(w), value(val), value_per_unit_weight(val / w) {}
    
    inline bool operator< (const Object& obj) const
    {
        return this->value_per_unit_weight < obj.value_per_unit_weight;
    }

    friend std::ostream& operator<<(std::ostream& os, const Object& obj);
};

std::ostream& operator<<(std::ostream& os, const Object& obj)
{
    os << "[" << obj.id << "] price: " << obj.value << " \tweight: " << obj.weight << " kg\tvalue per weight: " <<obj.value_per_unit_weight;
    return os; 
}


auto FillKnapsack(std::vector<Object>& objects, int knapsack_capacity)
{
    std::vector<Object> knapsack_contents;
    knapsack_contents.reserve(objects.size());

    // Sort objects by descending order (value per weight)
    std::sort(objects.begin(), objects.end());
    std::reverse(objects.begin(), objects.end());

    // Add the most valuable
    auto current_object = objects.begin();
    int current_total_weight = 0;
    while (current_total_weight < knapsack_capacity && current_object != objects.end()) {
        knapsack_contents.push_back(*current_object);
        current_total_weight += current_object->weight;
        current_object++;
    }

    // If bag's weight get over limit by last obj
    int weight_of_last_obj_to_remove = current_total_weight - knapsack_capacity; 
    // since obj is dividable, get weight of last object's to remove
    Object& last_object = knapsack_contents.back();

    if (weight_of_last_obj_to_remove > 0) {
        last_object.weight -= weight_of_last_obj_to_remove;
        last_object.value -= last_object.value_per_unit_weight * weight_of_last_obj_to_remove;
    }

    return knapsack_contents;    
}


int main(int argc, char* argv[])
{
    std::vector<Object> objects;
    objects.reserve(7);

    std::vector<int> weights {1, 2, 7, 9, 3, 4, 6};
    std::vector<double> values {10, 7, 15, 10, 12, 11, 5};
    for (auto i=0; i<7; i++)
        objects.push_back(Object(i+1, weights[i], values[i]));
    
    std::cout << "Object info" << std::endl;
    for (auto& obj: objects)
        std::cout << obj << std::endl;
    std::cout << std::endl;

    int knapsack_capacity = 7; // Bag weight limit
    auto solution = FillKnapsack(objects, knapsack_capacity);

    std::cout << "[Objects to put in (Max capacity = " << knapsack_capacity << ")]" << std::endl;
    for (auto& obj: solution)
        std::cout << obj << std::endl;
    std::cout << std::endl;

    return 0;
}