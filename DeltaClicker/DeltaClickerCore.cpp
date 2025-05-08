#include <conio.h> // For kbhit()
#include <cstdlib>
#include <ctime> 
#include <iostream>
#include <windows.h>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
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
		
		this_thread::sleep_for(chrono::milliseconds(delay + ((rand() % 2 && randomMode && randomOffset > 0) ? offset : offset * -1))); // Sleep for delay + offset

    }

}

Clicker::Clicker()
{
	createSaveFiles(); // Create the settings file and folder if they don't exist
	if (!(loadData())) { // If not loaded, set to default
		type = 1;
		LMB = VK_XBUTTON2; // Default to first option
		RMB = VK_XBUTTON1; // Default to first option
		delay = 100; // Default delay
		randomOffset = 0; // Default random offset
		offset = 0; // Default offset
		running = false; // Not running by default
		randomMode = false; // Not in random mode by default
		mousepos = { 0, 0 }; // Initialize mouse position
	}
	else {
		loaded = true;
	}
    srand(time(NULL)); // Seed
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

void Clicker::setLoaded(bool load) {
	loaded = load;
}

int Clicker::getDelay() {
	return delay;
}

bool Clicker::getRandomMode() {
	return randomMode;
}

int Clicker::getRandomOffset() {
	return randomOffset;
}

bool Clicker::getLoadState() {
	return loaded;
}

int Clicker::getType() {
	return type;
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


void Clicker::createSaveFiles() // Create the settings file and folder if they don't exist
{
	LPCWSTR filePath = L"C:\\ProgramData\\DeltaClicker\\settings.txt"; // Path to the settings file
	LPCWSTR dirPath = L"C:\\ProgramData\\DeltaClicker"; // Path to the settings folder

	DWORD dirAttributes = GetFileAttributesW(dirPath);
	DWORD fileAttributes = GetFileAttributesW(filePath);

    if (!(dirAttributes != INVALID_FILE_ATTRIBUTES && (dirAttributes & FILE_ATTRIBUTE_DIRECTORY))) { // Checks if the folder exists
		BOOL hDir = CreateDirectoryW(dirPath, NULL); // If it doesn't, create it
    }

	if (!(fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY))) { // Checks if the file exists
		HANDLE hFile = CreateFileW(filePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // If it doesn't, create it
    }
}



void Clicker::saveData()
{
	LPCWSTR filePath = L"C:\\ProgramData\\DeltaClicker\\settings.txt"; // Path to the settings file

	ofstream file(filePath); // Open the file for writing
	if (file.is_open()) {
		file << delay << ';' << offset << ';' << randomMode << ';' << randomOffset << ';' << type << ';';
	}
	file.close(); // Close the file
}


bool Clicker::loadData()
{
	LPCWSTR filePath = L"C:\\ProgramData\\DeltaClicker\\settings.txt"; // Path to the settings file

	ifstream file(filePath); // Open the file for reading
	string saveData;

	if (!(file.is_open()) || !(getline(file, saveData))) { // If the file doesn't exist or can't be read, return false
		return false;
	}

	string arr[5]; // Array to store the settings
	stringstream ss(saveData); // String stream to parse the settings


	for (int i = 0; i < 5; ++i) {
		getline(ss, arr[i], ';'); // Parse the settings
	}

	if (stoi(arr[0]) < 1 || stoi(arr[0]) > 32767 || stoi(arr[1]) < 0 || stoi(arr[1]) > 32767 || stoi(arr[3]) < 0 || stoi(arr[3]) > 32767) { // Making sure some kid won't break the save file
		return false;
	}

	try {
		delay = stoi(arr[0]);
		offset = stoi(arr[1]);
		randomMode = (arr[2] == "1");
		randomOffset = stoi(arr[3]);
	}
	catch (...) {
		return false; // If the settings can't be parsed, return false
	}
}