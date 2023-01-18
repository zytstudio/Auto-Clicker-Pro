#pragma once
#include <windows.h>
#include <WinUser.h>


using namespace std;


class Mouse_ {
public:
	void GetPt(POINT& pt) {
		GetCursorPos(&pt);
	}

	void MoveTO(int dx, int dy) {
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);
		int x = dx * 65535 / width;
		int y = dy * 65535 / height;
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x, y, 0, 0);
	}

	void L_Down() {
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	}

	void L_Up() {
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

	void L_Click() {
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

	void R_Down() {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	}

	void R_Up() {
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}

	void R_Click() {
		mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}

	void DoubleClick(int du = 50) {
		L_Click();
		Sleep(du);
		L_Click();
	}
}Mouse;