#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5];
        for (size_t i = 0; i < 5; i++) {
          int endIdx = k.size()-1-(6*i);
          if (endIdx < 0)
            w[4-i] = 0;
          else
            w[4-i] = generateWValues(endIdx, k);
        }
        const HASH_INDEX_T h = (HASH_INDEX_T) (rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4]);
        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(const char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        int num = letter;

        if (isalpha(letter))
          num -= 97;
        else
          num -= 22;
        return (HASH_INDEX_T) num;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }

    unsigned long long generateWValues(size_t endIdx, const std::string& k) const
    {
      // if the word has run out of characters
      if (endIdx < 0)
        return 0;

      unsigned long long w = 0;
      HASH_INDEX_T nums[6];
      // filling nums with letters' values
      for (size_t i = 0; i < 6; i++) {
        if (endIdx < i)
          nums[5-i] = 0;
        else 
          nums[5-i] = letterDigitToNumber(tolower(k[endIdx-i]));
      }
      w = (unsigned long long) ((((((nums[0]) * 36 + nums[1]) * 36 + nums[2]) * 36 + nums[3]) * 36 + nums[4]) * 36 + nums[5]);
      return w;
    }
};

#endif
