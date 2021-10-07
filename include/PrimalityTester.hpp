#ifndef PRIMALITY_TESTER_HPP 
#define PRIMALITY_TESTER_HPP

#include <cstdint>
#include <cstdlib>
#include <ctime>

class PrimalityTester{
    private:
        inline std::int_fast64_t mpow(std::int_fast64_t& base, std::int_fast64_t& exponent, std::int_fast64_t modulus) {
            if(modulus == 1) {
                return 0;
            }

            std::int_fast64_t result = 1;
            base = base % modulus;

            while(exponent > 0) {
                if(exponent % 2 == 1) {
                    result = (result * base) % modulus;
                }
                exponent = exponent >> 1;
                base = (base * base) % modulus;
            }

            return result;
        }

    public:
        PrimalityTester();
        ~PrimalityTester();
    
        bool isPrime(std::int_fast64_t, const std::int_fast64_t&);


};	
#endif
