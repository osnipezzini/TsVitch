

#include <borealis/core/thread.hpp>
#include <borealis/core/logger.hpp>

#include "presenter/live_data.hpp"
#include "utils/config_helper.hpp"
#include "tsvitch.h"

void LiveDataRequest::requestData(std::string url) { onLiveData(url); }