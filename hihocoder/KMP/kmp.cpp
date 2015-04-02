#include <iostream>
#include <cstring>
#include <cstdio>

namespace hihocoder{
namespace kmp{
class KmpWorker{
public:
	KmpWorker() {}
	KmpWorker(char *t, char *p) : text(t), pattern(p) {}
	bool init() {}

	bool count_pattern_in_text(int *result, char* pattern, char* text) {
	    int next[10004] = {}; 
		if (strlen(pattern) <= 0) {
			// do something	
			return false;
		}
		
		if (strlen(text) <= 0) {
			// do something	
			return false;
		}


		if (!gen_next(pattern, next)) {
			// do something	
		}


		// find substring
		//
		
		*result = 0;
		int text_length = strlen(text);
		int pattern_length = strlen(pattern);
        int q = 0;
        int p = 0;
        while (p < text_length) {
            if (text[p] == pattern[q]) {
                ++p;
                ++q;
                if (q == pattern_length) {
                    ++(*result); 
                }
            } 
            else {
                if (q == -1) {
                    ++p;
                    ++q;
                }
                else{
                    q = next[q]; 
                } 
            }
        }
        // for (int p = 0; p < text_length; ++p) {
        //     if (text[p] == pattern[q]) {
        //         ++q; 
        //         if (q == pattern_length - 1) {
        //             ++(*result);
        //             q = next[q]; 
        //             --p;
        //             continue;
        //         }
        //     }
        //     else {
        //         if (q == -1) {
        //             ++p;
        //             q = 0;
        //         }
        //         else {
        //             q = next[q];
        //             --p;
        //         }
        //     }

        // }
        /***********************************************/ 
        // int i = 0;
        // int j = 0;
        // int n = pattern_length;
        // int len = text_length;
        // while(i < len) {
        //     if (j == -1 || text[i] == pattern[j]) {
        //         ++i;
        //         ++j;
        //     }
        //     else {
        //         j = next[j];
        //     }
        //     if (j == n) {
        //         ++(*result);
        //     }
        // }
        /***********************************************/ 

		return true;
	}	
private:
	char* text;
	char* pattern;
	bool gen_next(char *pattern, int *next) {
		next[0] = -1;
        // std::cout << "next[0]= " << next[0] << ", next[1] = " << next[1] << std::endl;
        // std::cout << pattern << std::endl;
        // for (int p = 0; p < strlen(pattern); ++p) {
        //     int q = p - 1;
        //     while (1) { 
        //         // std::cout << "p = " << p << ", q = " << q << std::endl;
        //         q = next[q + 1];
        //         if (pattern[q + 1] == pattern[p]) {
        //             next[p + 1] = q + 1;
        //             break;
        //         }
        //         if (q == -1) {
        //             next[p + 1] = 0;
        //             break;
        //         }

        //     }
        //     printf("next[%d] = %d\n", p + 1, next[p + 1]);
        // }

        int i = 0;
        int j = -1;
        while( i < strlen(pattern)) {
            if (j == -1 || pattern[i] == pattern[j]) {
                next[i + 1] = j + 1;
                printf("next[%d] = %d\n", i + 1, next[i + 1]);
                j = next[i + 1];
                ++i;
            }
            else {
                j = next[j]; 
            }
        }
        /**************************************/ 
        // int i = 0;
        // int j = -1;
        // next[0] = -1;
        // int len = strlen(pattern);
        // while(i < len) {
        //     if (j == -1 || pattern[i] == pattern[j]) {
        //         next[++i] = ++j;
        //     } 
        //     else {
        //         j = next[j];
        //     }
        // }
        /**************************************/ 

		return true;
	}

};
}// end namespace
}// end namespace


int main() {
	// std::string text;
	// std::string pattern;
    char text[1000007];
    char pattern[10050];
	hihocoder::kmp::KmpWorker kmp_worker;
	if (!kmp_worker.init()) {
		// do something	
	}	
	int num_test;
	// std::cin >> num_test;
    scanf("%d", &num_test);	
    while(num_test) {
		// std::cin >> pattern;
		// std::cin >> text;
	    scanf("%s%s", pattern, text);	
        printf("%s\n%s\n", pattern, text); 
        --num_test;
		
		// if (!kmp_worker.set_text(text)) {
		// 	//do something	
		// }

		// if (!kmp_worker.set_pattern(pattern)) {
		// 	// do something	
		// }

		int result = 0;

		if (!kmp_worker.count_pattern_in_text(&result, pattern , text)) {
			// do something	
		}
        printf("%d\n", result);
		// std::cout << result << std::endl;
	}

	return 0;

}
