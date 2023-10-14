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
    std::cout << duration.count() / 1000000 << std::endl; // 6 seconds
    std::cout << j << std::endl;

}
