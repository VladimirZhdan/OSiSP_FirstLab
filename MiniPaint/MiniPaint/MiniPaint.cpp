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

// global variables
HINSTANCE hInst;								// current hInst
TCHAR szTitle[MAX_LOADSTRING];					// text of Title
TCHAR szWindowClass[MAX_LOADSTRING];			// name of main windows class
DrawingShapes *drawingShapes;
FabricsBase* currentFabric;
HPEN currHPen;
HBRUSH currHBrush;
//variables for Pan
static POINT prevPoint;
static POINT point;
//variables to work with Pen and Brush
static CHOOSECOLOR ccs;
static COLORREF acrCustClr[16];
static COLORREF stdColor;
//variables to work with Files
static TCHAR fileName[256] = _T("");
static OPENFILENAME hFile;
static HENHMETAFILE hEnhMetaFile;
static bool isEndOFDefinitionOfPrintArea;




// methods signatures
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// Own methods
void InitResources(HWND hWnd);
void InitChooseColorDialogStructure(HWND hWnd);
void InitOpenFileDialogStructure(HWND hWnd);

void CreateDrawObject(int index, HPEN currHPen, HBRUSH hBrush);
void PrintAsEnhancedFile(HWND hWnd, OPENFILENAME hFile);
void MouseWheel(HWND hWnd, WPARAM wParam);

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


	

	switch (message)
	{
	case WM_CREATE:
		InitResources(hWnd);
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
			if (FileLogic::SaveAsEnhancedFile(hWnd, hFile.lpstrFile))
			{
				MessageBox(hWnd, _T("Файл успешно сохранен"), _T("Success"), MB_OK);
			}				
			else
			{
				MessageBox(hWnd, _T("Ошибка сохранения файла"), _T("Error"), MB_OK);
			}				
			break;
		case IDM_PRINT:
			CreateDrawObject(3, (HPEN)GetStockObject(BLACK_PEN), (HBRUSH)GetStockObject(HOLLOW_BRUSH));
			isEndOFDefinitionOfPrintArea = false;			
			break;
		case IDM_CHOOSECOLOR:
			if (ChooseColor(&ccs))
			{
				stdColor = ccs.rgbResult;
				if (currHBrush) DeleteObject(currHBrush);
				currHBrush = CreateSolidBrush(stdColor);
				HPEN hPen;
				if (currHPen) DeleteObject(currHPen);
				currHPen = CreatePen(PS_SOLID, 1, stdColor);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		case IDM_LINE:
			CreateDrawObject(1, currHPen, currHBrush);
			break;
		case IDM_PENCIL:
			CreateDrawObject(2, currHPen, currHBrush);
			break;
		case IDM_RECTANGLE:
			CreateDrawObject(3, currHPen, currHBrush);
			break;
		case IDM_ELLIPSE:
			CreateDrawObject(4, currHPen, currHBrush);
			break;
		case IDM_POLYGONALLINE:
			CreateDrawObject(5, currHPen, currHBrush);
			break;
		case IDM_POLYGON:
			CreateDrawObject(6, currHPen, currHBrush);
			break;
		case IDM_TEXT:
			CreateDrawObject(7, currHPen, currHBrush);
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
		prevPoint = point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);	
		
		if (!(drawingShapes->isEndDrawing()))
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else
		{
			if (MK_LBUTTON == wParam)
			{
				drawingShapes->ChangeCoordinatesOfDrawObjects(point.x - prevPoint.x, point.y - prevPoint.y);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
			
		break;	
	case WM_LBUTTONDOWN:		
		drawingShapes->AddDot(point);	
		if ((!isEndOFDefinitionOfPrintArea) && (drawingShapes->isEndDrawing()))
		{
			isEndOFDefinitionOfPrintArea = true;
			PrintAsEnhancedFile(hWnd, hFile);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_RBUTTONDOWN:
		drawingShapes->AddExtraDot();		
		break;
	case WM_MOUSEWHEEL:
		MouseWheel(hWnd, wParam);
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

void InitResources(HWND hWnd)
{
	stdColor = RGB(0, 0, 0);
	InitChooseColorDialogStructure(hWnd);
	InitOpenFileDialogStructure(hWnd);
	currHPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	currHBrush = CreateSolidBrush(RGB(0, 0, 0));
	isEndOFDefinitionOfPrintArea = true;
	

}

void InitChooseColorDialogStructure(HWND hWnd)
{
	ccs.lStructSize = sizeof(CHOOSECOLOR);
	ccs.hwndOwner = hWnd;
	ccs.rgbResult = stdColor;
	ccs.Flags = CC_RGBINIT | CC_FULLOPEN;
	ccs.lpCustColors = (LPDWORD)acrCustClr;
}

void InitOpenFileDialogStructure(HWND hWnd)
{
	hFile.lStructSize = sizeof(OPENFILENAME);
	hFile.hwndOwner = hWnd;
	hFile.hInstance = hInst;
	hFile.lpstrFilter = _T("MetaFile\0*.met");
	hFile.lpstrFile = fileName;
	hFile.nMaxFile = 256;
	hFile.lpstrInitialDir = _T(".\\");
	hFile.lpstrDefExt = _T("met");
}



void CreateDrawObject(int index, HPEN currHPen, HBRUSH hBrush)
{
	currentFabric = Factory::GetCurrentFabric(index);
	drawingShapes->StartDrawing(currentFabric->Create(currHPen, hBrush));
}

void PrintAsEnhancedFile(HWND hWnd, OPENFILENAME hFile)
{
	hFile.lpstrTitle = _T("Сохранение в файл");
	hFile.Flags = OFN_NOTESTFILECREATE | OFN_OVERWRITEPROMPT;
	if (!GetSaveFileName(&hFile)) return;
	if (FileLogic::PrintAsEnhancedFile(hWnd, hFile.lpstrFile))
	{
		MessageBox(hWnd, _T("Файл успешно сохранен"), _T("Success"), MB_OK);
	}
	else
	{
		MessageBox(hWnd, _T("Ошибка сохранения файла"), _T("Error"), MB_OK);
	}
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

void MouseWheel(HWND hWnd, WPARAM wParam)
{
	WORD wParamLowWord = LOWORD(wParam);
	if ((wParamLowWord == MK_CONTROL) || (wParamLowWord == (MK_CONTROL | MK_SHIFT)))
	{
		WORD wheelDestiny = HIWORD(wParam);
		if (wheelDestiny > 65000)
		{
			drawingShapes->Zooming(0.5);			
		}
		else
		{
			drawingShapes->Zooming(2);
		}
		InvalidateRect(hWnd, NULL, true);
	}
}
