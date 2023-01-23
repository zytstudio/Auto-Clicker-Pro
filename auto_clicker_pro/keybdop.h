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

	void PressCompos(vector<int>& key_val, int du = 200, int start = 0) {
		int cur = key_val[start];
		if (start == key_val.size() - 1) {
			Press(cur, du);
			return;
		}
		Down(cur);
		PressCompos(key_val, du, start + 1);
		Up(cur);
	}

	void DownCompos(vector<int>& key_val, int start = 0) {
		if (start == key_val.size()) {
			return;
		}
		int cur = key_val[start];
		Down(cur);
		DownCompos(key_val, start + 1);
	}

	void UpCompos(vector<int>& key_val, int start = 0) {
		if (start == key_val.size()) {
			return;
		}
		int cur = key_val[start];
		Up(cur);
		DownCompos(key_val, start + 1);
	}
}Keybd;