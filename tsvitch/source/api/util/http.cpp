

#include "tsvitch/util/http.hpp"

namespace tsvitch {

cpr::Response HTTP::get(const std::string& url, const cpr::Parameters& parameters, int timeout) {
    return cpr::Get(cpr::Url{url}, parameters, CPR_HTTP_BASE);
}

};  // namespace tsvitch