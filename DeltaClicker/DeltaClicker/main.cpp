#include <windows.h>
#include "../DeltaClicker/DeltaClickerCore.hpp"
#include <iostream>
#include <conio.h>



using namespace std;

Clicker mainClicker; // Create an instance of Clicker



char barabolya[] = R"(~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~     ____  _____ _   _____  _    ____ _     ___ ____ _  _______ ____     ~
~    |  _ \| ____| | |_   _|/ \  / ___| |   |_ _/ ___| |/ / ____|  _ \    ~
~    | | | |  _| | |   | | / _ \| |   | |    | | |   | ' /|  _| | |_) |   ~
~    | |_| | |___| |___| |/ ___ \ |___| |___ | | |___| . \| |___|  _ <    ~
~    |____/|_____|_____|_/_/   \_\____|_____|___\____|_|\_\_____|_| \_\   ~
~                                                                         ~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)";






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
    int delay, randomOffset = 0, LMB,RMB;
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
    cout << endl;
	if (randomOffset > 0) {
		mainClicker.setRandomOffset(randomOffset); // Set random offset
		mainClicker.setRandomMode(true); // Set random mode
    }
    else {
		mainClicker.setRandomMode(false); // Set random mode
		mainClicker.setRandomOffset(0); // Set random offset
    }

    mainClicker.setDelay(delay); // Set delay
    mainClicker.setRandomMode(randomMode == 'y' || randomMode == 'Y'); // Set random mode
    mainClicker.setRandomOffset(randomOffset); // Set random offset
	mainClicker.setLMB(LMB); // Set left mouse button
	mainClicker.setRMB(RMB); // Set right mouse button

    return;
}



static void reloadSettings() {
    char ch = _getch(); // Get the pressed key
    system("cls"); // Clear the console
	cout << barabolya << endl; // Print the logo
    if (ch == 27) { // ESC key to exit
        exit(0);
        return;
    }
    cin.ignore(); // Clear the input buffer
    userInput(); // Recall mainProgram
    return; // Exit the current instance to avoid recursion stack overflow
}


static void mainProgram() {
	cout << barabolya << endl; // Print the logo
    userInput();
    mainClicker.start(); // Start the clicker



    cout << "Press ESC to exit or any other key to restart settings..." << endl; 
    while (true) {
        if (_kbhit()) {
            reloadSettings();
        }
		Sleep(200); // Sleep for 200ms to avoid high CPU usage 
        
    }

}



int main() {
    mainProgram(); // Main program
    return 0; // WTF
}