#pragma once

#include <windows.h>


class Clicker {
	private:
	int LMB, RMB, delay, randomOffset, offset, type;
	POINT mousepos;
	bool running = false;
	bool randomMode = false;
	bool loaded = false;
	const void mainLoop();
	bool createSaveFiles();
	public:
		Clicker();
		void start();
		void stop();
		void saveData();
		bool loadData();
		int getDelay();
		bool getRandomMode();
		int getRandomOffset();
		int getType();
		bool getLoadState();
		void setDelay(int d);
		void setRandomMode(bool mode);
		void setRandomOffset(int offset);
		void setLMB(int lmb);
		void setRMB(int rmb);
		void setLoaded(bool load);
		void setType(int t);
};

