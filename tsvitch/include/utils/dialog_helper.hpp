//
// Created by fang on 2022/12/28.
//

#pragma once

#include <string>

class DialogHelper {
public:
    static void showCancelableDialog(const std::string& msg, std::function<void(void)> cb);
    
    static void quitApp(bool restart = true);
};