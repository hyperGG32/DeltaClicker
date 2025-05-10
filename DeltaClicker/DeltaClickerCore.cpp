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



const void Clicker::mainLoop()
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
	bool created = createSaveFiles();
	if (!(loadData() && created)) { // If not loaded, set to default
		type = 1;
		offset = 0;
		LMB = VK_XBUTTON2; // Default to first option
		RMB = VK_XBUTTON1; // Default to first option
		delay = 100; // Default delay
		randomOffset = 0; // Default random offset
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

void Clicker::setType(int t) {
	type = t;
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


bool Clicker::createSaveFiles() // Create the settings file and folder if they don't exist
{
	LPCWSTR filePath = L"C:\\ProgramData\\DeltaClicker\\settings.txt"; // Path to the settings file
	LPCWSTR dirPath = L"C:\\ProgramData\\DeltaClicker"; // Path to the settings folder

	DWORD dirAttributes = GetFileAttributesW(dirPath);
	DWORD fileAttributes = GetFileAttributesW(filePath);

    if (!(dirAttributes != INVALID_FILE_ATTRIBUTES && (dirAttributes & FILE_ATTRIBUTE_DIRECTORY))) { // Checks if the folder exists
		BOOL hDir = CreateDirectoryW(dirPath, NULL); // If it doesn't, create it
    }

	if (!(fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY))) { // Checks if the file exists
		HANDLE hFile = CreateFileW(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // If it doesn't, create it. Make sure to include FILE_SHARE_WRITE or else
		return false;
    }
	return true;
}



void Clicker::saveData()
{
	LPCWSTR filePath = L"C:\\ProgramData\\DeltaClicker\\settings.txt"; // Path to the settings file

	ofstream file(filePath); // Open the file for writing
	if (file.is_open()) {
		file << delay << ';' << randomMode << ';' << randomOffset << ';' << type << ';';
	}
	file.close();
}


bool Clicker::loadData()
{
	LPCWSTR filePath = L"C:\\ProgramData\\DeltaClicker\\settings.txt"; // Path to the settings file

	ifstream file(filePath); // Open the file for reading
	string saveData;

	if (!(file.is_open()) || !(getline(file, saveData))) { // If the file doesn't exist or can't be read, return false
		file.close();
		return false;
	}

	string arr[4]; // Array to store the settings
	stringstream ss(saveData); // String stream to parse the settings


	for (int i = 0; i < 4; ++i) {
		getline(ss, arr[i], ';'); // Parse the settings
	}

	if (stoi(arr[0]) < 1 || stoi(arr[0]) > 32767 || stoi(arr[2]) < 0 || stoi(arr[2]) > 32767 || stoi(arr[3]) > 2 || stoi(arr[3]) < 1) { // Making sure some kid won't break the save file
		file.close();
		return false;
	}

	try {
		delay = stoi(arr[0]);
		randomMode = (arr[1] == "1");
		randomOffset = stoi(arr[2]);
		type = stoi(arr[3]);
	}
	catch (...) {
		file.close();
		return false; // If the settings can't be parsed, return false
	}
	file.close();
}