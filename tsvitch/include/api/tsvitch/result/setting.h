

#pragma once

#include "nlohmann/json.hpp"

namespace tsvitch {

class UnixTimeResult {
public:
    size_t now;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UnixTimeResult, now);

}  // namespace tsvitch