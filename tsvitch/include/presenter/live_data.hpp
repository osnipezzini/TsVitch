//
// Created by fang on 2022/9/13.
//

#pragma once

#include "tsvitch/result/home_live_result.h"
// #include "tsvitch/result/live_danmaku_result.h"
#include "presenter/presenter.h"

class LiveDataRequest : public Presenter {
public:
    virtual void onLiveData(std::string url) {}

    virtual void onError(const std::string& error) {}

    void requestData(std::string url);

    void reportHistory(int roomid);

    // void requestPayLiveInfo(int roomid);

    // void requestLiveDanmakuToken(int roomid);

    std::string getQualityDescription(int qn);

    static inline int defaultQuality = 0;
    tsvitch::LiveRoomPlayInfo liveRoomPlayInfo{};
    tsvitch::LiveStreamFormatCodec liveUrl{};
    std::unordered_map<int, std::string> qualityDescriptionMap{};
};