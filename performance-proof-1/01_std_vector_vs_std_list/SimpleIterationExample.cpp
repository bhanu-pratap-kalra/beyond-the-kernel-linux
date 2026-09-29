#include <vector>
#include <list>
#include <chrono>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    size_t max_size = 100000;
    long long vector_sum = 0;
    long long list_sum = 0;

    if (argc == 2)
    {
        max_size = static_cast<size_t>(std::stoi(argv[1]));
    }
    
    std::vector<int> local_vector;
    std::list<int> local_list;

    local_vector.reserve(max_size);

    for (size_t i = 0; i < max_size; ++i)
    {
        local_vector.push_back(1);
        local_list.push_back(1);
    }

    using Clock = std::chrono::steady_clock;

    auto vector_start = Clock::now();
    for (const auto& num : local_vector)
    {
        //Why don't we simply iterate ?
        //When we use -O2 optimization, if only iteration is performed without any processing, the compiler may remove the complete iteration
        vector_sum += num;
    }
    auto vector_end = Clock::now();

    const double vector_ns = std::chrono::duration<double, std::nano>(vector_end - vector_start).count();

    auto list_start = Clock::now();
    for (const auto& num : local_list)
    {
        list_sum += num;
    }
    auto list_end = Clock::now();

    const double list_ns = std::chrono::duration<double, std::nano>(list_end - list_start).count();

    //Again we simply print the sum, so that compiler does not remove the processing of above iteration
    std::cout << "Vector sum: " << vector_sum << std::endl;
    std::cout << "Time taken to iterate through " << max_size << " elements in vector = " << vector_ns << " ns." << std::endl;

    std::cout << "List sum: " << list_sum << std::endl;
    std::cout << "Time taken to iterate through " << max_size << " elements in list = " << list_ns << " ns." << std::endl;
}