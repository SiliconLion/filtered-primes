#include <stdio.h>
#include "include/cave-bedrock.h"
#include <inttypes.h>
#include <stdlib.h>

//if the system is 64 bit, we provide this program. Otherwise, we provide an empty file
//(which will be an error) as this code assumes a size_t is 64bit.
#if UINTPTR_MAX == UINT64_MAX

//num is the number we are checking to see if it is prime.
//prior_primes is a list of every number less than num that is prime.
bool check_if_prime(uint64_t num, CaveVec* prior_primes) {
    for(size_t i = 0; i < prior_primes->len; i++) {
        uint64_t prime_i = *(uint64_t*)cave_vec_at_unchecked(prior_primes, i);
        //never need to check past sqrt(num). However, casting num to floating point and calling
        //sqrt() on it introduces floating point error. I don't know enough about floating point error to
        //calculate when the error would be off by 1 or more, but if any prime is missed, then the whole thing
        //will start getting filled up with non-prime numbers. So I check this way instead. I'm guessing
        //it's a similar speed.
        if(prime_i * prime_i > num) {
            return true;
        }
        if(num % prime_i == 0) {
            return false;
        }
    }
    return true;
}



void fprint_vec_of_uint64(CaveVec* v, FILE * stream) {
    for(size_t i = 0; i < v->len; i++) {
        uint64_t element = *(uint64_t*)cave_vec_at_unchecked(v, i);
        fprintf(stream, "%" PRIu64 " , ", element);
    }
    fprintf(stream, "\n");
}

void check_error(CaveError err) {
    if(err != CAVE_NO_ERROR) {
        const char* err_str = cave_error_string(err);
        printf("Error: %s", err_str);
        exit(-1);
    }
}

int main(int arc, char * argv[] ) {
    CaveError err = CAVE_NO_ERROR;
    CaveVec primes;
    cave_vec_init(&primes, sizeof(uint64_t), 1000000, &err);
    check_error(err);

    uint64_t two_literal = 2;
    cave_vec_push(&primes, &two_literal, &err);

//the number of bytes in 12 GB. Chosen because it's a pretty large number that I can also
//check all numbers below in less than a day.
    uint64_t upperbound = (uint64_t) 12884901888;

    for(uint64_t i = 3; i < upperbound; i++) {
        bool i_is_prime = check_if_prime((size_t)i, &primes);
        if(i_is_prime) {
            cave_vec_push(&primes, &i, &err);
            check_error(err);
        }
    }


    printf("number of primes between 1 and %" PRIu64 " is %" PRIu64 ".\n", upperbound, (uint64_t)primes.len);

    CaveVec filtered_primes;
    cave_vec_init(&filtered_primes, sizeof(uint64_t), 0, &err);
    check_error(err);
    cave_vec_push(&filtered_primes,&two_literal, &err);
    check_error(err);

    uint64_t prev_prime = 2;
    for(size_t i = 0; i < primes.len; i++) {
        uint64_t curr_prime = *(uint64_t*) cave_vec_at_unchecked(&primes, i);
        if((double)curr_prime > 1.5 * (double)prev_prime) {
            cave_vec_push(&filtered_primes, &curr_prime, &err);
            check_error(err);
            prev_prime = curr_prime;
        }
    }

    fprint_vec_of_uint64(&filtered_primes, stdout);

    FILE* out_file = fopen("out.txt", "w");
    fprint_vec_of_uint64(&filtered_primes, out_file);
    fclose(out_file);

    return 0;
}

#endif
