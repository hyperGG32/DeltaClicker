

#include <conio.h> // For kbhit()
#include <cstdlib>
#include <ctime> 
#include <iostream>
#include <windows.h>
#include <thread>
#include "DeltaClickerCore.hpp"

using namespace std;


static int randInt(int min, int max) { // Generate random integer between min and max inclusively
    if (max - min + 1 == 1) { return max; }
    return rand() % (max - min + 1) + min;
}



void Clicker::mainLoop()
{
    while (running)
    {
        if (GetAsyncKeyState(LMB) < 0) { // Listen for button presses
            if (randomOffset != 0) {
                offset = randInt(0, randomOffset); // Generate offset
            }
            GetCursorPos(&mousepos); // Mouse pos
            mouse_event(MOUSEEVENTF_LEFTDOWN, mousepos.x, mousepos.y, 0, 0); // Left click
            mouse_event(MOUSEEVENTF_LEFTUP, mousepos.x, mousepos.y, 0, 0);
        }

        if (GetAsyncKeyState(RMB) < 0) {
            if (randomOffset != 0) {
                offset = randInt(0, randomOffset); // Generate offset
            }
            GetCursorPos(&mousepos); // Mouse pos
            mouse_event(MOUSEEVENTF_RIGHTDOWN, mousepos.x, mousepos.y, 0, 0); // Right click
            mouse_event(MOUSEEVENTF_RIGHTUP, mousepos.x, mousepos.y, 0, 0);
        }
		
		this_thread::sleep_for(chrono::milliseconds(delay + ((rand() % 2 && randomOffset > 0) ? offset : offset * -1))); // Sleep for delay + offset

    }

}

Clicker::Clicker()
{
	LMB = VK_XBUTTON2; // Default to first option
	RMB = VK_XBUTTON1; // Default to first option
	delay = 100; // Default delay
	randomOffset = 0; // Default random offset
	offset = 0; // Default offset
	running = false; // Not running by default
	randomMode = false; // Not in random mode by default
	mousepos = { 0, 0 }; // Initialize mouse position
    srand(time(NULL));
}


void Clicker::setDelay(int d)
{
	delay = d;
}

void Clicker::setRandomMode(bool mode)
{   
	randomMode = mode;
}

void Clicker::setRandomOffset(int offset)
{
	randomOffset = offset;
}

void Clicker::setLMB(int lmb)
{
	LMB = lmb;
}

void Clicker::setRMB(int rmb)
{
	RMB = rmb;
}

void Clicker::start()
{
	if (running) {
		return; // Already running
	}
    thread worker(&Clicker::mainLoop, this); // Pass pointer to member function and object instance
    running = true;
	worker.detach(); // Detach the thread to run independently
}


void Clicker::stop()
{
	running = false;
}