#include <iostream>
#include <conio.h> // Include conio.h for getch()
#pragma warning(disable : 4996)
using namespace std;

int main() {
    cout << "12312314" << endl;
    cout << "이은석님의" << endl;
    cout << "Application" << endl;

    string a;
    char key;

    while (true) {
        cout << "command > ";
        cin >> a;

        if (a == "p") {
            cout << "나는 과제를 겁나 잘하는 학생이다";
        }
        else if (a == "f") {
            cout << "나는 과제가 겁나 즐겁다";
        }
        else if (a == "j") {
            cout << "교수님 과제 더 내주세요";
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