#include "../../include/PrimalityTester.hpp"

PrimalityTester::PrimalityTester() {
    srand(time(0));
}

PrimalityTester::~PrimalityTester() {
}

// Primality test done using Fermat's Little Theorem => a^p-1 === 1mod(p)
bool PrimalityTester::isPrime(std::int_fast64_t prime, const std::int_fast64_t& maxIterations = 20) {
    if(prime == 1) {
        return false;
    }

    std::int_fast64_t answer = 0;
    std::int_fast64_t randomBase = 0;
    // Create variable once
    std::int_fast64_t primeMinusOne = prime - 1;

    // Test primality more than once => Drawback of fermat's primality test
    for(int i = 0; i < maxIterations; i++){
        randomBase = rand() % (prime - 1) + 1;
        answer = mpow(randomBase, primeMinusOne, prime);

        if(answer != 1) {
            return false;
        }

    }    

    return true;
}
