#include<stdio.h>
#include<functional>
#include <map>
#include<iostream>

#include <chrono>
using namespace std::chrono;
 
#define EXECUTIONS 50000000
void conditionalAdd(long& i, long& j)
{
    if(i%2 == 0)
    {
        j++;
    } 
    else
    {
        j+=2;
    }
}

void add_1_ptr(long& a) { a++; };
void add_2_ptr(long& a) { a+=2; };

int main(int argc, char * argv[])
{  
    std::function<void(long&)> add_1 = [&] (long& i) {
        i++;
    };

    std::function<void(long&)> add_2 = [&] (long& i) {
        i+=2;
    };
    std::map<int, std::function<void(long&)>> map {};
    map[0] = add_1;
    map[1] = add_2;
    long j = 0;

    auto start = high_resolution_clock::now();
    for(long i = 0; i < EXECUTIONS; i++) {
        conditionalAdd(i,j);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() / 1000000 << std::endl; // 0 seconds
    std::cout << j << std::endl;
    
    j = 0;
    start = high_resolution_clock::now();
    for(long i = 0; i < EXECUTIONS; i++) {
        map[i%2](j);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() / 1000000 << std::endl; // 5 seconds
    std::cout << j << std::endl;

    void (*func_1)(long&);
    void (*func_2)(long&);

    func_1 = add_1_ptr;
    func_2 = add_2_ptr;
    std::map<int, void(*)(long&)> func_ptr_map {};
    func_ptr_map[0] = func_1;
    func_ptr_map[1] = func_2;
    j = 0;
    start = high_resolution_clock::now();
    for(long i = 0; i < EXECUTIONS; i++) {
        func_ptr_map[i%2](j);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() / 1000000 << std::endl; // 4 seconds
    std::cout << j << std::endl;
    return 0;

}
