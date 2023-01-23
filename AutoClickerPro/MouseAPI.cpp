#include "pch.h"
#include "MouseAPI.h"

void MouseGetPt(POINT& pt) {
	GetCursorPos(&pt);
}

void MouseMoveTo(int dx, int dy) {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int x = dx * 65535 / width;
	int y = dy * 65535 / height;
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x, y, 0, 0);
}

void MouseLDown() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
}

void MouseLUp() {
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void MouseLClick() {
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void MouseRDown() {
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
}

void MouseRUp() {
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void MouseRClick() {
	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void MouseDoubleClick(int du) {
	MouseLClick();
	Sleep(du);
	MouseLClick();
}
