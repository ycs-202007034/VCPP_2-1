#ifdef _DEBUG_
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

#include <windows.h>
#include "DrawObject.h"
#include "Interface.h"

#define S_Box 1
#define S_Circle 2
#define S_Bonobono 3
#define S_Ryan 4
#define S_Cube 5

void SetMinMaxWindowSizes(HWND hWnd, MINMAXINFO* minMaxInfo, int minWidth, int minHeight) {
	// 윈도우 영역 크기 정의
	RECT rect = { 0, 0, minWidth, minHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// MINMAXINFO 구조체를 사용하여 창 크기 제한 설정
	minMaxInfo->ptMinTrackSize.x = width; // 최소 너비
	minMaxInfo->ptMinTrackSize.y = height; // 최소 높이
	minMaxInfo->ptMaxTrackSize.x = width; // 최대 너비
	minMaxInfo->ptMaxTrackSize.y = height; // 최대 높이
}
void UpdateCursor(HWND hwnd, const RECT& drawing_area) {
	// 커서의 위치를 가져옵니다.
	POINT pt;
	GetCursorPos(&pt);
	// 해당 위치를 클라이언트 영역의 좌표로 변환합니다.
	ScreenToClient(hwnd, &pt);
	// 드로잉 영역 내에 커서가 있는지 확인합니다.
	if (PtInRect(&drawing_area, pt))
	{
		// 드로잉 영역 안에 있으면 커서를 크로스로 변경합니다.
		SetCursor(LoadCursor(NULL, IDC_CROSS));
	}
	else
	{
		// 드로잉 영역 밖에 있으면 기본 커서를 사용합니다.
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
}
void HandleMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseLButtonPressed, BOOL& isMouseRButtonPressed, POINT& startPoint, POINT& endPoint, RECT& Box, RECT& Circle, POINT& m_startPoint, POINT& m_endPoint, POINT& startPointSaved, POINT& endPointSaved, POINT& distance) {
	// 도형의 종류가 Circle이고 마우스 왼쪽 버튼이 눌린 경우
	if (Shape == S_Circle && isMouseLButtonPressed) {
		endPoint = { LOWORD(lParam), HIWORD(lParam) };

		int radius = min(abs(startPoint.x - endPoint.x), abs(startPoint.y - endPoint.y)); // 반지름은 두 방향 중 작은 값으로 설정

		int centerX = (startPoint.x + endPoint.x) / 2; // 중심의 x 좌표
		int centerY = (startPoint.y + endPoint.y) / 2; // 중심의 y 좌표

		Circle.left = centerX - radius;
		Circle.top = centerY - radius;
		Circle.right = centerX + radius;
		Circle.bottom = centerY + radius;

		InvalidateRect(hwnd, &drawing_area, TRUE);
	}

	// 도형의 종류가 Circle이고 마우스 오른쪽 버튼이 눌린 경우
	if (Shape == S_Circle && isMouseRButtonPressed) {

		// 현재 마우스 위치를 가져옵니다.
		POINT currentPoint = { LOWORD(lParam), HIWORD(lParam) };

		// 이전 endPoint 저장
		endPointSaved = endPoint;

		// 마우스 이동 거리 계산
		int deltaX = currentPoint.x - endPoint.x;

		if (abs(deltaX) >= 100) {
			// 이동 거리가 100px 이상이면 크기 조정
			int radius = (Circle.right - Circle.left) / 2;

			if (deltaX > 0) {
				// 우측으로 이동한 경우
				radius *= 2; // 2배 확대
			}
			else {
				// 좌측으로 이동한 경우
				radius /= 2; // 절반으로 축소
			}

			// 원의 중심을 유지하면서 크기를 조정
			int centerX = (Circle.left + Circle.right) / 2;
			int centerY = (Circle.top + Circle.bottom) / 2;

			Circle.left = centerX - radius;
			Circle.top = centerY - radius;
			Circle.right = centerX + radius;
			Circle.bottom = centerY + radius;

			// endPoint 업데이트
			endPoint = currentPoint;

			// 화면을 갱신하여 원을 그립니다.
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}

	// 도형의 종류가 Box이고 마우스 왼쪽 버튼이 눌린 경우
	if (Shape == S_Box && isMouseLButtonPressed) {
		// 마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 끝점의 좌표값으로 설정
		endPoint = { LOWORD(lParam), HIWORD(lParam) };

		// 사각형 좌표값 정렬(사각형을 반대로 그리는 경우를 대비하여)
		Box.left = min(startPoint.x, endPoint.x);
		Box.top = min(startPoint.y, endPoint.y);
		Box.right = max(startPoint.x, endPoint.x);
		Box.bottom = max(startPoint.y, endPoint.y);

		// 화면을 갱신하여 사각형을 그립니다.
		InvalidateRect(hwnd, &drawing_area, TRUE);
	}

	// 도형의 종류가 Box이고 마우스 오른쪽 버튼이 눌린 경우
	if (Shape == S_Box && isMouseRButtonPressed) {
		// 마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 이동이 끝난 좌표값으로 설정
		m_endPoint.x = LOWORD(lParam);
		m_endPoint.y = HIWORD(lParam);

		// 사각형 이동이 끝난 좌표값과 사각형 이동이 시작된 좌표값의 차를 통해 마우스의 이동 거리를 계산
		distance.x = m_endPoint.x - m_startPoint.x;
		distance.y = m_endPoint.y - m_startPoint.y;

		// 사각형의 좌표값을 기존에 저장해놓은 좌표값에 마우스의 이동거리 만큼을 더한 좌표값으로 설정
		Box.left = startPointSaved.x + distance.x;
		Box.top = startPointSaved.y + distance.y;
		Box.right = endPointSaved.x + distance.x;
		Box.bottom = endPointSaved.y + distance.y;

		// 화면을 갱신하여 사각형을 그립니다.
		InvalidateRect(hwnd, &drawing_area, TRUE);
	}

	// 도형의 종류가 Ryan이고 마우스 왼쪽 버튼이 눌린 경우
	if (Shape == S_Ryan && isMouseLButtonPressed) {
		// 마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 끝점의 좌표값으로 설정
		endPoint = { LOWORD(lParam), HIWORD(lParam) };

		// 화면을 갱신하여 Ryan을 그립니다.
		InvalidateRect(hwnd, &drawing_area, TRUE);
	}
}

void HandleLeftButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, POINT& startPoint, POINT& endPoint, BOOL& isMouseLButtonPressed, int& Shape, const RECT& drawing_area) {
	// 좌표값을 가져와서 시작 좌표값에 할당
	startPoint = { LOWORD(lParam), HIWORD(lParam) };
	endPoint = startPoint;

	// 도형의 종류가 Circle, Box, Ryan인 경우에만 처리
	if (Shape == S_Circle || Shape == S_Box || Shape == S_Ryan) {
		// 시작점이 드로잉 영역 안에 있다면
		if (PtInRect(&drawing_area, startPoint)) {
			// 체크 변수의 값을 TRUE로 설정
			isMouseLButtonPressed = TRUE;
		}
	}
}

void HandleRightButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseRButtonPressed, POINT& startPointSaved, POINT& endPointSaved, POINT& endPoint, POINT& m_startPoint, RECT& Box, RECT& Circle) {
	// 도형의 종류가 Circle인 경우
	if (Shape == S_Circle) {
		// 시작 좌표값을 백업(endPoint의 초기값은 startPointSaved와 동일) 
		startPointSaved = { LOWORD(lParam), HIWORD(lParam) };
		endPoint = startPointSaved;

		// 시작점이 드로잉 영역 안에 있다면
		if (PtInRect(&drawing_area, startPointSaved) && PtInRect(&Circle, startPointSaved)) {
			// 체크 변수의 값을 TRUE로 설정
			isMouseRButtonPressed = TRUE;
		}
	}

	// 도형의 종류가 Box인 경우
	if (Shape == S_Box) {
		// 마우스 오른쪽 버튼을 눌렀을 때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 이동이 시작된 좌표값으로 설정
		m_startPoint.x = LOWORD(lParam);
		m_startPoint.y = HIWORD(lParam);

		// 마우스 오른쪽 버튼을 기존에 만들어진 사각형 영역 안에서 눌렀다면
		if (PtInRect(&drawing_area, m_startPoint) && PtInRect(&Box, m_startPoint))
		{
			// 체크 변수의 값을 TRUE로 설정
			isMouseRButtonPressed = TRUE;

			// 기존 사각형의 좌표값을 Saved 변수에 저장
			startPointSaved.x = Box.left;
			startPointSaved.y = Box.top;
			endPointSaved.x = Box.right;
			endPointSaved.y = Box.bottom;
		}
	}
}
// 좌표값을 저장할 전역 변수 선언
// 시작과 끝 좌표와 좌표값 백업, 마우스 이동 좌표, 거리값 좌표, 도형에 대한 좌표, 드로잉 영역에 대한 좌표
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT m_startPoint = { 0 };
POINT m_endPoint = { 0 };
POINT distance = { 0 };
POINT startPointSaved = { 0 };
POINT endPointSaved = { 0 };
RECT Box = { 0 };
RECT Circle = { 0 };
RECT drawing_area = { 0 };

// 누른 버튼의 도형의 종류를 저장할 전역 변수 선언
int Shape = 0;

// 마우스와 스페이스의 입력상태 체크 전역 변수 선언
int isMouseLButtonPressed = FALSE;	// 마우스 왼쪽 버튼이 눌린 상태인지 체크
int isMouseRButtonPressed = FALSE;	// 마우스 오른쪽 버튼이 눌린 상태인지 체크
int isSpaceButtonPressed = FALSE;	// 스페이스 버튼이 눌린 상태인지 체크

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// 창의 최소 및 최대 크기에 대한 정보 제어
	case WM_GETMINMAXINFO:
	{
		SetMinMaxWindowSizes(hwnd, (MINMAXINFO*)lParam, 800, 480);
	}
	break;

	// 키가 눌린 상태인 경우
	case WM_KEYDOWN:
	{
		// 만약에 스페이스키가 눌린 상태라면
		if (wParam == VK_SPACE) {
			// 체크 변수의 값을 TRUE로 설정
			isSpaceButtonPressed = TRUE;

			// WM_PAINT 메시지 호출
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	// 키가 떼진 상태라면
	case WM_KEYUP:
	{
		// 만약에 스페이스키가 떼진 상태라면
		if (wParam == VK_SPACE) {
			// 체크 변수의 값을 FALSE으로 설정
			isSpaceButtonPressed = FALSE;

			// WM_PAINT 메시지 호출
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	// 버튼이 눌렸다면
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam); // 버튼의 ID를 가져옵니다.

		// 버튼의 아이디에 따라 처리
		switch (wmId)
		{
			// Box 버튼이라면
		case 1:
		{
			Shape = S_Box;								// 도형의 종류를 Box로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			Box = { 0 };								// Box의 좌표값을 0으로 초기화
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// Circle 버튼이라면
		case 2:
		{
			Shape = S_Circle;							// 도형의 종류를 Circle로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			Circle = { 0 };								// Circle의 좌표값을 0으로 초기화
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// Bonobono 버튼이라면
		case 3:
		{
			Shape = S_Bonobono;							// 도형의 종류를 Bonobono로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			InvalidateRect(hwnd, &drawing_area, TRUE);	// WM_PAINT 메시지 호출
			break;
		}

		// Ryan 버튼이라면
		case 4:
		{
			Shape = S_Ryan;								// 도형의 종류를 Ryan으로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			startPoint = { 0 };							// startPoint의 좌표값을 0으로 초기화
			endPoint = { 0 };							// endPoint의 좌표값을 0으로 초기화
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// Cube 버튼이라면
		case 5:
		{
			Shape = S_Cube;								// 도형의 종류를 Cube로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// 해당사항이 없는 경우
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		break;
	}
	break;

	case WM_LBUTTONDOWN:
	{
		HandleLeftButtonDown(hwnd, wParam, lParam, startPoint, endPoint, isMouseLButtonPressed, Shape, drawing_area);
	}
	break;

	// 마우스 왼쪽 버튼을 뗀 경우
	case WM_LBUTTONUP:
	{
		// 체크 변수의 값을 FALSE으로 설정
		isMouseLButtonPressed = FALSE;
	}
	break;

	// 마우스 오른쪽 버튼이 눌린 경우
	case WM_RBUTTONDOWN:
	{
		HandleRightButtonDown(hwnd, wParam, lParam, drawing_area, Shape, isMouseRButtonPressed, startPointSaved, endPointSaved, endPoint, m_startPoint, Box, Circle);
	}
	break;

	// 마우스 오른쪽 버튼을 뗀 경우
	case WM_RBUTTONUP:
	{
		// 체크 변수의 값을 FALSE로 설정
		isMouseRButtonPressed = FALSE;
	}
	break;

	// 마우스가 움직이는 경우
	case WM_MOUSEMOVE:
	{
		HandleMouseMove(hwnd, wParam, lParam, drawing_area, Shape, isMouseLButtonPressed, isMouseRButtonPressed, startPoint, endPoint, Box, Circle, m_startPoint, m_endPoint, startPointSaved, endPointSaved, distance);
	}
	break;

	case WM_PAINT:
	{
		// 페인트 구조체 선언과 윈도우 핸들러 받아오기
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		DrawInterface(hwnd, hdc, drawing_area);

		// 도형의 종류가 Box라면
		if (Shape == S_Box) {
			DrawBox(hdc, Box);
		}

		// 도형의 종류가 Circle이라면
		if (Shape == S_Circle) {
			DrawCircle(hdc, Circle);
		}

		// 도형의 종류가 Bonobono라면
		if (Shape == S_Bonobono) {
			DrawBonobono(hwnd, hdc, isSpaceButtonPressed);
		}

		// 도형의 종류가 Ryan이라면
		if (Shape == S_Ryan) {
			DrawRyan(hwnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}

		EndPaint(hwnd, &ps);
	}
	break;

	// 버튼(윈도우)을 생성
	case WM_CREATE:
	{
		CreateButtons(hwnd, ((LPCREATESTRUCT)lParam)->hInstance);
	}
	break;

	// 마우스 포인터의 모양을 변경
	case WM_SETCURSOR:
	{
		UpdateCursor(hwnd, drawing_area);
		return TRUE; // 메시지가 처리되었음을 나타냅니다.
	}
	break;

	// 윈도우가 종료된경우
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	// 해당사항이 없는 경우
	default:
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	break;

	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202007034"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.

	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, NULL, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{
		}*/
	}

	// 종료 메시지 보내기
	return (int)msg.wParam;

}