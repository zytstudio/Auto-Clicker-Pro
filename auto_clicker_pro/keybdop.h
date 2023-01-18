#pragma once
#include <windows.h>
#include <WinUser.h>


using namespace std;


class Keybd_ {
public:
	void Down(int vk) {
		keybd_event(vk, 0, 0, 0);
	}

	void Up(int vk) {
		keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
	}

	void Press(int vk, int du = 0) {
		Down(vk);
		Sleep(du);
		Up(vk);
	}
}Keybd;