# Filtered Primes
This is just a fun little program I wrote to find a list of primes I needed for a hashmap implementation for 
Cave-Bedrock.
It goes through and finds all the prime numbers below some hardcoded value. 
Then it filters through that list so that every subsequent prime is at least 25% larger than the previous one.
It's not a particularly efficient or clever implementation, but I don't have enough ram to do the Sieve of Eratosthenes,
and I don't want to fall down the rabbit hole of more clever prime number finding algorithms. 
Arguably I should have just found a list of prime numbers, but this was enjoyable to write and an excuse to use the 
Cave library I'm working on. 

## Caveats 
* Only works on 64-bit systems. I wanted to be able to assume a size_t was 64 bits for better or worse. 
* In order to build, cmake needs to be able to find the Cave library found here https://github.
  com/SiliconLion/cave
* Only tested on my Macbook, but should build on any Unix system. Theoretically it should be easy to make build on 
  Windows, but YMMV.