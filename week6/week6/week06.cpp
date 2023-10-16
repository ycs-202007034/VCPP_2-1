#include <windows.h>

// 사용자 도형의 현재 위치
int userX = 50;
int userY = 50;
int prevUserX = 0; // 이전 위치를 저장하는 변수
int prevUserY = 0;

// 타겟 도형의 위치
RECT rect_target = { 150, 150, 250, 250 }; // 타겟 도형 좌표

// hit를 출력할 문자열
WCHAR hitText[] = L"hit";

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    RECT rect_user = { prevUserX, prevUserY, prevUserX + 10, prevUserY + 10 }; // 이전 사용자 도형 좌표
    RECT new_rect_user = { userX, userY, userX + 10, userY + 10 }; // 새로운 사용자 도형 좌표
    HBRUSH hBrush_user = CreateSolidBrush(RGB(51, 204, 0));
    HBRUSH hBrush_target = CreateSolidBrush(RGB(204, 102, 255));
    HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255));

    switch (uMsg)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            prevUserX = userX;
            prevUserY = userY;
            userX--;
            break;
        case VK_RIGHT:
            prevUserX = userX;
            prevUserY = userY;
            userX++;
            break;
        case VK_UP:
            prevUserX = userX;
            prevUserY = userY;
            userY--;
            break;
        case VK_DOWN:
            prevUserX = userX;
            prevUserY = userY;
            userY++;
            break;
        }

        // 이전 위치에 그린 도형을 지우기
        FillRect(hdc, &rect_user, hBrush_eraser);

        // 충돌 여부 확인
        if (userX + 10 >= rect_target.left && userX <= rect_target.right &&
            userY + 10 >= rect_target.top && userY <= rect_target.bottom)
        {
            // 충돌 시 "hit" 문자열을 출력
            TextOut(hdc, 10, 10, hitText, wcslen(hitText));
        }

        // 사용자 도형을 이동한 위치에 그림
        InvalidateRect(hwnd, &new_rect_user, TRUE);
        break;
    case WM_KEYUP:
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FillRect(hdc, &new_rect_user, hBrush_user);
        FillRect(hdc, &rect_target, hBrush_target);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    DeleteObject(hBrush_user);
    DeleteObject(hBrush_target);
    DeleteObject(hBrush_eraser);

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"WindowClass";

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    RECT rect = { 0, 0, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

    HWND hwnd = CreateWindowEx(
        0,
        L"WindowClass",
        L"Hit Detection",
        WS_OVERLAPPEDWINDOW,
        100, 100,
        rect.right - rect.left, rect.bottom - rect.top,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}