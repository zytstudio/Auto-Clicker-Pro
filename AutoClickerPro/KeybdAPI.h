#pragma once
#include "AutoClickerPro.h"
#include "KeyMap.h"
#include <windows.h>
#include <WinUser.h>
#include <vector>

#define ALLUPPER 0
#define ALLLOWER 1
// #define INITCAP 2

extern "C" AUTOCLICKERPRO_API void KeybdDown(int vk);
extern "C" AUTOCLICKERPRO_API void KeybdUp(int vk);
extern "C" AUTOCLICKERPRO_API void KeybdPress(int vk, int du = 0);
extern "C" AUTOCLICKERPRO_API void KeybdPressCompos(std::vector<int>&key_val, int du = 200, int start = 0);
extern "C" AUTOCLICKERPRO_API void KeybdDownCompos(std::vector<int>&key_val, int start = 0);
extern "C" AUTOCLICKERPRO_API void KeybdUpCompos(std::vector<int>&key_val, int start = 0);
extern "C" AUTOCLICKERPRO_API int FmtStr(std::string & str, int op = ALLUPPER);
extern "C" AUTOCLICKERPRO_API int GetKeyVal(std::string key);
