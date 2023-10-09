#include <Windows.h>

RECT rectangle = { 0, 0, 0, 0 }; 
RECT previousRectangle = { 0, 0, 0, 0 }; 
bool isDrawing = false; 
bool isMoving = false;  
POINT startPoint; 
POINT offset; 

// MoveRect 함수 추가
void MoveRect(RECT* rect, int newX, int newY)
{
    int width = rect->right - rect->left;
    int height = rect->bottom - rect->top;

    rect->left = newX;
    rect->top = newY;
    rect->right = newX + width;
    rect->bottom = newY + height;
}

// 창 프로시저 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (!isDrawing && !isMoving)
        {
            // 클릭한 위치가 기존 도형의 범위 안에 있는지 확인
            if (PtInRect(&rectangle, { LOWORD(lParam), HIWORD(lParam) }))
            {
                isMoving = true;
                offset.x = LOWORD(lParam) - rectangle.left;
                offset.y = HIWORD(lParam) - rectangle.top;
            }
            else
            {
                // 클릭한 위치가 새로 그릴 사각형의 범위 안에 있는지 확인
                RECT clientRect;
                GetClientRect(hWnd, &clientRect);
                if (PtInRect(&clientRect, { LOWORD(lParam), HIWORD(lParam) }))
                {
                    isDrawing = true;
                    startPoint.x = LOWORD(lParam);
                    startPoint.y = HIWORD(lParam);

                    // 기존 도형 초기화
                    previousRectangle = rectangle;
                    rectangle = { 0, 0, 0, 0 };

                    // 화면 다시 그리기
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
                // 현재 도형의 위치를 저장
                previousRectangle = rectangle;

                rectangle.left = startPoint.x;
                rectangle.top = startPoint.y;
                rectangle.right = LOWORD(lParam);
                rectangle.bottom = HIWORD(lParam);
            }
            isDrawing = false;
            InvalidateRect(hWnd, NULL, TRUE); // 화면 다시 그리기
        }
        else if (isMoving)
        {
            isMoving = false;
        }
        break;

    case WM_MOUSEMOVE:
        if (isDrawing)
        {
            // 마우스 이동 중일 때 사각형 그리기 모드인 경우 사각형 업데이트
            HDC hdc = GetDC(hWnd);
            HBRUSH greenBrush = CreateSolidBrush(RGB(204, 255, 153)); 
            SelectObject(hdc, greenBrush);
         

            // 이전 도형을 지우기 위해 이전 위치로 사각형을 그립니다.
            Rectangle(hdc, previousRectangle.left, previousRectangle.top, previousRectangle.right, previousRectangle.bottom);

            // 새로운 위치로 사각형을 그립니다.
            Rectangle(hdc, startPoint.x, startPoint.y, LOWORD(lParam), HIWORD(lParam));

            DeleteObject(greenBrush);
            ReleaseDC(hWnd, hdc);

            // 현재 도형의 위치를 업데이트
            rectangle.left = startPoint.x;
            rectangle.top = startPoint.y;
            rectangle.right = LOWORD(lParam);
            rectangle.bottom = HIWORD(lParam);
        }
        else if (isMoving)
        {
            // 마우스 이동 모드인 경우 도형 이동 수행
            int newX = LOWORD(lParam) - offset.x;
            int newY = HIWORD(lParam) - offset.y;

            // 현재 위치로 도형을 이동
            MoveRect(&rectangle, newX, newY);

            // 화면 다시 그리기
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_RBUTTONDOWN:
        // 오른쪽 버튼 누를 때 아무 작업 없음
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
        // 창 닫기 버튼을 누를 때 프로그램 종료
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        // 프로그램 종료
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

    // 윈도우 클래스 등록
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"MyWindowClass";
    RegisterClassEx(&wcex);

    // 윈도우 생성
    hWnd = CreateWindow(L"MyWindowClass", L"202007034 조희섭", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return 1;
    }

    // 윈도우 표시
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 메시지 루프
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}