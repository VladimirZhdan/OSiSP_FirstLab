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
//file for slider
#include <CommCtrl.h>
//files for drag-drop
#include <ShellAPI.h>
#include <string.h>
#include <stdio.h>


#define MAX_LOADSTRING 100
// for drag-drop
#define BUF_SIZE 500


enum CHOOSE_COLOR_MODE
{
	PEN_MODE,
	BRUSH_MODE,
};

// global variables
HINSTANCE hInst;								// current hInst
TCHAR szTitle[MAX_LOADSTRING];					// text of Title
TCHAR szWindowClass[MAX_LOADSTRING];			// name of main windows class
DrawingShapes *drawingShapes;
FabricsBase* currentFabric;
//variables for DrawObject
int currentDrawObjectIndex;
POINT prevPoint;
POINT point;
int thickness;
COLORREF colorPen;
COLORREF colorBrush;
//variables to work with Pen and Brush
CHOOSECOLOR ccs;
COLORREF acrCustClr[16];
COLORREF stdColor;
//variables to work with Files
TCHAR fileName[256] = _T("");
OPENFILENAME hFile;
HENHMETAFILE hEnhMetaFile;
bool isEndOFDefinitionOfPrintArea;

// methods signatures
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ChooseThickness(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// Own methods
void InitResources(HWND hWnd);
void InitChooseColorDialogStructure(HWND hWnd);
void InitOpenFileDialogStructure(HWND hWnd);
void MenuHandle(HWND hWnd, WORD wmId, WORD wmEvent);
void OpenFileHandle(HWND hWnd);
void OpenFile(HWND hWnd, TCHAR fileName[]);
void SaveFileHandle(HWND hWnd);
void PrintHandle();
void PrintAsEnhancedFile(HWND hWnd, OPENFILENAME hFile);
void ChooseColorHandle(HWND hWnd, CHOOSE_COLOR_MODE mode);
void MouseMoveHandle(HWND hWnd, WPARAM wParam, LPARAM lParam);
void LButtonDownHandle(HWND hWnd);
void CreateDrawObject(int index, int thickness, COLORREF colorPen, COLORREF colorBrush);
void MouseWheel(HWND hWnd, WPARAM wParam);
void FreeResources();



int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Initialization global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINIPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Initialize application
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIPAINT));	

	// cycle of handle messages
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
	//variables for drag-drop	
	HDROP hDropInfo = NULL;
	UINT buffsize = BUF_SIZE;	
	TCHAR bufferForFileName[BUF_SIZE];		

	switch (message)
	{
	case WM_CREATE:		
		DragAcceptFiles(hWnd, TRUE);
		InitResources(hWnd);
		break;
	case WM_DROPFILES:
		hDropInfo = (HDROP)wParam;
		DragQueryFile(hDropInfo, 0, bufferForFileName, buffsize);
		TCHAR *expansion;
		expansion = _tcsstr(bufferForFileName, _T(".met"));
		if (expansion != NULL)
		{
			OpenFile(hWnd, bufferForFileName);
		}
		else
		{
			MessageBox(hWnd, _T("Несовместимый тип файла."), _T("Error"), MB_OK);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);		
		MenuHandle(hWnd, wmId, wmEvent);
		break;
	case WM_CHAR:
		if (!(drawingShapes->isEndDrawing()))
		{
			drawingShapes->AddInformation((TCHAR)wParam);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_MOUSEMOVE:
		MouseMoveHandle(hWnd, wParam, lParam);
		break;	
	case WM_LBUTTONDOWN:		
		LButtonDownHandle(hWnd);
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
		FreeResources();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void InitResources(HWND hWnd)
{	
	DrawingShapes::InitInstance(hWnd);
	drawingShapes = DrawingShapes::getInstance();
	stdColor = RGB(0, 0, 0);
	InitChooseColorDialogStructure(hWnd);
	InitOpenFileDialogStructure(hWnd);
	isEndOFDefinitionOfPrintArea = true;	
	currentDrawObjectIndex = 1;
	thickness = 1;
	colorPen = 0;
	colorBrush = 0;	
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

void MenuHandle(HWND hWnd, WORD wmId, WORD wmEvent)
{
	switch (wmId)
	{
	case IDM_OpenEnhancedFile:
		OpenFileHandle(hWnd);
		break;
	case IDM_SaveAsEnhancedFile:
		SaveFileHandle(hWnd);
		break;
	case IDM_PRINT:
		PrintHandle();
		break;
	case IDM_CHOOSECOLORPEN:
		ChooseColorHandle(hWnd, PEN_MODE);
		break;
	case IDM_CHOOSECOLORBRUSH:
		ChooseColorHandle(hWnd, BRUSH_MODE);
		break;
	case IDM_CHOOSETHICKNESS:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSETHICKNESS), hWnd, ChooseThickness);		
		break;
	case IDM_LINE:
		currentDrawObjectIndex = 1;
		break;
	case IDM_PENCIL:
		currentDrawObjectIndex = 2;
		break;
	case IDM_RECTANGLE:
		currentDrawObjectIndex = 3;
		break;
	case IDM_ELLIPSE:
		currentDrawObjectIndex = 4;
		break;
	case IDM_POLYGONALLINE:
		currentDrawObjectIndex = 5;
		break;
	case IDM_POLYGON:
		currentDrawObjectIndex = 6;
		break;
	case IDM_TEXT:
		currentDrawObjectIndex = 7;
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	default:
		break;
	}
}

void OpenFileHandle(HWND hWnd)
{
	hFile.lpstrTitle = _T("Открытие файла");
	hFile.Flags = OFN_HIDEREADONLY;
	if (!GetOpenFileName(&hFile)) return;
	OpenFile(hWnd, hFile.lpstrFile);	
	InvalidateRect(hWnd, NULL, TRUE);
}

void OpenFile(HWND hWnd, TCHAR fileName[])
{
	if (!(FileLogic::OpenEnhancedFile(&hEnhMetaFile, fileName)))
	{
		MessageBox(hWnd, _T("Ошибка открытия файла"), _T("Error"), MB_OK);
	}
	else
	{
		drawingShapes->ClearShapes();
		drawingShapes->setMetaFile(hEnhMetaFile);
	}
}

void SaveFileHandle(HWND hWnd)
{
	hFile.lpstrTitle = _T("Сохранение в файл");
	hFile.Flags = OFN_NOTESTFILECREATE | OFN_OVERWRITEPROMPT;
	if (!GetSaveFileName(&hFile)) return;
	if (FileLogic::SaveAsEnhancedFile(hWnd, hFile.lpstrFile))
	{
		MessageBox(hWnd, _T("Файл успешно сохранен"), _T("Success"), MB_OK);
	}
	else
	{
		MessageBox(hWnd, _T("Ошибка сохранения файла"), _T("Error"), MB_OK);
	}
}

void PrintHandle()
{		
	CreateDrawObject(3, 0, 0, 0);
	isEndOFDefinitionOfPrintArea = false;
}

void ChooseColorHandle(HWND hWnd, CHOOSE_COLOR_MODE mode)
{
	switch (mode)
	{
	case PEN_MODE:
		if (ChooseColor(&ccs))
		{
			colorPen = ccs.rgbResult;	
			CreateDrawObject(currentDrawObjectIndex, thickness, colorPen, colorBrush);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case BRUSH_MODE:
		if (ChooseColor(&ccs))
		{
			colorBrush = ccs.rgbResult;
			CreateDrawObject(currentDrawObjectIndex, thickness, colorPen, colorBrush);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}
}


void MouseMoveHandle(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	prevPoint = point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);

	if (!(drawingShapes->isEndDrawing()))
	{
		InvalidateRect(hWnd, NULL, TRUE);
	}
	else
	{
		if (MK_MBUTTON == wParam || ((MK_MBUTTON | MK_SHIFT) == wParam))
		{									
			drawingShapes->ChangeCoordinatesOfDrawObjects(point.x - prevPoint.x, point.y - prevPoint.y);
			InvalidateRect(hWnd, NULL, TRUE);		
		}
	}
}

void LButtonDownHandle(HWND hWnd)
{
	if (drawingShapes->isEndDrawing())
	{
		CreateDrawObject(currentDrawObjectIndex, thickness, colorPen, colorBrush);
	}

	drawingShapes->AddDot(point);
	if ((!isEndOFDefinitionOfPrintArea) && (drawingShapes->isEndDrawing()))
	{
		isEndOFDefinitionOfPrintArea = true;
		PrintAsEnhancedFile(hWnd, hFile);
		InvalidateRect(hWnd, NULL, TRUE);
	}
}



void CreateDrawObject(int index, int thickness, COLORREF colorPen, COLORREF colorBrush)
{
	currentFabric = Factory::GetCurrentFabric(index);
	drawingShapes->StartDrawing(currentFabric->Create(thickness, colorPen, colorBrush));
}

void PrintAsEnhancedFile(HWND hWnd, OPENFILENAME hFile)
{
	hFile.lpstrTitle = _T("Сохранение в файл");
	hFile.Flags = OFN_NOTESTFILECREATE | OFN_OVERWRITEPROMPT;
	if (GetSaveFileName(&hFile)) {
		if (FileLogic::PrintAsEnhancedFile(hWnd, hFile.lpstrFile))
		{
			MessageBox(hWnd, _T("Файл успешно сохранен"), _T("Success"), MB_OK);
		}
		else
		{
			MessageBox(hWnd, _T("Ошибка сохранения файла"), _T("Error"), MB_OK);
		}
	}
	else
	{
		drawingShapes->DeleteLastShape();
	}
	
}



void MouseWheel(HWND hWnd, WPARAM wParam)
{
	WORD wParamLoWord = LOWORD(wParam);
	if ((wParamLoWord == MK_CONTROL) || (wParamLoWord == (MK_CONTROL | MK_SHIFT)))
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

void FreeResources()
{
	delete drawingShapes;
}

// handler for About Dialog
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

INT_PTR CALLBACK ChooseThickness(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{		
	static HWND hTrack;
	static int trackValue;
	int wmId, wmEvent;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		trackValue = ::thickness;
		hTrack = GetDlgItem(hDlg, IDC_SLIDER);
		SetDlgItemInt(hDlg, IDC_SLIDERVALUE, trackValue, 0);
		SendMessage(hTrack, TBM_SETRANGEMIN, 0, 1);
		SendMessage(hTrack, TBM_SETRANGEMAX, 0, 100);
		SendMessage(hTrack, TBM_SETPOS, TRUE, trackValue);		
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			::thickness = trackValue;
			CreateDrawObject(currentDrawObjectIndex, thickness, colorPen, colorBrush);
			EndDialog(hDlg, wmId);
			return (INT_PTR)TRUE;
			break;
		case IDCANCEL:
			EndDialog(hDlg, wmId);
			return (INT_PTR)TRUE;
			break;
		}
		return (INT_PTR)TRUE;
		break;
	case WM_HSCROLL:
		trackValue = LOWORD(SendMessage(hTrack, TBM_GETPOS, 0, 0));
		SetDlgItemInt(hDlg, IDC_SLIDERVALUE, trackValue, 0);
		InvalidateRect(hDlg, NULL, TRUE);
		break;
	}
	return (INT_PTR)FALSE;
}

