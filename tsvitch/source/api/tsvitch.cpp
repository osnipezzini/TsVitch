#include "tsvitch.h"
#include "tsvitch/util/http.hpp"
#include <random>
#include <utility>

namespace tsvitch {

std::string genRandomHex(int length) {
    char seed[17] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0'};

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    std::string text;
    for (int n = 0; n < length; ++n) {
        int val = dis(gen);
        text += seed[val];
    }
    return text;
}

}  