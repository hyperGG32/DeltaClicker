#pragma once
#ifdef _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef NOMINMAX
  #define NOMINMAX
  #endif
  #ifndef NOGDI
  #define NOGDI      // прибирає ERROR та інші макроси GDI
  #endif
  #include <windows.h>
#endif
#include <atomic>


class Clicker {
	private:
	int LMB, RMB, delay, randomOffset, offset, type;
	POINT mousepos;
	std::atomic<bool> running = false;
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

