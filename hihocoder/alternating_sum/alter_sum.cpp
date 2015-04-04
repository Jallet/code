#include <iostream>
#include <hash_map>
#define ODD 0
#define EVEN 1

using namespace __gnu_cxx;

struct value{
    int sum;
    bool odd;
};

int get_sum(long source, hash_map<long, value> *map) {
    long left = source / 10;
    long right = source % 10;
    hash_map<long, value>::iterator end = map->end();
    hash_map<long, value>::iterator iter;
    int sum = 0; 
    if ((iter = map->find(left)) != end) {
        if (iter->second.odd == ODD) {
            sum = iter->second.sum - right;
        } 
        else {
            sum = iter->second.sum + right;
        }
    }
    else {
        sum = get_sum(left, map);   
    }

    value *temp = new value;
    (*map)[source] = *temp;
    temp->sum = sum;
    temp->odd = EVEN;
     
    return sum;
}

int main() {
    hash_map<long, value> map;
    hash_map<long, value> *sum_map = &map;
    long left_bound = 0;
    long right_bound = 0;
    int sum = 0;
    
    int N = 4;
    while (N--) {
        std::cin >> left_bound >> right_bound >> sum; 
        std::cout << left_bound << "\t" << right_bound << "\t" << sum << "\t" << std::endl; 
        
        long total = 0;
        long divisor = 1000000000;
        for (long i = left_bound; i < right_bound; ++i) {
            if (get_sum(i, sum_map) == sum) {
                total = (total + i) % divisor;
            }
        }

        std::cout << total << std::endl;
    }
}
