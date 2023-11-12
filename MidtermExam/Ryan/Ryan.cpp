#include <Windows.h>

HINSTANCE hInst;
HWND hWnd;
HCURSOR hCursorArrow; // ȭ��ǥ Ŀ�� �ڵ�
COLORREF viewColor = RGB(255, 240, 200);
HBRUSH hBackgroundBrush; // ���� �귯��
HPEN hBorderPen;        // �׵θ� ��

bool isBoxVisible = false;
bool isPressSpace = false;
bool isDrawing = false; // �׸� �׸��� ���� ���θ� ��Ÿ���� �÷���
POINT startPoint;
POINT endPoint;
// ��ư �ĺ���
#define BUTTON_ID_1 1001
#define BUTTON_ID_2 1002
#define BUTTON_ID_3 1003
#define BUTTON_ID_4 1004
#define BUTTON_ID_5 1005

void drawbonobono(HWND hWnd, HDC hdc) {
    RECT circle;
    GetClientRect(hWnd, &circle);

    int moveRight = 110; //���������� �̵��� �ȼ� ��
    int moveDown = 25; // �Ʒ��� �̵��� �ȼ� ��
    float scale = 0.8; // ���뺸���� ũ�⸦ �����ϱ� ���� ����

    if (isBoxVisible) {
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, face);
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(100 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(458 * scale) + moveDown); // ��
        SelectObject(hdc, mouse);
        Ellipse(hdc, (int)(315 * scale) + moveRight, (int)(300 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(380 * scale) + moveDown); // ��

        SelectObject(hdc, white);
        Ellipse(hdc, (int)(270 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(340 * scale) + moveRight, (int)(345 * scale) + moveDown); // �ڿ���
        Ellipse(hdc, (int)(340 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(410 * scale) + moveRight, (int)(345 * scale) + moveDown); // �� ������
        SelectObject(hdc, black);
        Ellipse(hdc, (int)(320 * scale) + moveRight, (int)(275 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(315 * scale) + moveDown); // ��
        Ellipse(hdc, (int)(185 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(195 * scale) + moveRight, (int)(260 * scale) + moveDown); // ���ʴ�
        Ellipse(hdc, (int)(490 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(500 * scale) + moveRight, (int)(260 * scale) + moveDown); // �����ʴ�
        SelectObject(hdc, white);
        Ellipse(hdc, (int)(187 * scale) + moveRight, (int)(245 * scale) + moveDown, (int)(193 * scale) + moveRight, (int)(255 * scale) + moveDown); // ���ʴ�
        Ellipse(hdc, (int)(492 * scale) + moveRight, (int)(245 * scale) + moveDown, (int)(498 * scale) + moveRight, (int)(255 * scale) + moveDown); // �����ʴ�

        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // ���ʼ���1
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // ���� ����2
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // ������ ����1
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // ������ ����2
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        DeleteObject(mouse);
        SelectObject(hdc, hOldPen); // ���� �� ����
        DeleteObject(hPen); // �� ����
    }
    if (isBoxVisible == true && isPressSpace == true) {


        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, face);
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(100 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(458 * scale) + moveDown); //��
        SelectObject(hdc, mouse);
        Ellipse(hdc, (int)(315 * scale) + moveRight, (int)(300 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(380 * scale) + moveDown); //��

        SelectObject(hdc, white);
        Ellipse(hdc, (int)(270 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(340 * scale) + moveRight, (int)(345 * scale) + moveDown); // �ڿ���
        Ellipse(hdc, (int)(340 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(410 * scale) + moveRight, (int)(345 * scale) + moveDown); // �� ������
        SelectObject(hdc, black);

        Ellipse(hdc, (int)(320 * scale) + moveRight, (int)(275 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(315 * scale) + moveDown); // �� 

        MoveToEx(hdc, (int)(185 * scale) + moveRight, (int)(240 * scale) + moveDown, NULL); // ���� ��
        LineTo(hdc, (int)(200 * scale) + moveRight, (int)(260 * scale) + moveDown); //
        MoveToEx(hdc, (int)(200 * scale) + moveRight, (int)(260 * scale) + moveDown, NULL); // ������ ��
        LineTo(hdc, (int)(185 * scale) + moveRight, (int)(280 * scale) + moveDown); //

        MoveToEx(hdc, (int)(505 * scale) + moveRight, (int)(240 * scale) + moveDown, NULL); // ������ ����1
        LineTo(hdc, (int)(490 * scale) + moveRight, (int)(260 * scale) + moveDown); //
        MoveToEx(hdc, (int)(490 * scale) + moveRight, (int)(260 * scale) + moveDown, NULL); // ������ ����2
        LineTo(hdc, (int)(505 * scale) + moveRight, (int)(280 * scale) + moveDown); //

        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // ���ʼ���1
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // ���� ����2
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // ������ ����1
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // ������ ����2
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        DeleteObject(mouse);
        SelectObject(hdc, hOldPen); // ���� �� ����
        DeleteObject(hPen); // �� ����
    }
}
void drawryan(HWND hWnd, HDC hdc ,int left, int top, int right, int bottom){
    RECT circle;
    GetClientRect(hWnd, &circle);

    int moveRight = 110; //���������� �̵��� �ȼ� ��
    int moveDown = 25; // �Ʒ��� �̵��� �ȼ� ��
    float scale = 0.8; 
   
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(255, 200, 15));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));

        SelectObject(hdc, face);
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(85 * scale) + moveDown, (int)(320 * scale) + moveRight, (int)(250 * scale) + moveDown);// ���ʱ�
        Ellipse(hdc, (int)(365 * scale) + moveRight, (int)(85 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(250 * scale) + moveDown);// �����ʱ�
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(100 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(458 * scale) + moveDown);// ��
        SelectObject(hdc, white);
        Ellipse(hdc, (int)(270 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(340 * scale) + moveRight, (int)(345 * scale) + moveDown); // �ڿ���
        Ellipse(hdc, (int)(340 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(410 * scale) + moveRight, (int)(345 * scale) + moveDown); // �� ������
        SelectObject(hdc, black);
        Ellipse(hdc, (int)(235 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(255 * scale) + moveRight, (int)(260 * scale) + moveDown); // ���ʴ�
        Ellipse(hdc, (int)(430 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(450 * scale) + moveRight, (int)(260 * scale) + moveDown); // �����ʴ�
        SelectObject(hdc, black);
        MoveToEx(hdc, (int)(210 * scale) + moveRight, (int)(207 * scale) + moveDown, NULL); // ���� ����1
        LineTo(hdc, (int)(280 * scale) + moveRight, (int)(207 * scale) + moveDown); //
        MoveToEx(hdc, (int)(210 * scale) + moveRight, (int)(210 * scale) + moveDown, NULL); // ���� ����2
        LineTo(hdc, (int)(280 * scale) + moveRight, (int)(210 * scale) + moveDown); //
        MoveToEx(hdc, (int)(210 * scale) + moveRight, (int)(214 * scale) + moveDown, NULL); // ���� ����3
        LineTo(hdc, (int)(280 * scale) + moveRight, (int)(214 * scale) + moveDown); //
        MoveToEx(hdc, (int)(480 * scale) + moveRight, (int)(207 * scale) + moveDown, NULL); // ������ ����1
        LineTo(hdc, (int)(410 * scale) + moveRight, (int)(207 * scale) + moveDown); //
        MoveToEx(hdc, (int)(480 * scale) + moveRight, (int)(210 * scale) + moveDown, NULL); // ������ ����2
        LineTo(hdc, (int)(410 * scale) + moveRight, (int)(210 * scale) + moveDown); //
        MoveToEx(hdc, (int)(480 * scale) + moveRight, (int)(214 * scale) + moveDown, NULL); // ������ ����3
        LineTo(hdc, (int)(410 * scale) + moveRight, (int)(214 * scale) + moveDown); //


        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        SelectObject(hdc, hOldPen); // ���� �� ����
        DeleteObject(hPen); // �� ����
  
}
void DrawRyan(HDC hdc, POINT start, POINT end) {
    // ���⿡�� drawryan �Լ� ȣ��
    int left = min(start.x, end.x);
    int top = min(start.y, end.y);
    int right = max(start.x, end.x);
    int bottom = max(start.y, end.y);

    drawryan(hWnd, hdc, left, top, right, bottom);
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // WinMain �Լ� ������ Ŀ�� �ڵ��� �ε��մϴ�.
    hCursorArrow = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    hWnd = CreateWindow(L"MyWindowClass", L"�߰����", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 0, 0, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return 0;

    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);

    // ���� �귯�� ����
    hBackgroundBrush = CreateSolidBrush(viewColor);

    // �׵θ� �� ����
    hBorderPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

    // ��ư 1 ����
    CreateWindow(L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_1, hInst, NULL);

    // ��ư 2 ����
    CreateWindow(L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36 + 130 + 16, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_2, hInst, NULL);

    // ��ư 3 ����
    CreateWindow(L"BUTTON", L"BonoBono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36 + (130 + 16) * 2, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_3, hInst, NULL);

    // ��ư 4 ����
    CreateWindow(L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36 + (130 + 16) * 3, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_4, hInst, NULL);

    // ��ư 5 ����
    CreateWindow(L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36 + (130 + 16) * 4, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_5, hInst, NULL);

    SetCursor(hCursorArrow);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // ���ҽ� ����
    DeleteObject(hBackgroundBrush);
    DeleteObject(hBorderPen);

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // ���� ����
        HBRUSH hBrush = CreateSolidBrush(viewColor);
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
        return 0;
    }
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SETCURSOR:
    {
        // ���콺 Ŀ���� ���� ��ġ�� ȭ�� ��ǥ�� �����ɴϴ�.
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        int margin = 8;
        int padding = 8;
        int width = clientRect.right - clientRect.left - 2 * margin - 2 * padding;
        int height = clientRect.bottom - clientRect.top - 2 * margin - 2 * padding;
        int innerMargin = 18;  // ���ο� �簢���� �׵θ� ����
        int innerWidth = width - 2 * innerMargin;
        int innerHeight = 320;  // �簢���� ����
        int innerX = margin + padding + innerMargin;
        int innerY = margin + padding + height - innerMargin - innerHeight;

        RECT rect;
        // ����� ������ ��ǥ�� �����մϴ�. �Ʒ��� ��ǥ�� ���÷� �����Ǹ� ������ ��ǥ�� �����ؾ� �մϴ�.
        int left = margin + padding + innerMargin;
        int top = margin + padding + height - innerMargin - innerHeight;
        int right = left + innerWidth;
        int bottom = top + innerHeight;

        // ���콺 Ŀ���� ��ġ�� ����� ���� ���� �ִ��� Ȯ��
        if (cursorPos.x >= left && cursorPos.x <= right && cursorPos.y >= top && cursorPos.y <= bottom)
        {
            SetCursor(LoadCursor(NULL, IDC_CROSS)); // ����� ���� ���� �ִٸ� CROSS Ŀ���� ����
        }
        else
        {
            SetCursor(hCursorArrow); // ����� ���� �ۿ� �ִٸ� �⺻ Ŀ���� ����
        }

        return TRUE; // Ŀ���� �����Ǿ����� �˸��ϴ�.
    }

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            if (!isPressSpace) { // �����̽��ٰ� ó�� ������ ���� �۵��ϵ��� ����
                isPressSpace = true;
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        break;
    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            isPressSpace = false; // �����̽��ٰ� ������ �� ���� ����
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        int margin = 8;
        int padding = 8;
        int width = clientRect.right - clientRect.left - 2 * margin - 2 * padding;
        int height = clientRect.bottom - clientRect.top - 2 * margin - 2 * padding;

        // ���� ĥ�ϱ�
        SelectObject(hdc, hBackgroundBrush);
        FillRect(hdc, &clientRect, hBackgroundBrush);

        // �׵θ� �׸���
        SelectObject(hdc, hBorderPen);
        Rectangle(hdc, margin + padding, margin + padding, margin + padding + width, margin + padding + height);

        // ���ο� �簢�� �׸���
        int innerMargin = 18;  // ���ο� �簢���� �׵θ� ����
        int innerWidth = width - 2 * innerMargin;
        int innerHeight = 320;  // �簢���� ����
        int innerX = margin + padding + innerMargin;
        int innerY = margin + padding + height - innerMargin - innerHeight;

        HBRUSH hInnerBrush = CreateSolidBrush(RGB(255, 255, 255));  // ��� ���
        HPEN hInnerPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));     // ������ �׵θ�

        SelectObject(hdc, hInnerBrush);
        SelectObject(hdc, hInnerPen);

        Rectangle(hdc, innerX, innerY, innerX + innerWidth, innerY + innerHeight);

        // ���ҽ� ����
        DeleteObject(hInnerBrush);
        DeleteObject(hInnerPen);

        drawbonobono(hWnd, hdc);
        if (isDrawing) {
            DrawRyan(hdc, startPoint, endPoint);
        }
        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_LBUTTONDOWN:
        if (wParam == MK_LBUTTON) {
            // ���� ���콺 ��ư�� ���� ���, �׸� �׸��� ����
            isDrawing = true;
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
        }
        break;

    case WM_MOUSEMOVE:
        if (isDrawing) {
            // �׸� �׸��Ⱑ ���� ���� ���, �� ������ ������Ʈ�ϰ� �ٽ� �׸���
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            RECT rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
            InvalidateRect(hWnd, &rect, TRUE);
            UpdateWindow(hWnd);
        }
        break;
   
    case WM_LBUTTONUP:
        if (isDrawing) {
            // ���� ���콺 ��ư�� ���� ���, �׸� �׸��� ����
            isDrawing = false;
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            RECT rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
            InvalidateRect(hWnd, &rect, TRUE);
            UpdateWindow(hWnd);
        }
        break;

    case WM_COMMAND:
    {
        // ��ư Ŭ�� �̺�Ʈ ó��
        if (HIWORD(wParam) == BN_CLICKED)
        {
            int buttonID = LOWORD(wParam);
            switch (buttonID)
            {
            case BUTTON_ID_1:
                // ��ư 1 Ŭ�� ó��
                MessageBox(hWnd, L"Box Clicked", L"Button Clicked", MB_OK);
                break;
            case BUTTON_ID_2:
                // ��ư 2 Ŭ�� ó��
                MessageBox(hWnd, L"Circle", L"Button Clicked", MB_OK);
                break;
            case BUTTON_ID_3:
                isBoxVisible = !isBoxVisible; // ���뺸�� ǥ�� ���¸� ���� (���̸� �����, ������ ������ ���̰� ����)
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case BUTTON_ID_4:
                // ��ư 4 Ŭ�� ó��
                isDrawing = true;
                break;
            case BUTTON_ID_5:
                // ��ư 5 Ŭ�� ó��
                MessageBox(hWnd, L"Cube Clicked", L"Button Clicked", MB_OK);
                break;
            }
        }
        return 0;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}