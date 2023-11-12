#include <Windows.h>

HINSTANCE hInst;
HWND hWnd;
HCURSOR hCursorArrow; // 화살표 커서 핸들
COLORREF viewColor = RGB(255, 240, 200);
HBRUSH hBackgroundBrush; // 배경색 브러시
HPEN hBorderPen;        // 테두리 펜

bool isBoxVisible = false;
bool isPressSpace = false;
bool isDrawing = false; // 그림 그리기 진행 여부를 나타내는 플래그
POINT startPoint;
POINT endPoint;
// 버튼 식별자
#define BUTTON_ID_1 1001
#define BUTTON_ID_2 1002
#define BUTTON_ID_3 1003
#define BUTTON_ID_4 1004
#define BUTTON_ID_5 1005

void drawbonobono(HWND hWnd, HDC hdc) {
    RECT circle;
    GetClientRect(hWnd, &circle);

    int moveRight = 110; //오른쪽으로 이동할 픽셀 수
    int moveDown = 25; // 아래로 이동할 픽셀 수
    float scale = 0.8; // 보노보노의 크기를 조절하기 위한 비율

    if (isBoxVisible) {
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, face);
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(100 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(458 * scale) + moveDown); // 얼굴
        SelectObject(hdc, mouse);
        Ellipse(hdc, (int)(315 * scale) + moveRight, (int)(300 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(380 * scale) + moveDown); // 입

        SelectObject(hdc, white);
        Ellipse(hdc, (int)(270 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(340 * scale) + moveRight, (int)(345 * scale) + moveDown); // 코왼쪽
        Ellipse(hdc, (int)(340 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(410 * scale) + moveRight, (int)(345 * scale) + moveDown); // 코 오른쪽
        SelectObject(hdc, black);
        Ellipse(hdc, (int)(320 * scale) + moveRight, (int)(275 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(315 * scale) + moveDown); // 코
        Ellipse(hdc, (int)(185 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(195 * scale) + moveRight, (int)(260 * scale) + moveDown); // 왼쪽눈
        Ellipse(hdc, (int)(490 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(500 * scale) + moveRight, (int)(260 * scale) + moveDown); // 오른쪽눈
        SelectObject(hdc, white);
        Ellipse(hdc, (int)(187 * scale) + moveRight, (int)(245 * scale) + moveDown, (int)(193 * scale) + moveRight, (int)(255 * scale) + moveDown); // 왼쪽눈
        Ellipse(hdc, (int)(492 * scale) + moveRight, (int)(245 * scale) + moveDown, (int)(498 * scale) + moveRight, (int)(255 * scale) + moveDown); // 오른쪽눈

        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // 왼쪽수염1
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // 왼쪽 수염2
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // 오른쪽 수염1
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // 오른쪽 수염2
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        DeleteObject(mouse);
        SelectObject(hdc, hOldPen); // 이전 펜 선택
        DeleteObject(hPen); // 펜 삭제
    }
    if (isBoxVisible == true && isPressSpace == true) {


        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(127, 200, 255));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH mouse = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, face);
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(100 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(458 * scale) + moveDown); //얼굴
        SelectObject(hdc, mouse);
        Ellipse(hdc, (int)(315 * scale) + moveRight, (int)(300 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(380 * scale) + moveDown); //입

        SelectObject(hdc, white);
        Ellipse(hdc, (int)(270 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(340 * scale) + moveRight, (int)(345 * scale) + moveDown); // 코왼쪽
        Ellipse(hdc, (int)(340 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(410 * scale) + moveRight, (int)(345 * scale) + moveDown); // 코 오른쪽
        SelectObject(hdc, black);

        Ellipse(hdc, (int)(320 * scale) + moveRight, (int)(275 * scale) + moveDown, (int)(365 * scale) + moveRight, (int)(315 * scale) + moveDown); // 코 

        MoveToEx(hdc, (int)(185 * scale) + moveRight, (int)(240 * scale) + moveDown, NULL); // 왼쪽 눈
        LineTo(hdc, (int)(200 * scale) + moveRight, (int)(260 * scale) + moveDown); //
        MoveToEx(hdc, (int)(200 * scale) + moveRight, (int)(260 * scale) + moveDown, NULL); // 오른쪽 눈
        LineTo(hdc, (int)(185 * scale) + moveRight, (int)(280 * scale) + moveDown); //

        MoveToEx(hdc, (int)(505 * scale) + moveRight, (int)(240 * scale) + moveDown, NULL); // 오른쪽 수염1
        LineTo(hdc, (int)(490 * scale) + moveRight, (int)(260 * scale) + moveDown); //
        MoveToEx(hdc, (int)(490 * scale) + moveRight, (int)(260 * scale) + moveDown, NULL); // 오른쪽 수염2
        LineTo(hdc, (int)(505 * scale) + moveRight, (int)(280 * scale) + moveDown); //

        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // 왼쪽수염1
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(255 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // 왼쪽 수염2
        LineTo(hdc, (int)(295 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(300 * scale) + moveDown, NULL); // 오른쪽 수염1
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(310 * scale) + moveDown); //
        MoveToEx(hdc, (int)(430 * scale) + moveRight, (int)(340 * scale) + moveDown, NULL); // 오른쪽 수염2
        LineTo(hdc, (int)(380 * scale) + moveRight, (int)(320 * scale) + moveDown); //

        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        DeleteObject(mouse);
        SelectObject(hdc, hOldPen); // 이전 펜 선택
        DeleteObject(hPen); // 펜 삭제
    }
}
void drawryan(HWND hWnd, HDC hdc ,int left, int top, int right, int bottom){
    RECT circle;
    GetClientRect(hWnd, &circle);

    int moveRight = 110; //오른쪽으로 이동할 픽셀 수
    int moveDown = 25; // 아래로 이동할 픽셀 수
    float scale = 0.8; 
   
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH face = CreateSolidBrush(RGB(255, 200, 15));
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));

        SelectObject(hdc, face);
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(85 * scale) + moveDown, (int)(320 * scale) + moveRight, (int)(250 * scale) + moveDown);// 왼쪽귀
        Ellipse(hdc, (int)(365 * scale) + moveRight, (int)(85 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(250 * scale) + moveDown);// 오른쪽귀
        Ellipse(hdc, (int)(150 * scale) + moveRight, (int)(100 * scale) + moveDown, (int)(535 * scale) + moveRight, (int)(458 * scale) + moveDown);// 얼굴
        SelectObject(hdc, white);
        Ellipse(hdc, (int)(270 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(340 * scale) + moveRight, (int)(345 * scale) + moveDown); // 코왼쪽
        Ellipse(hdc, (int)(340 * scale) + moveRight, (int)(290 * scale) + moveDown, (int)(410 * scale) + moveRight, (int)(345 * scale) + moveDown); // 코 오른쪽
        SelectObject(hdc, black);
        Ellipse(hdc, (int)(235 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(255 * scale) + moveRight, (int)(260 * scale) + moveDown); // 왼쪽눈
        Ellipse(hdc, (int)(430 * scale) + moveRight, (int)(240 * scale) + moveDown, (int)(450 * scale) + moveRight, (int)(260 * scale) + moveDown); // 오른쪽눈
        SelectObject(hdc, black);
        MoveToEx(hdc, (int)(210 * scale) + moveRight, (int)(207 * scale) + moveDown, NULL); // 왼쪽 눈썹1
        LineTo(hdc, (int)(280 * scale) + moveRight, (int)(207 * scale) + moveDown); //
        MoveToEx(hdc, (int)(210 * scale) + moveRight, (int)(210 * scale) + moveDown, NULL); // 왼쪽 눈썹2
        LineTo(hdc, (int)(280 * scale) + moveRight, (int)(210 * scale) + moveDown); //
        MoveToEx(hdc, (int)(210 * scale) + moveRight, (int)(214 * scale) + moveDown, NULL); // 왼쪽 눈썹3
        LineTo(hdc, (int)(280 * scale) + moveRight, (int)(214 * scale) + moveDown); //
        MoveToEx(hdc, (int)(480 * scale) + moveRight, (int)(207 * scale) + moveDown, NULL); // 오른쪽 눈썹1
        LineTo(hdc, (int)(410 * scale) + moveRight, (int)(207 * scale) + moveDown); //
        MoveToEx(hdc, (int)(480 * scale) + moveRight, (int)(210 * scale) + moveDown, NULL); // 오른쪽 눈썹2
        LineTo(hdc, (int)(410 * scale) + moveRight, (int)(210 * scale) + moveDown); //
        MoveToEx(hdc, (int)(480 * scale) + moveRight, (int)(214 * scale) + moveDown, NULL); // 오른쪽 눈썹3
        LineTo(hdc, (int)(410 * scale) + moveRight, (int)(214 * scale) + moveDown); //


        DeleteObject(face);
        DeleteObject(black);
        DeleteObject(white);
        SelectObject(hdc, hOldPen); // 이전 펜 선택
        DeleteObject(hPen); // 펜 삭제
  
}
void DrawRyan(HDC hdc, POINT start, POINT end) {
    // 여기에서 drawryan 함수 호출
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

    // WinMain 함수 내에서 커서 핸들을 로드합니다.
    hCursorArrow = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    hWnd = CreateWindow(L"MyWindowClass", L"중간고사", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 0, 0, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return 0;

    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);

    // 배경색 브러시 생성
    hBackgroundBrush = CreateSolidBrush(viewColor);

    // 테두리 펜 생성
    hBorderPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

    // 버튼 1 생성
    CreateWindow(L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_1, hInst, NULL);

    // 버튼 2 생성
    CreateWindow(L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36 + 130 + 16, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_2, hInst, NULL);

    // 버튼 3 생성
    CreateWindow(L"BUTTON", L"BonoBono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36 + (130 + 16) * 2, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_3, hInst, NULL);

    // 버튼 4 생성
    CreateWindow(L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 36 + (130 + 16) * 3, 26, 130, 48, hWnd, (HMENU)BUTTON_ID_4, hInst, NULL);

    // 버튼 5 생성
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

    // 리소스 정리
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
        // 배경색 설정
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
        // 마우스 커서의 현재 위치를 화면 좌표로 가져옵니다.
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        int margin = 8;
        int padding = 8;
        int width = clientRect.right - clientRect.left - 2 * margin - 2 * padding;
        int height = clientRect.bottom - clientRect.top - 2 * margin - 2 * padding;
        int innerMargin = 18;  // 새로운 사각형과 테두리 간격
        int innerWidth = width - 2 * innerMargin;
        int innerHeight = 320;  // 사각형의 높이
        int innerX = margin + padding + innerMargin;
        int innerY = margin + padding + height - innerMargin - innerHeight;

        RECT rect;
        // 드로잉 영역의 좌표를 정의합니다. 아래의 좌표는 예시로 제공되며 적절한 좌표로 수정해야 합니다.
        int left = margin + padding + innerMargin;
        int top = margin + padding + height - innerMargin - innerHeight;
        int right = left + innerWidth;
        int bottom = top + innerHeight;

        // 마우스 커서의 위치가 드로잉 영역 내에 있는지 확인
        if (cursorPos.x >= left && cursorPos.x <= right && cursorPos.y >= top && cursorPos.y <= bottom)
        {
            SetCursor(LoadCursor(NULL, IDC_CROSS)); // 드로잉 영역 내에 있다면 CROSS 커서로 설정
        }
        else
        {
            SetCursor(hCursorArrow); // 드로잉 영역 밖에 있다면 기본 커서로 설정
        }

        return TRUE; // 커서가 설정되었음을 알립니다.
    }

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            if (!isPressSpace) { // 스페이스바가 처음 눌렸을 때만 작동하도록 변경
                isPressSpace = true;
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        break;
    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            isPressSpace = false; // 스페이스바가 놓였을 때 상태 변경
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

        // 배경색 칠하기
        SelectObject(hdc, hBackgroundBrush);
        FillRect(hdc, &clientRect, hBackgroundBrush);

        // 테두리 그리기
        SelectObject(hdc, hBorderPen);
        Rectangle(hdc, margin + padding, margin + padding, margin + padding + width, margin + padding + height);

        // 새로운 사각형 그리기
        int innerMargin = 18;  // 새로운 사각형과 테두리 간격
        int innerWidth = width - 2 * innerMargin;
        int innerHeight = 320;  // 사각형의 높이
        int innerX = margin + padding + innerMargin;
        int innerY = margin + padding + height - innerMargin - innerHeight;

        HBRUSH hInnerBrush = CreateSolidBrush(RGB(255, 255, 255));  // 흰색 배경
        HPEN hInnerPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));     // 검정색 테두리

        SelectObject(hdc, hInnerBrush);
        SelectObject(hdc, hInnerPen);

        Rectangle(hdc, innerX, innerY, innerX + innerWidth, innerY + innerHeight);

        // 리소스 정리
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
            // 왼쪽 마우스 버튼이 눌린 경우, 그림 그리기 시작
            isDrawing = true;
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
        }
        break;

    case WM_MOUSEMOVE:
        if (isDrawing) {
            // 그림 그리기가 진행 중인 경우, 끝 지점을 업데이트하고 다시 그리기
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            RECT rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
            InvalidateRect(hWnd, &rect, TRUE);
            UpdateWindow(hWnd);
        }
        break;
   
    case WM_LBUTTONUP:
        if (isDrawing) {
            // 왼쪽 마우스 버튼이 놓인 경우, 그림 그리기 중지
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
        // 버튼 클릭 이벤트 처리
        if (HIWORD(wParam) == BN_CLICKED)
        {
            int buttonID = LOWORD(wParam);
            switch (buttonID)
            {
            case BUTTON_ID_1:
                // 버튼 1 클릭 처리
                MessageBox(hWnd, L"Box Clicked", L"Button Clicked", MB_OK);
                break;
            case BUTTON_ID_2:
                // 버튼 2 클릭 처리
                MessageBox(hWnd, L"Circle", L"Button Clicked", MB_OK);
                break;
            case BUTTON_ID_3:
                isBoxVisible = !isBoxVisible; // 보노보노 표시 상태를 변경 (보이면 숨기고, 숨겨져 있으면 보이게 변경)
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case BUTTON_ID_4:
                // 버튼 4 클릭 처리
                isDrawing = true;
                break;
            case BUTTON_ID_5:
                // 버튼 5 클릭 처리
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