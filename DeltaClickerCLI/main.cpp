#include <windows.h>
#include "../DeltaClicker/DeltaClickerCore.hpp"
#include <iostream>
#include <conio.h>
#include <cmath>
#undef max
#include <limits>



using namespace std;

Clicker mainClicker; // Create an instance of Clicker



char barabolya[] = R"(~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~     ____  _____ _   _____  _    ____ _     ___ ____ _  _______ ____     ~
~    |  _ \| ____| | |_   _|/ \  / ___| |   |_ _/ ___| |/ / ____|  _ \    ~
~    | | | |  _| | |   | | / _ \| |   | |    | | |   | ' /|  _| | |_) |   ~
~    | |_| | |___| |___| |/ ___ \ |___| |___ | | |___| . \| |___|  _ <    ~
~    |____/|_____|_____|_/_/   \_\____|_____|___\____|_|\_\_____|_| \_\   ~
~                                                                         ~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)"; // barabolya



static bool checkInput() { // Checks for valid user input. If invalid, clears the input buffer
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

static int delayInput() {
    system("cls");
    int delay;
    cout << "ENTER DELAY (in ms): ";
    cin >> delay; // Here's kbhit thing won't work, as delay is multicharacter
    if (!(checkInput())) {
		return mainClicker.getDelay(); // If invalid input, return previous value
    }
    if (delay < 1) {
        delay = 1;
        cout << "DELAY WAS SET TO 1, BECAUSE IT WAS LOWER/NEGATIVE";
    }
    mainClicker.setDelay(delay);
    mainClicker.saveData();
    return delay;
}

static bool randomModeInput() {
    system("cls");
	char randomMode;
    cout << "ENTER RANDOM MODE (Y/N)";
    while (true) {
        if (_kbhit()) {
            randomMode = _getch();
            break;
        }
        Sleep(200);
    }
    mainClicker.setRandomMode(randomMode == 'y' || randomMode == 'Y');
    mainClicker.saveData();
	return (randomMode == 'y' || randomMode == 'Y');
}

static int randomOffsetInput(int delay) {
    system("cls");
	int randomOffset;
    cout << "ENTER +- OFFSET (in ms): ";
    cin >> randomOffset; // Same as delay
    if (!(checkInput())) {
        return mainClicker.getDelay(); // If invalid input, return previous value
    }
    if (randomOffset > delay || randomOffset < 0) { // Check for valid offset
        randomOffset = delay;
        cout << "OFFSET WAS SET TO DELAY VALUE, BECAUSE IT WAS BIGGER/NEGATIVE";
    }
	mainClicker.setRandomOffset(randomOffset);
    mainClicker.saveData();
	return randomOffset;
}

static int typeInput() {
    system("cls");
    int type, LMB, RMB;
    cout << "ENTER SIDE BUTTON LAYOUT (1/2)";
    while (true) {
        if (_kbhit()) {
            type = _getch() - 48;;
            break;
        }
        Sleep(200);
    }
    if (type < 1 || type > 2) {
        type = 1;
    }
    switch (type) // Unoptimized unreadable thing
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
	mainClicker.setLMB(LMB);
	mainClicker.setRMB(RMB);
    mainClicker.setType(type);
	mainClicker.saveData();
    return type;
}


static void userInput() {
    system("cls");
    cout << barabolya << endl;
    if (mainClicker.getLoadState()) { // Much bloat
        mainClicker.start();
		cout << "~    CURRENT SETTINGS                                                     ~" << endl;
        cout << "~    DELAY: " << mainClicker.getDelay();
		for (int i = 0; i < 62 - static_cast<int>(log10(mainClicker.getDelay())) - 1; ++i) { // Some bloat
			cout << " ";
		}
        cout << "~" << endl;
		cout << "~    RANDOM MODE: " << (mainClicker.getRandomMode() ? "YES                                                     ~" : "NO                                                      ~") << endl;
		if (mainClicker.getRandomMode()) {
            cout << "~    RANDOM OFFSET: " << mainClicker.getRandomOffset();
			for (int i = 0; i < 54 - static_cast<int>(log10((mainClicker.getRandomOffset() == 0) ? 1 : mainClicker.getRandomOffset())) - 1; ++i) { // So if it's zero in won't break anything
				cout << " ";
			}
			cout << "~" << endl;
		}
        cout << "~    LAYOUT: " << ((mainClicker.getType() == 1) ? "A" : "B") << "                                                            ~" << endl;
        cout << R"(~                                                                         ~
~    CHANGE DELAY - D                           CHANGE RANDOM MODE - M    ~
~    CHANGE RANDOM OFFSET - O                   CHANGE LAYOUT - L         ~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)" << endl;
        while (true) {
            if (_kbhit()) {
                char ch = _getch();
                switch (ch) { // Uh it is very bulky, potentially buggy and eats memory, but I hope it works
                case 'd':
                case 'D':
                    delayInput();
                    if (mainClicker.getRandomOffset() > mainClicker.getDelay()) { // When changing delay, avoid random offset being higher than delay
                        mainClicker.setRandomOffset(mainClicker.getDelay());
                        mainClicker.saveData();
                    }
                    userInput();
                    return;
                    break;
                case 'm':
                case 'M':
                    randomModeInput();
                    userInput();
                    return;
                    break;
                case 'o':
                case 'O':
                    randomOffsetInput(mainClicker.getDelay());
                    userInput();
                    return;
                    break;
                case 'l':
                case 'L':
					typeInput();
					userInput();
					return;
					break;
				case 27:
					exit(0);
					return;
					break;
                }
            }
            Sleep(200);
        }
    }
    delayInput();
    if (randomModeInput()) {
		randomOffsetInput(mainClicker.getDelay());
    }
	typeInput();
    cout << endl;
    mainClicker.start();
    mainClicker.setLoaded(true);
    userInput();
    return;
}


int main() {
    userInput();
    return 0; // WTF
}