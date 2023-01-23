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
#include "AutoClickerPro.h"
#include "MouseAPI.h"
#include "KeybdAPI.h"


#define ERR_NO_ARG -1
#define ERR_WRONG_ARG -2
#define ERR_Unknown -127


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


void StrSplit(string str, char split, vector<string>& res) {
	istringstream iss(str);
	string token;
	while (getline(iss, token, split)) {
		res.push_back(token);
	}
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
			FmtStr(action, ALLUPPER);
			if (action == "GET") {
				if (argc >= 4) {
					string delay_ = argv[3];
					int delay = Str2Int(delay_);
					printf("The program will get your mouse position in %.3f second(s). \n", float(delay) / 1000);
					Sleep(delay);
				}
				POINT pt;
				MouseGetPt(pt);
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
				MouseMoveTo(dx, dy);
			}
			else if (action == "L") {
				if (argc == 3) {
					MouseLClick();
					break;
				}
				string r_action = argv[3];
				FmtStr(r_action, ALLUPPER);
				if (r_action == "DOWN") {
					MouseLDown();
				}
				else if (r_action == "UP") {
					MouseLUp();
				}
				else if (r_action == "CLICK") {
					MouseLClick();
				}
				else if (r_action == "DCLICK") {
					MouseDoubleClick();
				}
				else {
					ErrExit(ERR_WRONG_ARG);
				}
			}
			else if (action == "R") {
				if (argc == 3) {
					MouseRClick();
					break;
				}
				string r_action = argv[3];
				FmtStr(r_action, ALLUPPER);
				if (r_action == "DOWN") {
					MouseRDown();
				}
				else if (r_action == "UP") {
					MouseRUp();
				}
				else if (r_action == "CLICK") {
					MouseRClick();
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
			FmtStr(key_str_all, ALLUPPER);
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
				KeybdPressCompos(key_val);
				break;
			}
			string action = argv[3];
			FmtStr(action, ALLUPPER);
			if (action == "DOWN") {
				KeybdDownCompos(key_val);
			}
			else if (action == "UP") {
				KeybdUpCompos(key_val);
			}
			else if (action == "CLICK") {
				int du = 0;
				if (argc >= 5) {
					string du_ = argv[4];
					du = Str2Int(du_);
				}
				KeybdPressCompos(key_val, du);
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