// Paint_Plus_1.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include "Paint_Plus_1.h"
#include "RibbonFramework.h"
#include "CommandHandler.h"
#include "RibbonIDs.h"
#include <gdiplus.h>
#include <iostream>
#include <Objbase.h>
#include <windowsx.h>
#include <Commctrl.h>
#include <windows.h>
#include <Commdlg.h>
#include "Headerdll.h"

//using namespace std;
using namespace Gdiplus;
using namespace libdll;	

#pragma comment(lib, "Ole32.lib")
#pragma comment (lib,"Gdiplus.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define  LINE 0
#define  RECTANGLE 1
#define  ELLIPSE 2
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;		// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

void Paint(HDC, POINT*);
void ButtonMove(LPARAM lParam);
void Move(LPARAM lParam, WPARAM wParam, POINT ListPoint[10000]);
// Forward declarations of functions included in this code module:
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

	// TODO: Place code here.
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
		return FALSE;
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINT_PLUS_1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT_PLUS_1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CoUninitialize();
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;// CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT_PLUS_1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_PAINT_PLUS_1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
GdiplusStartupInput gdiPlusStartupInput;
ULONG_PTR gdiPlusToken;

POINT ListPoint[20000];
COLORREF color = RGB(0, 0, 0);
int LoaiHinh[10000] = { -1 };
int stt = 0;
bool click = false;
int i = 0;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	bool initSuccess;

	switch (message)
	{
	case WM_CREATE:
		//Init the Ribbon framework;
		initSuccess = InitializeFramework(hWnd);
		if (!initSuccess)
			return -1;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
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
	case WM_LBUTTONDOWN:
	{

						   POINT start;
						   start.x = GET_X_LPARAM(lParam);
						   start.y = GET_Y_LPARAM(lParam);
						   ListPoint[i] = start;
						   i++;
						   click = true;
						   LoaiHinh[stt] = shape;
						   break;
	}
	case WM_MOUSEMOVE:
	{
						 if (click == true){//why aaaa
							 libdll::myclass a;
							 a.Move(lParam, wParam, ListPoint, i); 
							 InvalidateRect(hWnd, NULL, TRUE);
						 }

						 break;
	}
	case WM_LBUTTONUP:
	{
						 i++;
						 stt++;
						 click = false;;
						 break;
	}
	case WM_PAINT:
	{
					 InitCommonControls();
					 GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, NULL);

					 PAINTSTRUCT ps;
					 HDC hdc, hdc_temp;
					 HPEN hpen;
					 HBITMAP bitmap = NULL;


					 hdc = BeginPaint(hWnd, &ps);
					 libdll::myclass a;
					 a.Paint(hdc, ListPoint,LoaiHinh,i);

					 EndPaint(hWnd, &ps);
					 break;
	}
	case WM_DESTROY:
		DestroyFramework();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

void Paint(HDC hdc, POINT  ListPoint[10000])
{
	Graphics* graphics = new Graphics(hdc);
	int lineWith = 3;
	Pen* pen = new Pen(Color(255, 0, 0, 0), lineWith);
	int j = 0;
	int k = 0;

	for (j, k; j < i; j += 2, k++){
		if (LoaiHinh[k] == LINE){
			graphics->DrawLine(pen, ListPoint[j].x, ListPoint[j].y, ListPoint[j + 1].x, ListPoint[j + 1].y);
		}
		else if (LoaiHinh[k] == RECTANGLE)
			graphics->DrawRectangle(pen, ListPoint[j].x, ListPoint[j].y, ListPoint[j + 1].x - ListPoint[j].x, ListPoint[j + 1].y - ListPoint[j].y);
		else if (LoaiHinh[k] == ELLIPSE)
			graphics->DrawEllipse(pen, ListPoint[j].x, ListPoint[j].y, ListPoint[j + 1].x - ListPoint[j].x, ListPoint[j + 1].y - ListPoint[j].y);
	}

	delete pen;
	delete graphics;
}



