//
// Created by fang on 2022/7/22.
//

// Thanks to XITRIX's patch to borealis
// https://github.com/XITRIX/borealis/commit/c309f22bd451aaf59fbbb15c5f2345104582e8a8

#pragma once

// 避免多次请求API
#define CHECK_REQUEST \
    if (requesting) return;
#define SET_REQUEST requesting = true;
#define CHECK_AND_SET_REQUEST CHECK_REQUEST SET_REQUEST
#define UNSET_REQUEST requesting = false;

class Presenter {
public:
    virtual ~Presenter() {
        if (deletionToken) *deletionToken = true;
    }

protected:
    bool* deletionToken       = nullptr;
    int* deletionTokenCounter = nullptr;
    bool requesting           = false;
};