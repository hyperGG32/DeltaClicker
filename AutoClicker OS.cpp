// AutoClicker OS.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <conio.h> // For kbhit() (ChatGPT comment)
using namespace std;

static void reloadSettings();
static void mainProgram();
static void userInput();
static void checkForInvalidInput();
static int randInt(int min, int max);

int LMB, RMB, delay, randomOffset = 0, offset = 0; // LMB stands for left click button; RMB for right click button


static int randInt(int min, int max) { // Generate random integer between min and max inclusively
    if (max - min + 1 == 1) { return max; }
    return rand() % (max - min + 1) + min;
}

static void checkForInvalidInput() { // Checks for valid user input. If invalid, exits program. Rewrite for listening for valid user input
    if (cin.fail()) {
        cout << "INVALID INPUT. PROGRAM CANNOT CONTINUE FUNCTIONING, EXITING...";
        Sleep(2000);
        exit(-1);
    }
    return;
}

static void userInput() {
    char randomMode;
    cout << "ENTER DELAY (in ms): ";
    cin >> delay;
    if (delay < 1) {
        delay = 1;
        cout << "DELAY WAS SET TO 1, BECAUSE IT WAS LOWER/NEGATIVE";
    }
    checkForInvalidInput();
    cout << endl << "ENTER RANDOM MODE (Y/N): ";
    cin >> randomMode;
    checkForInvalidInput();
    if (randomMode == 'y' || randomMode == 'Y') {
        cout << endl << "ENTER +- OFFSET (in ms): ";
        cin >> randomOffset;
        checkForInvalidInput();
        if (randomOffset > delay || randomOffset < 0) { // Check for valid offset
            randomOffset = delay;
            cout << "OFFSET WAS SET TO DELAY VALUE, BECAUSE IT WAS BIGGER/NEGATIVE";
        }
    }
    cout << endl << "ENTER SIDE BUTTON" << endl << "1 - FRONT SIDE BUTTON FOR LEFT CLICK; BACK SIDE BUTTON FOR RIGHT CLICK\n2 - BACK SIDE BUTTON FOR LEFT CLICK; FRONT SIDE BUTTON FOR RIGHT CLICK \nDEFAULT - FIRST OPTION" << endl << "ANSWER: ";
    cin >> LMB; // Listen for User Input
    checkForInvalidInput();
    cout << endl;
    return;
}



static void mainProgram() {
    userInput();
    POINT mousepos;
    switch (LMB) // Unoptimized unreadable thing
    {
    case 1:
        LMB = VK_XBUTTON2;
        RMB = VK_XBUTTON1;
        break;
    case 2:
        LMB = VK_XBUTTON1;
        RMB = VK_XBUTTON2;
        break;

    default:
        LMB = VK_XBUTTON2;
        RMB = VK_XBUTTON1;
        break;
    }

    cout << "Press ESC to exit or any other key to restart settings..." << endl; // ChatGPT cout

    while (true)
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

        Sleep(delay + ((rand() % 2 && randomOffset > 0) ? offset : offset * -1)); // Waits delay + random amount of ms if randomMode is on

        if (_kbhit()) { // Check for any key press (ChatGPT comment)
            reloadSettings(); 
            return;
        }
    }
}

static void reloadSettings() {
    char ch = _getch(); // Get the pressed key (ChatGPT comment)
    system("cls"); // Clear the console
    if (ch == 27) { // ESC key to exit (ChatGPT comment)
        exit(0);
        return;
    }
    cin.ignore(); // Clear the input buffer (ChatGPT comment)
    mainProgram(); // Recall mainProgram (ChatGPT comment)
    return; // Exit the current instance to avoid recursion stack overflow (ChatGPT comment)
}

int main() {
    srand(time(NULL)); // Seed for random generation
    mainProgram(); // Main program
    return 0; // WTF
}
