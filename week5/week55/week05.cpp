#include <Windows.h>

RECT rectangle = { 0, 0, 0, 0 }; 
RECT previousRectangle = { 0, 0, 0, 0 }; 
bool isDrawing = false; 
bool isMoving = false;  
POINT startPoint; 
POINT offset; 

// MoveRect �Լ� �߰�
void MoveRect(RECT* rect, int newX, int newY)
{
    int width = rect->right - rect->left;
    int height = rect->bottom - rect->top;

    rect->left = newX;
    rect->top = newY;
    rect->right = newX + width;
    rect->bottom = newY + height;
}

// â ���ν��� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (!isDrawing && !isMoving)
        {
            // Ŭ���� ��ġ�� ���� ������ ���� �ȿ� �ִ��� Ȯ��
            if (PtInRect(&rectangle, { LOWORD(lParam), HIWORD(lParam) }))
            {
                isMoving = true;
                offset.x = LOWORD(lParam) - rectangle.left;
                offset.y = HIWORD(lParam) - rectangle.top;
            }
            else
            {
                // Ŭ���� ��ġ�� ���� �׸� �簢���� ���� �ȿ� �ִ��� Ȯ��
                RECT clientRect;
                GetClientRect(hWnd, &clientRect);
                if (PtInRect(&clientRect, { LOWORD(lParam), HIWORD(lParam) }))
                {
                    isDrawing = true;
                    startPoint.x = LOWORD(lParam);
                    startPoint.y = HIWORD(lParam);

                    // ���� ���� �ʱ�ȭ
                    previousRectangle = rectangle;
                    rectangle = { 0, 0, 0, 0 };

                    // ȭ�� �ٽ� �׸���
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
        }
        break;

    case WM_LBUTTONUP:
        if (isDrawing)
        {
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            if (PtInRect(&clientRect, startPoint))
            {
                // ���� ������ ��ġ�� ����
                previousRectangle = rectangle;

                rectangle.left = startPoint.x;
                rectangle.top = startPoint.y;
                rectangle.right = LOWORD(lParam);
                rectangle.bottom = HIWORD(lParam);
            }
            isDrawing = false;
            InvalidateRect(hWnd, NULL, TRUE); // ȭ�� �ٽ� �׸���
        }
        else if (isMoving)
        {
            isMoving = false;
        }
        break;

    case WM_MOUSEMOVE:
        if (isDrawing)
        {
            // ���콺 �̵� ���� �� �簢�� �׸��� ����� ��� �簢�� ������Ʈ
            HDC hdc = GetDC(hWnd);
            HBRUSH greenBrush = CreateSolidBrush(RGB(204, 255, 153)); 
            SelectObject(hdc, greenBrush);
         

            // ���� ������ ����� ���� ���� ��ġ�� �簢���� �׸��ϴ�.
            Rectangle(hdc, previousRectangle.left, previousRectangle.top, previousRectangle.right, previousRectangle.bottom);

            // ���ο� ��ġ�� �簢���� �׸��ϴ�.
            Rectangle(hdc, startPoint.x, startPoint.y, LOWORD(lParam), HIWORD(lParam));

            DeleteObject(greenBrush);
            ReleaseDC(hWnd, hdc);

            // ���� ������ ��ġ�� ������Ʈ
            rectangle.left = startPoint.x;
            rectangle.top = startPoint.y;
            rectangle.right = LOWORD(lParam);
            rectangle.bottom = HIWORD(lParam);
        }
        else if (isMoving)
        {
            // ���콺 �̵� ����� ��� ���� �̵� ����
            int newX = LOWORD(lParam) - offset.x;
            int newY = HIWORD(lParam) - offset.y;

            // ���� ��ġ�� ������ �̵�
            MoveRect(&rectangle, newX, newY);

            // ȭ�� �ٽ� �׸���
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_RBUTTONDOWN:
        // ������ ��ư ���� �� �ƹ� �۾� ����
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HBRUSH greenBrush = CreateSolidBrush(RGB(204, 255, 000)); 
        SelectObject(hdc, greenBrush);
        Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
        DeleteObject(greenBrush);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_CLOSE:
        // â �ݱ� ��ư�� ���� �� ���α׷� ����
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        // ���α׷� ����
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;

    // ������ Ŭ���� ���
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"MyWindowClass";
    RegisterClassEx(&wcex);

    // ������ ����
    hWnd = CreateWindow(L"MyWindowClass", L"202007034 ����", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return 1;
    }

    // ������ ǥ��
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // �޽��� ����
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}