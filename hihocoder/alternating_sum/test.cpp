#include <iostream>
#include <hash_map>
#include <math.h>
#include <stdio.h>
#define ODD 0
#define EVEN 1

using namespace __gnu_cxx;

struct value{
    int sum;
    int odd;
};

int num_hit = 0;
int num_result = 0;

int get_sum(long source, hash_map<long, value> *map, int *a) {
    long left = source / 10;
    long right = source % 10;
    hash_map<long, value>::iterator end = map->end();
    hash_map<long, value>::iterator iter;
    int sum = 0;
    int odd = EVEN;
    if ((iter = map->find(left)) != end) {
        ++num_hit; 
        sum = iter->second.sum;
        odd = iter->second.odd;
    }

    else {
        if (left == 0) {
            sum = 0;
            odd = EVEN;
        }
        else {
            sum = get_sum(left, map, &odd);
        }
    }

    if (odd == ODD) {
        sum = sum - right;
    } 
    else {
        sum = sum + right;
    }

    value *temp = new value;
    temp->sum = sum;
    temp->odd = (odd == ODD) ? EVEN : ODD;
    (*map)[source] = *temp;
    *a = temp->odd;
     
    return sum;
}

// int test(int sum ,int x) {
//    int i = 0;
//    int g_sum = 0;
//    for (i = 0; i < 10000; ++i) {
//         if (x == 0) {
//             break; 
//         }
//         int temp = x % 10;
//         x = x / 10;
//         g_sum += pow(-1, i) * temp;
//    }
// 
//    if (i % 2 == 0) {
//         g_sum *= -1; 
//    }
// 
//    if (g_sum != sum) {
//         return -1; 
//    }
//    else {
//        return 0;
//    }
// }

int main() {
    hash_map<long, value> map;
    hash_map<long, value> *sum_map = &map;
    long left_bound = 0;
    long right_bound = 0;
    int sum = 0;
    
    clock_t start;
    clock_t finish;
    start = clock();
    int N = 1;
    while (N--) {
        std::cin >> left_bound >> right_bound >> sum; 
        // std::cout << left_bound << "\t" << right_bound << "\t" << sum << "\t" << std::endl; 
        
        long total = 0;
        long divisor = 1000000000;
        int odd = ODD;
        long temp = 0;
        for (long i = left_bound; i <= right_bound; ++i) {
            if ((temp = get_sum(i, sum_map, &odd)) == sum) {
                total = (total + i) % divisor;
                ++num_result;
            }
        }
        // std::cout << "number of hits is " << num_hit << std::endl;
        // std::cout << "number of results is " << num_result << std::endl;

        std::cout << total << std::endl;
    }
   finish = clock();
   printf("time is %lf\n", (double)(finish - start));
}
