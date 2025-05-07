#pragma once

#include <windows.h>


class Clicker {
	private:
	int LMB, RMB, delay, randomOffset,offset;
	POINT mousepos;
	bool running = false;
	bool randomMode = false;
	void mainLoop();
	public:
		Clicker();
		void start();
		void stop();
		void setDelay(int d);
		void setRandomMode(bool mode);
		void setRandomOffset(int offset);
		void setLMB(int lmb);
		void setRMB(int rmb);
};

