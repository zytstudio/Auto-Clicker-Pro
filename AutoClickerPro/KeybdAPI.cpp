#include "pch.h"
#include "KeybdAPI.h"

int FmtStr(std::string& str, int op) {
	switch (op) {
		case ALLUPPER: {
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
			break;
		}
		case ALLLOWER: {
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			break;
		}
		default: {
			return -1;
		}
	}
	return 0;
}

int GetKeyVal(std::string key) {
	FmtStr(key, ALLUPPER);
	std::map<std::string, int>::iterator it;
	it = KEY_MAP_.find(key);
	if (it == KEY_MAP_.end()) {
		return -1;
	}
	return it->second;
}

void KeybdDown(int vk) {
	keybd_event(vk, 0, 0, 0);
}

void KeybdUp(int vk) {
	keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
}

void KeybdPress(int vk, int du) {
	KeybdDown(vk);
	Sleep(du);
	KeybdUp(vk);
}

void KeybdPressCompos(std::vector<int>& key_val, int du, int start) {
	int cur = key_val[start];
	if (start == key_val.size() - 1) {
		KeybdPress(cur, du);
		return;
	}
	KeybdDown(cur);
	KeybdPressCompos(key_val, du, start + 1);
	KeybdUp(cur);
}

void KeybdDownCompos(std::vector<int>& key_val, int start) {
	if (start == key_val.size()) {
		return;
	}
	int cur = key_val[start];
	KeybdDown(cur);
	KeybdDownCompos(key_val, start + 1);
}

void KeybdUpCompos(std::vector<int>& key_val, int start) {
	if (start == key_val.size()) {
		return;
	}
	int cur = key_val[start];
	KeybdUp(cur);
	KeybdUpCompos(key_val, start + 1);
}
