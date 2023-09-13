#include <iostream>
#include <conio.h> // Include conio.h for getch()
#pragma warning(disable : 4996)
using namespace std;

int main() {
    cout << "이은석의 행복한 VC++" << endl;

    string a;
    char key;

    while (true) {
        cout << "command > ";
        cin >> a;

        if (a == "q") {
            cout << "qwer 화이팅";
        }
        else if (a == "w") {
            cout << "과제 너무 좋다";
        }
        else if (a == "e") {
            cout << "담주부턴 과제량 3배다";
        }
        else if (a == "r") {
            cout << "행복합니다.";
        }
        else {
            cout << "올바른 명령이 아닙니다." << endl;
        }

        cout << endl << "Press 'ESC' to exit or any other key to continue..." << endl;

        key = getch();

        if (key == 27)
            break; //esc누르면 나가진다
    }

    return 0;
}