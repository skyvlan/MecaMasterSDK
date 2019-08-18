# MecaMasterSDK
an attempt to create a Lighting SDK for dA Meca Master RGB through Reverse Engineering

# NOTICE
this project is still far from finished, but hey, the basic stuff is working

# TODO
0. ~~Actually work on this thing without procrastinating every 5 minutes~~
1. Do Total rewrite in C++ (current one is written in C)
2. Finish Features
3. ~~do initial commit of rewrite~~ 
4. Add wiki(?)  
5. Linux and Mac support
6. Tidy up things

# Example
```
// Set the color of the device withrandom colors
#include "pch.h"
#include <iostream>
#include <random>
#include <Windows.h>
#include "KeyboardSDK.h"

int main(){
	std::random_device R;
	std::random_device G;
	std::random_device B;
	std::uniform_int_distribution<int> uf(0, 255);
	KeyboardSDK Keyboard;
	if (!Keyboard.FindKeyboard()) {
		std::cout << "Cannot Find Keyboard" << std::endl;
	}
	else {
		std::cout << "Keyboard Found!" << std::endl;
		while (true) {

			std::cout << "Color changed to: " << std::hex << "#" << uf(R) << uf(G) << uf(B) << std::endl;
			Keyboard.SetColorAllKeys(uf(R), uf(G), uf(B));
			Sleep(1000);
		}
	}
}
```