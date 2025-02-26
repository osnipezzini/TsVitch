

#include "utils/number_helper.hpp"
#include <pystring.h>
#include <chrono>
#include <random>

#ifdef _WIN32
#define GET_TIME                   \
    time_t curTime = time(NULL);   \
    struct tm curTm;               \
    localtime_s(&curTm, &curTime); \
    struct tm tm;                  \
    localtime_s(&tm, &sec);
#elif defined(PS4)
#include <borealis/platforms/ps4/ps4_sysmodule.hpp>

#pragma clang optimize off
static inline void convertUtcToLocalTime(const struct tm* utc, struct tm* local_time) {
    brls::OrbisDateTime utc_sce, local_sce;
    utc_sce.day    = utc->tm_mday;
    utc_sce.month  = utc->tm_mon + 1;
    utc_sce.year   = utc->tm_year + 1900;
    utc_sce.hour   = utc->tm_hour;
    utc_sce.minute = utc->tm_min;
    utc_sce.second = utc->tm_sec;

    brls::OrbisTick utc_tick;
    brls::OrbisTick local_tick;
    brls::sceRtcGetTick(&utc_sce, &utc_tick);
    brls::sceRtcConvertUtcToLocalTime(&utc_tick, &local_tick);
    brls::sceRtcSetTick(&local_sce, &local_tick);

    local_time->tm_year = local_sce.year - 1900;
    local_time->tm_mon  = local_sce.month - 1;
    local_time->tm_mday = local_sce.day;
    local_time->tm_hour = local_sce.hour;
    local_time->tm_min  = local_sce.minute;
    local_time->tm_sec  = local_sce.second;
}
#pragma clang optimize on

#define GET_TIME                               \
    struct tm tm, tm_utc, curTm, curTm_utc;    \
    time_t curTime = time(NULL);               \
    localtime_r(&curTime, &curTm_utc);         \
    convertUtcToLocalTime(&curTm_utc, &curTm); \
    localtime_r(&sec, &tm_utc);                \
    convertUtcToLocalTime(&tm_utc, &tm);
#else
#define GET_TIME                   \
    time_t curTime = time(NULL);   \
    struct tm curTm;               \
    localtime_r(&curTime, &curTm); \
    struct tm tm;                  \
    localtime_r(&sec, &tm);
#endif

const char seed[64] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',  'F',
                       'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',  'V',
                       'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',  'l',
                       'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0', '\0'};

std::string getRandom(int length, int rangeStart, int rangeEnd) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(rangeStart, rangeEnd);
    std::string text;
    for (int n = 0; n < length; ++n) {
        int val = dis(gen);
        text += seed[val];
    }
    return text;
}

std::string tsvitch::getRandomText(int length) { return getRandom(length, 0, 61); }

std::string tsvitch::getRandomNumber(int length) { return getRandom(length, 1, 9); }

std::string tsvitch::getRandomHex(int length, bool lowerCase) {
    if (lowerCase) {
        return pystring::lower(getRandom(length, 0, 15));
    }
    return getRandom(length, 0, 15);
}

std::string tsvitch::sec2Time(size_t t) {
    size_t hour   = t / 3600;
    size_t minute = t / 60 % 60;
    size_t sec    = t % 60;
    if (hour == 0) {
        return tsvitch::pre0(minute, 2) + ":" + tsvitch::pre0(sec, 2);
    }
    return tsvitch::pre0(hour, 2) + ":" + tsvitch::pre0(minute, 2) + ":" + tsvitch::pre0(sec, 2);
}

std::string tsvitch::uglyString2Time(const std::string& str) {
    if (str.empty()) return "";
    auto res = pystring::split(str, ":");
    if (res.size() != 2) return str;
    try {
        int min = std::stoi(res[0]);
        int sec = std::stoi(res[1]);
        return tsvitch::sec2Time(min * 60 + sec);
    } catch (...) {
        return str;
    }
}

std::string tsvitch::sec2TimeDLNA(size_t t) {
    size_t hour   = t / 3600;
    size_t minute = t / 60 % 60;
    size_t sec    = t % 60;
    return std::to_string(hour) + ":" + tsvitch::pre0(minute, 2) + ":" + tsvitch::pre0(sec, 2);
}

std::string tsvitch::sec2MinSec(size_t t) { return tsvitch::pre0(t / 60, 2) + ":" + tsvitch::pre0(t % 60, 2); }

std::string tsvitch::num2w(size_t t) {
    if (t < 10000) {
        return std::to_string(t);
    }
    if (t < 100000000) {
        t = (t / 100 + 5) / 10;
        if (t % 10 == 0) {
            return std::to_string(t / 10) + "万";
        }
        return std::to_string(t / 10) + "." + std::to_string(t % 10) + "万";
    }
    t = (t / 1000000 + 5) / 10;
    return std::to_string(t / 10) + "." + std::to_string(t % 10) + "亿";
}

std::string tsvitch::sec2date(time_t sec) {
    GET_TIME

    if (curTm.tm_year != tm.tm_year || sec > curTime) {
        return std::to_string(tm.tm_year + 1900) + "-" + std::to_string(tm.tm_mon + 1) + "-" +
               std::to_string(tm.tm_mday);
    }
    size_t inter = curTime - sec;

    if (curTm.tm_mon != tm.tm_mon || ((curTm.tm_mon == tm.tm_mon) && abs(curTm.tm_mday - tm.tm_mday) >= 2)) {
        return std::to_string(tm.tm_mon + 1) + "-" + std::to_string(tm.tm_mday);
    } else if (inter > 86400) {
        return "昨天";
    } else if (inter > 3600) {
        return std::to_string(inter / 3600) + "小时前";
    } else if (inter > 60) {
        return std::to_string(inter / 60) + "分钟前";
    }

    return "刚刚";
}

std::string tsvitch::sec2dateV2(time_t sec) {
    GET_TIME
    return std::to_string(tm.tm_year + 1900) + "-" + pre0(tm.tm_mon + 1, 2) + "-" + pre0(tm.tm_mday, 2);
}

std::string tsvitch::sec2FullDate(time_t sec) {
    GET_TIME

    return std::to_string(tm.tm_year + 1900) + "-" + pre0(tm.tm_mon + 1, 2) + "-" + pre0(tm.tm_mday, 2) + " " +
           pre0(tm.tm_hour, 2) + ":" + pre0(tm.tm_min, 2) + ":" + pre0(tm.tm_sec, 2);
}

std::string tsvitch::sec2TimeDate(time_t sec) {
    GET_TIME

    if (curTm.tm_year != tm.tm_year || sec > curTime) {
        return std::to_string(tm.tm_year + 1900) + "-" + std::to_string(tm.tm_mon + 1) + "-" +
               std::to_string(tm.tm_mday);
    }

    if (curTm.tm_mon != tm.tm_mon || ((curTm.tm_mon == tm.tm_mon) && abs(curTm.tm_mday - tm.tm_mday) >= 2)) {
        return std::to_string(tm.tm_mon + 1) + "-" + std::to_string(tm.tm_mday);
    } else if (abs(curTm.tm_mday - tm.tm_mday) >= 1) {
        return "昨天 " + tsvitch::pre0(tm.tm_hour, 2) + ":" + tsvitch::pre0(tm.tm_min, 2);
    }
    return "今天 " + tsvitch::pre0(tm.tm_hour, 2) + ":" + tsvitch::pre0(tm.tm_min, 2);
}

size_t tsvitch::getUnixTime() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}