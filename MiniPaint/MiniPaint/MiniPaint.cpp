// MiniPaint.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "MiniPaint.h"
#include <commdlg.h>
//own files
#include "DrawingShapes.h"
#include "FabricsBase.h"
#include "Factory.h"
#include "FileLogic.h"



#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна


DrawingShapes *drawingShapes;
FabricsBase* currentFabric;
HPEN currHPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

// Отправить объявления функций, включенных в этот модуль кода:
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

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINIPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIPAINT));	

	// Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
   //WS_OVERLAPPEDWINDOW
   hWnd = CreateWindow(szWindowClass, szTitle, 
	   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
	   CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, HWND_DESKTOP, NULL, hInstance, NULL);
   

   DrawingShapes::InitInstance(hWnd);
   drawingShapes = DrawingShapes::getInstance();

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
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
	static COLORREF stdColor = RGB(0,0,0);	

	//variables to work with Files
	static TCHAR fileName[256] = _T("");
	static OPENFILENAME hFile;
	static HENHMETAFILE hEnhMetaFile;



	switch (message)
	{
	case WM_CREATE:
		//init ChooseColorDialog
		ccs.lStructSize = sizeof(CHOOSECOLOR);
		ccs.hwndOwner = hWnd;
		ccs.rgbResult = stdColor;
		ccs.Flags = CC_RGBINIT | CC_FULLOPEN;
		ccs.lpCustColors = (LPDWORD)acrCustClr;
		//init OpenFileDialog
		hFile.lStructSize = sizeof(OPENFILENAME);
		hFile.hwndOwner = hWnd;
		hFile.hInstance = hInst;
		hFile.lpstrFilter = _T("MetaFile\0*.met");
		hFile.lpstrFile = fileName;
		hFile.nMaxFile= 256;
		hFile.lpstrInitialDir = _T(".\\");
		hFile.lpstrDefExt = _T("met");
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);		
		switch (wmId)
		{		
		case IDM_OpenEnhancedFile:
			hFile.lpstrTitle = _T("Открытие файла");
			hFile.Flags = OFN_HIDEREADONLY;
			if (!GetOpenFileName(&hFile)) return 1;
			///
			/// Work with fileName
			///
			if (!(FileLogic::OpenEnhancedFile(&hEnhMetaFile, hFile.lpstrFile)))
			{
				MessageBox(hWnd, _T("Ошибка открытия файла"), _T("Error"), MB_OK);
			}
			else
			{
				drawingShapes->setMetaFile(hEnhMetaFile);
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_SaveAsEnhancedFile:
			hFile.lpstrTitle = _T("Сохранение в файл");
			hFile.Flags = OFN_NOTESTFILECREATE | OFN_OVERWRITEPROMPT;
			if (!GetSaveFileName(&hFile)) return 1;
			///
			/// Work with fileName
			///
			if (FileLogic::SaveAsEnhancedFile(hWnd, hFile.lpstrFile))
			{
				MessageBox(hWnd, _T("Файл успешно сохранен"), _T("Success"), MB_OK);
			}				
			else
			{
				MessageBox(hWnd, _T("Ошибка сохранения файла"), _T("Error"), MB_OK);
			}				
			break;
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

// Обработчик сообщений для окна "О программе".
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
