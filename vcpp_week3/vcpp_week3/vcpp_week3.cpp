#include <iostream>
#include <windows.h>
//

int main() {
    INPUT_RECORD inputBuffer[128];
    DWORD numEvents;
    DWORD numEventsRead;

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    if (hInput == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get input handle." << std::endl;
        return 1;
    }

    while (true) {
        if (!ReadConsoleInput(hInput, inputBuffer, 128, &numEventsRead)) {
            std::cerr << "Failed to read input." << std::endl;
            return 1;
        }

        for (numEvents = 0; numEvents < numEventsRead; numEvents++) {
            if (inputBuffer[numEvents].EventType == KEY_EVENT &&
                inputBuffer[numEvents].Event.KeyEvent.bKeyDown) {
                KEY_EVENT_RECORD keyEvent = inputBuffer[numEvents].Event.KeyEvent;

                if (keyEvent.wVirtualKeyCode == VK_ESCAPE) {
                    std::cout << "프로그램 종료" << std::endl;
                    return 0;
                }

                // 키 입력 처리
                if (keyEvent.wVirtualKeyCode == VK_DOWN) {
                    Sleep(300);
                    if (GetAsyncKeyState(VK_RIGHT)) {
                        if (GetAsyncKeyState('A') & 0x8000) {
                            std::cout << "아도겐! =o" << std::endl;
                        }
                    }
                }
                else if (keyEvent.wVirtualKeyCode == VK_UP) {
                    Sleep(300);
                    if (GetAsyncKeyState(VK_UP)) {
                        if (GetAsyncKeyState('A') & 0x8000) {
                            std::cout << "어퍼컷" << std::endl;
                        }
                    }
                }
                else if (keyEvent.wVirtualKeyCode == VK_RIGHT) {
                    Sleep(300);
                    if (GetAsyncKeyState(VK_RIGHT)) {
                        if (GetAsyncKeyState('B') & 0x8000) {
                            std::cout << "발차기" << std::endl;
                        }
                    }
                }
            }
        }
    }

    return 0;
}