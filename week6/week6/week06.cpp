#include <windows.h>

// ����� ������ ���� ��ġ
int userX = 50;
int userY = 50;
int prevUserX = 0; // ���� ��ġ�� �����ϴ� ����
int prevUserY = 0;

// Ÿ�� ������ ��ġ
RECT rect_target = { 150, 150, 250, 250 }; // Ÿ�� ���� ��ǥ

// hit�� ����� ���ڿ�
WCHAR hitText[] = L"hit";

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    RECT rect_user = { prevUserX, prevUserY, prevUserX + 10, prevUserY + 10 }; // ���� ����� ���� ��ǥ
    RECT new_rect_user = { userX, userY, userX + 10, userY + 10 }; // ���ο� ����� ���� ��ǥ
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

        // ���� ��ġ�� �׸� ������ �����
        FillRect(hdc, &rect_user, hBrush_eraser);

        // �浹 ���� Ȯ��
        if (userX + 10 >= rect_target.left && userX <= rect_target.right &&
            userY + 10 >= rect_target.top && userY <= rect_target.bottom)
        {
            // �浹 �� "hit" ���ڿ��� ���
            TextOut(hdc, 10, 10, hitText, wcslen(hitText));
        }

        // ����� ������ �̵��� ��ġ�� �׸�
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