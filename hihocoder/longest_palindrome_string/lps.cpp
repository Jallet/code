#include <cstring>
#include <cstdio>
#include <iostream>
char extended_string[2000000];
char original_string[1000000];

int main() {
    int N = 0;
    // printf("start\n");
    int length[2000000];
    char tokenizer = '$';
    
    scanf("%d", &N);
    // printf("N = %d\n", N);

    while (N--) {
        
        scanf("%s", original_string);
        
        int len = strlen(original_string);
        
        for (int i = 0; i < len; ++i) {
            extended_string[2 * i] = tokenizer;
            extended_string[2 * i + 1] = original_string[i]; 
        }
        extended_string[2 * len] = tokenizer;
        extended_string[2 * len + 1] = '\0';
        printf("%s\n%s\n", original_string, extended_string);

        len = strlen(extended_string);
        
        int max_j = 0;
        int max_length = 1;
        int max_index = 0;
        length[0] = 1; 
        
        for (int i = 1; i < len; ++i) {
            int left_index = 2 * max_j - i;
            int lower_bound = 0; 
            if (left_index >= 0) {
                lower_bound = length[left_index] < length[max_j] - 2 * (i - max_j) 
                              ? length[left_index] : length[max_j] - 2 * (i - max_j); 
            }
            else {
                lower_bound = length[max_j] - 2 * (i - max_j);
            }
            
            lower_bound = lower_bound < 0 ? 1 : lower_bound;

            std::cout << "lower_bound = " << lower_bound << std::endl;
                
            if (lower_bound % 2 == 0) {
                    // printf("lower_bound is even!\n");
                } 
            
            int k = (lower_bound + 1) / 2;
            
            while(true) {
                if (i - k < 0) {
                    length[i] = 2 * (k - 1) + 1;
                    break;
                }
                if (i + k >= len) {
                    length[i] = 2 * (k - 1) + 1; 
                    break;
                }

                if (extended_string[i + k] == extended_string[i - k]) {
                    ++k;
                }
                else {
                    length[i] = 2 * (k - 1) + 1;
                    break;
                }
            }

            if (i + k > max_j + (length[max_j] - 1) / 2) {
                max_j = i;
            }
            
            if (length[i] > max_length) {
                max_length = length[i];
                max_index = i;
            
            }
        }
        
        if (max_length % 2 == 0) {
            // printf("max_length is even\n"); 
        }
        max_length = (max_length - 1) / 2;
        printf("%d\n", max_length);
   }
}

