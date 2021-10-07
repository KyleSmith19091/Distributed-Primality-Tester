#include <iostream>
#include <cmath>
#include <cstdint>
#include "../../include/Server.hpp"

#define isOdd(k) K & 1

using namespace std;

// O(logK) where K is the exponent
int_fast64_t mpow(int_fast64_t N, int_fast64_t K, int_fast64_t M) {
    if(M == 1) {
        return 0;
    }
    int_fast64_t r = 1;

    N = N % M;

    while (K > 0) {
        if (K % 2 == 1) {
            r = (r * N) % M;
        }
        K = K >> 1;
        N = (N * N) % M;
    }

    return r;
}

bool fermat(int_fast64_t P, int maxIters = 20) {

    for(int i = 0; i < maxIters; i++){
        int_fast64_t R = (rand() % (P-1)) + 1;
        int_fast64_t T = mpow(R,P-1,P);

        if(T != 1) {
            return false;
        }

    }

    return true;
}

int main(){
    
    srand(time(0));

    //testing::InitGoogleTest();
    //return RUN_ALL_TESTS();

    Server server;
    server.startServer();

    return 0;

}
