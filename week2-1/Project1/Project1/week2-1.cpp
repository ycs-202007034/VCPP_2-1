#include <iostream>
#include <conio.h> // Include conio.h for getch()
#pragma warning(disable : 4996)
using namespace std;

int main() {
    cout << "12312314" << endl;
    cout << "����������" << endl;
    cout << "Application" << endl;

    string a;
    char key;

    while (true) {
        cout << "command > ";
        cin >> a;

        if (a == "p") {
            cout << "���� ������ �̳� ���ϴ� �л��̴�";
        }
        else if (a == "f") {
            cout << "���� ������ �̳� ��̴�";
        }
        else if (a == "j") {
            cout << "������ ���� �� ���ּ���";
        }
        else {
            cout << "�ùٸ� ����� �ƴմϴ�." << endl;
        }

        cout << endl << "Press 'ESC' to exit or any other key to continue..." << endl;

        key = getch();

        if (key == 27)
            break; //esc������ ��������
    }

    return 0;
}