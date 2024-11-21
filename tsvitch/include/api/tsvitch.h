#pragma once

#include <string>
#include <map>
#include <vector>
#include <future>

namespace tsvitch {

class LiveM3u8;
typedef std::vector<LiveM3u8> LiveM3u8ListResult;

using ErrorCallback = std::function<void(const std::string&, int code)>;

#define CLIENT tsvitch::TsVitchClient
#define CLIENT_ERR const std::string &error, int code

class TsVitchClient {
public:
    static void get_file_m3u8(const std::function<void(LiveM3u8ListResult)>& callback = nullptr,
                             const ErrorCallback& error                             = nullptr);
};
}  // namespace tsvitch