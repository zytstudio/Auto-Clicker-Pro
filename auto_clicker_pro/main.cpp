#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include "keymap.h"
#include "keybdop.h"
#include "mouseop.h"


#define ERR_NO_ARG -1
#define ERR_WRONG_ARG -2
#define ERR_Unknown -127

#define UPPER 0
#define LOWER 1
// #define INITCAP 2


using namespace std;


void ErrExit(int error_code) {
	switch (error_code) {
	case ERR_NO_ARG:
		cout << "You can't run this program directly. \nUse command with arguments to run it. " << endl;
		system("pause");
		break;
	case ERR_WRONG_ARG:
		cout << "Wrong arguments. " << endl;
		break;
	default:
		cout << "Unknown error. " << endl;
	}
	exit(error_code);
}


int FmtStr(string& str, int op = UPPER) {
	switch (op) {
		case UPPER: {
			transform(str.begin(), str.end(), str.begin(), ::toupper);
			break;
		}
		case LOWER: {
			transform(str.begin(), str.end(), str.begin(), ::tolower);
			break;
		}
		default: {
			return -1;
		}
	}
	return 0;
}


int Str2Int(string str) {
	int var = 0;
	int len = str.length(), start = 0;
	bool sym = true;
	if (len == 0) {
		return 0;
	}
	if (str[0] == '-') {
		if (len == 1) {
			return 0;
		}
		start = 1;
		sym = false;
	}
	for (int i = len - 1; i >= start; i--) {
		char cur = str[i];
		if (cur > '9' || cur < '0') {
			return 0;
		}
		int cur_num = cur - '0';
		var += cur_num * pow(10, len - i - 1);
	}
	if (!sym) {
		var = -var;
	}
	return var;
}


void StrSplit(string str, char split, vector<string>& res) {
	istringstream iss(str);
	string token;
	while (getline(iss, token, split)) {
		res.push_back(token);
	}
}


int GetKeyVal(string key) {
	FmtStr(key, UPPER);
	std::map<string, int>::iterator it;
	it = KEY_MAP_.find(key);
	if (it == KEY_MAP_.end()) {
		return -1;
	}
	return it->second;
}


int main(int argc, char const* argv[]) {
	if (argc == 1) {
		ErrExit(ERR_NO_ARG);
	}
	else if (argc < 2) {
		ErrExit(ERR_WRONG_ARG);
	}
	char type = argv[1][0];
	switch (type) {
		case 'm':
		case 'M': {
			if (argc < 3) {
				ErrExit(ERR_WRONG_ARG);
			}
			string action = argv[2];
			FmtStr(action, UPPER);
			if (action == "GET") {
				if (argc >= 4) {
					string delay_ = argv[3];
					int delay = Str2Int(delay_);
					printf("The program will get your mouse position in %.3f second(s). \n", float(delay) / 1000);
					Sleep(delay);
				}
				POINT pt;
				Mouse.GetPt(pt);
				printf("Your mouse position is (%d, %d). \n", pt.x, pt.y);
			}
			else if (action == "GOTO") {
				if (argc < 5) {
					ErrExit(ERR_WRONG_ARG);
				}
				string dx_ = argv[3], dy_ = argv[4];
				int dx = Str2Int(dx_), dy = Str2Int(dy_);
				if (dx < 0 || dy < 0) {
					ErrExit(ERR_WRONG_ARG);
				}
				Mouse.MoveTO(dx, dy);
			}
			else if (action == "L") {
				if (argc == 3) {
					Mouse.L_Click();
					break;
				}
				string r_action = argv[3];
				FmtStr(r_action, UPPER);
				if (r_action == "DOWN") {
					Mouse.L_Down();
				}
				else if (r_action == "UP") {
					Mouse.L_Up();
				}
				else if (r_action == "CLICK") {
					Mouse.L_Click();
				}
				else if (r_action == "DCLICK") {
					Mouse.DoubleClick();
				}
				else {
					ErrExit(ERR_WRONG_ARG);
				}
			}
			else if (action == "R") {
				if (argc == 3) {
					Mouse.R_Click();
					break;
				}
				string r_action = argv[3];
				FmtStr(r_action, UPPER);
				if (r_action == "DOWN") {
					Mouse.R_Down();
				}
				else if (r_action == "UP") {
					Mouse.R_Up();
				}
				else if (r_action == "CLICK") {
					Mouse.R_Click();
				}
				else {
					ErrExit(ERR_WRONG_ARG);
				}
			}
			else {
				ErrExit(ERR_WRONG_ARG);
			}
			break;
		}
		case 'k':
		case 'K': {
			if (argc < 3) {
				ErrExit(ERR_WRONG_ARG);
			}
			string key_str_all = argv[2];
			FmtStr(key_str_all, UPPER);
			vector<string> key_str;
			vector<int> key_val;
			StrSplit(key_str_all, '+', key_str);
			for (int i = 0; i < key_str.size(); i++) {
				int cur = GetKeyVal(key_str[i]);
				if (cur == -1) {
					ErrExit(ERR_WRONG_ARG);
				}
				key_val.push_back(cur);
			}
			if (argc == 3) {
				Keybd.PressCompos(key_val);
				break;
			}
			string action = argv[3];
			FmtStr(action, UPPER);
			if (action == "DOWN") {
				Keybd.DownCompos(key_val);
			}
			else if (action == "UP") {
				Keybd.UpCompos(key_val);
			}
			else if (action == "CLICK") {
				int du = 0;
				if (argc >= 5) {
					string du_ = argv[4];
					du = Str2Int(du_);
				}
				Keybd.PressCompos(key_val, du);
			}
			else {
				ErrExit(ERR_WRONG_ARG);
			}
			break;
		}
		case 's':
		case 'S': {
			int delay = 200;
			if (argc >= 3) {
				string delay_ = argv[2];
				delay = Str2Int(delay_);
			}
			Sleep(delay);
			break;
		}
		default: {
			ErrExit(ERR_WRONG_ARG);
		}
	}
	return 0;
}