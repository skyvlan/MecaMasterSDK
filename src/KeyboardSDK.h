#pragma once
#include "hidapi.h"
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstddef>


enum KeyList {
	ESC, F1, F2, F3, F4, NOKEY1, F5, F6, F7, F8, F9, F10,
	F11, F12, PrtScr, ScrLk, Pause, NOKEY2, NOKEY3, NOKEY4, NOKEY5, Tilde, Num1, Num2,
	Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0, Minus, Equals, Plus, Backspace,
	Insert, Home, PgUp, Numlock, NumDivide, NumMultiply, NumMinus, Tab, Q, W, E, R,
	T, Y, U, I, O, P, LeftBracket, RightBracket, BackSlash, NOKEY6, Del, End,
	PgDn, NumPad7, NumPad8, NumPad9, NumPadPlus, CapsLock, A, S, D, F, G, H,
	J, K, L, Semicolon, Quotes, NOKEYA, Enter, NOKEY7, NOKEY8, NOKEY9, NOKEY10, NumPad4,
	NumPad5, NumPad6, NOKEY11, LShift, NOKEY12, Z, X, C, V, B, N, M,
	Comma, Period, Slash, UNKNOWN1, NOKEY13, SHIFT, NOKEY14, UPARROW, NOKEY15, NumPad1, NumpPad2, NumPad3,
	NumEnter, LCtrl, Win, LAlt, NOKEYB, NOKEY16, SPACE, NOKEY17, NOKEY18, RAlt, FN, List,
	NOKEY19, RCtrl, NOKEY20, NOKEY21, LEFTARROW, DOWNARROW, RIGHTARROW, NumPad0, NOKEY22, NumPadDot, NOKEY23, NOKEY24
};

enum modes {

};

class USBHelper {
private:
	struct hid_device_info *devs, *cur_dev;

	char* DevPath;
public:

	hid_device* Handle;
	std::vector <hid_device*> Handle_vec;
	std::vector <char*> paths_vec;

	void GetDevHandles(int VID, int PID);
	void GetPathList(int VID, int PID);
	bool SendBuffer(std::vector<unsigned char> Buffer);
	bool SendRawBuffer(hid_device* device_handle, std::vector<unsigned char> Buffer);
};


class KeyboardSDK
{
private:
	std::vector<KeyList> ValidKeys{ ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
	F11, F12, PrtScr, ScrLk, Pause, Tilde, Num1, Num2,
	Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0, Minus, Equals, Plus, Backspace,
	Insert, Home, PgUp, Numlock, NumDivide, NumMultiply, NumMinus, Tab, Q, W, E, R,
	T, Y, U, I, O, P, LeftBracket, RightBracket, BackSlash, Del, End,
	PgDn, NumPad7, NumPad8, NumPad9, NumPadPlus, CapsLock, A, S, D, F, G, H,
	J, K, L, Semicolon, Quotes, Enter, NumPad4,
	NumPad5, NumPad6,  LShift,  Z, X, C, V, B, N, M,
	Comma, Period, Slash, SHIFT, UPARROW, NumPad1, NumpPad2, NumPad3,
	NumEnter, LCtrl, Win, LAlt, SPACE, RAlt, FN, List,
	RCtrl, LEFTARROW, DOWNARROW, RIGHTARROW, NumPad0, NumPadDot };
public:
	hid_device* KBHandle;
	USBHelper Device;
	bool FindKeyboard();
	bool SetColorAllKeys(int R, int G, int B);
	bool Shutdown();
};



class BufferBuilder {
private:
	std::array <int, 9> initBuffer{};
	std::array <int, 132> RBuffer{};
	std::array <int, 132> GBuffer{};
	std::array <int, 132> BBuffer{};
public:

	std::vector <unsigned char> devBuffer{};


	std::vector<KeyList> keys{};
	void Build(uint8_t R, uint8_t G, uint8_t B, std::vector<KeyList> Keys);
};

