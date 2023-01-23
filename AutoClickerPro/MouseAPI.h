#pragma once
#include "AutoClickerPro.h"
#include <windows.h>
#include <WinUser.h>

extern "C" AUTOCLICKERPRO_API void MouseGetPt(POINT & pt);
extern "C" AUTOCLICKERPRO_API void MouseMoveTo(int dx, int dy);
extern "C" AUTOCLICKERPRO_API void MouseLDown();
extern "C" AUTOCLICKERPRO_API void MouseLUp();
extern "C" AUTOCLICKERPRO_API void MouseLClick();
extern "C" AUTOCLICKERPRO_API void MouseRDown();
extern "C" AUTOCLICKERPRO_API void MouseRUp();
extern "C" AUTOCLICKERPRO_API void MouseRClick();
extern "C" AUTOCLICKERPRO_API void MouseDoubleClick(int du = 50);
