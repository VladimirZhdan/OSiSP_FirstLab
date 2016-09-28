// MiniPaint.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "MiniPaint.h"
#include <commdlg.h>
//own files
#include "DrawingShapes.h"
#include "FabricsBase.h"
#include "Factory.h"




#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����


DrawingShapes *drawingShapes;
FabricsBase* currentFabric;
HPEN currHPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINIPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIPAINT));	

	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIPAINT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MINIPAINT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   drawingShapes = new DrawingShapes(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	static CHOOSECOLOR ccs;
	static COLORREF acrCustClr[16];
	static HBRUSH hBrush;
	static POINT point;			
	static COLORREF stdColor = RGB(255,0,0);	



	switch (message)
	{
	case WM_CREATE:
		ccs.lStructSize = sizeof(CHOOSECOLOR);
		ccs.hwndOwner = hWnd;
		ccs.rgbResult = stdColor;
		ccs.Flags = CC_RGBINIT | CC_FULLOPEN;
		ccs.lpCustColors = (LPDWORD)acrCustClr;
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);		
		switch (wmId)
		{			
		case IDM_CHOOSECOLOR:
			if (ChooseColor(&ccs))
			{
				stdColor = ccs.rgbResult;
				if (hBrush) DeleteObject(hBrush);
				hBrush = CreateSolidBrush(stdColor);
				HPEN hPen;
				if (currHPen) DeleteObject(currHPen);
				currHPen = CreatePen(PS_SOLID, 5, stdColor);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		case IDM_LINE:
			currentFabric = Factory::GetCurrentFabric(1);
			drawingShapes->StartDrawing(currentFabric->Create(currHPen));
			break;
		case IDM_PENCIL:
			currentFabric = Factory::GetCurrentFabric(2);
			drawingShapes->StartDrawing(currentFabric->Create(currHPen));
			break;
		case IDM_RECTANGLE:
			currentFabric = Factory::GetCurrentFabric(3);
			drawingShapes->StartDrawing(currentFabric->Create(currHPen));
			break;
		case IDM_ELLIPSE:
			currentFabric = Factory::GetCurrentFabric(4);
			drawingShapes->StartDrawing(currentFabric->Create(currHPen));
			break;
		case IDM_POLYGONALLINE:
			currentFabric = Factory::GetCurrentFabric(5);
			drawingShapes->StartDrawing(currentFabric->Create(currHPen));
			break;
		case IDM_POLYGON:
			currentFabric = Factory::GetCurrentFabric(6);
			drawingShapes->StartDrawing(currentFabric->Create(currHPen));
			break;
		case IDM_TEXT:
			currentFabric = Factory::GetCurrentFabric(7);
			drawingShapes->StartDrawing(currentFabric->Create(currHPen));
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CHAR:
		if (!(drawingShapes->isEndDrawing()))
		{
			drawingShapes->AddInformation((TCHAR)wParam);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_MOUSEMOVE:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);	
		if (!(drawingShapes->isEndDrawing()))
			InvalidateRect(hWnd, NULL, TRUE);
		break;	
	case WM_LBUTTONDOWN:		
		drawingShapes->AddDot(point);			
		break;
	case WM_RBUTTONDOWN:
		drawingShapes->AddExtraDot();
		break;
	case WM_ERASEBKGND:
		return 1;
		break;
	case WM_PAINT:
		drawingShapes->Drawing(point);	
		break;
	case WM_DESTROY:
		PostQuitMessage(0);		
		//!!!		
		delete drawingShapes;
		//!!!		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
