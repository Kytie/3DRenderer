// 3DRenderer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "3DRenderer.h"
#include "Vector3D.h"
#include "Matrix4.h"
#include "Polygon.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;




#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
Vector3D originalVecs[1599];
int vecIndexPoints[3192][3];

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				ImportModel();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY3DRENDERER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DRENDERER));

	// Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DRENDERER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY3DRENDERER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static RECT client;
	static int clientWidth;
	static int	clientHeight;
	static float degreeX = 0.0;
	static float degreeY = 0.0;
	static bool colour = false;

	switch (message)
	{

	case WM_CREATE:
		ImportModel();
		SetTimer(hWnd, 123, 700, NULL);
		break;

	case WM_TIMER:
		SetTimer(hWnd, 123, 700, NULL);
		degreeX = degreeX + 0.10;
		degreeY = degreeY + 0.10;
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		SetTimer(hWnd, 123, 4000, NULL);
		break;
	case WM_LBUTTONDOWN:
		SetTimer(hWnd, 123, 4000, NULL);
		break;
	case WM_RBUTTONDOWN:
		SetTimer(hWnd, 123, 4000, NULL);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_WIREFRAME:
			colour = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case IDM_CWIREFRAME:
			colour = true;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		{
			if (GetClientRect(hWnd, &client))
		{
			clientWidth = client.right - client.left;
			clientHeight = client.bottom - client.top;
		}
		hdc = BeginPaint(hWnd, &ps);
		HDC backbuffDC = CreateCompatibleDC(hdc);
		HBITMAP backbuffer = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
		SelectObject(backbuffDC, backbuffer);
		HGDIOBJ brush = SelectObject(backbuffDC, GetStockObject(DC_BRUSH));
		Rectangle(backbuffDC, client.left, client.top, client.right, client.bottom);
		
		Vector3D vector[1599];
		for(int i = 0; i<1599; i++)
		{
			vector[i] = originalVecs[i];
		}
		

		Polygons draw;
		//Model To World
		Vector3D transVector(150,80,-5);
		Vector3D scaleVec(3,3,3);
		Matrix4 translation;
		Matrix4 rotationY;
		Matrix4 rotationX;
		Matrix4 rotation;
		Matrix4 scale;

		Matrix4 modelToWorld;
		scale.SetScaleMatrix(scaleVec);
		rotationY.SetRotationMatrixY(degreeY);
		rotationX.SetRotationMatrixX(degreeX);
		translation.SetTranslationMatrix(transVector);
		rotation = rotationX*rotationY;
		modelToWorld = translation*rotation*scale;


		for(int i = 1; i<1599; i++)
		{
			vector[i] = modelToWorld * vector[i];
		}


		//World To View
		//view matrix
		Vector3D eye(0.0,0.0,0.0);
		Vector3D at(0.0,0.0,-1.0);
		Vector3D up(0.0,1.0,0.0);
		Vector3D v = at - eye;
		v = v.Normalise(v);
		Vector3D r = v.GetCrossProduct(up);
		r = r.Normalise(r);
		Vector3D u = r.GetCrossProduct(v);
		u = u.Normalise(u);

		Matrix4 viewMatrix;
		Matrix4 worldToView;
		Matrix4 identity;
		viewMatrix.CreateViewMatrix(v, u, r, eye);
		identity.SetIdentityMatrix();
		worldToView = worldToView.invert(viewMatrix, identity);

		for(int i = 1; i<1599; i++)
		{
			vector[i] = worldToView * vector[i];
		}

		//View To Viewport
		//Projection Matrix
		float pMatrix[4][4] = {{5.0,0.0,0.0,0.0},{0.0,5.0,0.0,0.0},{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,1.0}};
		Matrix4 projectionmatrix(*pMatrix);

		for(int i = 1; i<1599; i++)
		{
			vector[i] = projectionmatrix * vector[i];
		}


		Polygons polygon[3192];

		for(int i=0; i<3192; i++)
		{
			int x = 0;
			int y = 0;
			int z = 0;
			for(int j = 0; j<1; j++)
			{
				x = vecIndexPoints[i][j];
			}
			for(int k = 1; k<2; k++)
			{
				y = vecIndexPoints[i][k];
			}
			for(int m = 2; m<3; m++)
			{
				z = vecIndexPoints[i][m];
			}
			polygon[i].SetPolygon(vector[x], 0);
			polygon[i].SetPolygon(vector[y], 1);
			polygon[i].SetPolygon(vector[z], 2);
		}
		
		
		for(int i = 0; i<3192; i++)
		{
			draw.DrawPolygon(polygon[i], 3, backbuffDC);

			if(colour)
			{
				Vector3D vec1 = polygon[i].GetPolygon(0);
				Vector3D vec2 = polygon[i].GetPolygon(1);
				Vector3D vec3 = polygon[i].GetPolygon(2);
			
				int  xMin = vec1.GetX();
				int  xMax = vec1.GetX();
				int  yMin = vec1.GetY();
				int  yMax = vec1.GetY();

				if(vec2.GetX() < xMin)
				{
					xMin = vec2.GetX();
				}
				if(vec3.GetX() < xMin)
				{
					xMin = vec3.GetX();
				}
				if(vec2.GetX() > xMax)
				{
					xMax = vec2.GetX();
				}
				if(vec3.GetX() > xMax)
				{
				xMax = vec3.GetX();
				}

				if(vec2.GetY() < yMin)
				{
					yMin = vec2.GetY();
				}
				if(vec3.GetY() < yMin)
				{
					yMin = vec3.GetY();
				}
				if(vec2.GetY() > yMax)
				{
					yMax = vec2.GetY();
				}
				if(vec3.GetY() > yMax)
				{
					yMax = vec3.GetY();
				}

				int y = yMin;
				bool odd = false;

				while(y<=yMax)
				{
					int x = xMin;
					while(x <= xMax)
					{
						if(GetPixel(backbuffDC, x, y) == RGB(0,0,0))
						{
							int x1 = vec1.GetX();
							int x2 = vec2.GetX();
							int x3 = vec3.GetX();
							int y1 = vec1.GetY();
							int y2 = vec2.GetY();
							int y3 = vec3.GetY();


							if(odd)
							{
								odd = false;
							}
							else
							{
								odd = true;
							}

							if(x == x1 && y == y1 || x == x2 && y == y2 || x == x3 && y == y3)
							{
								odd = false;
							}
						}
						if(odd)
						{

							if(GetPixel(backbuffDC, x, y) == RGB(0,0,0))
							{
							}
							else
							{
								SetPixel(backbuffDC, x, y, RGB(50,100,50));
							}
						}
						x = x+1;
					}
					y = y + 1;
				}
			}
		}





		BitBlt(hdc, client.left, client.top, clientWidth, clientHeight, backbuffDC, client.left, client.top, SRCCOPY);
		DeleteObject(brush);
		DeleteObject(backbuffer);
		DeleteObject(backbuffDC);
		EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
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

void ImportModel()
{
	char buffer[256];
	int i = 1;
	int j = 0;
	ifstream objFile("teddy.obj", ifstream::in);
	if(objFile.is_open())
	{
		while(! objFile.eof())
		{
			objFile.getline(buffer,256);
			istringstream iss(buffer, istringstream::in);
			char op; float x, y, z;
			iss>>op>>x>>y>>z;
			if(op == 'v')
			{
				originalVecs[i].SetX(x);
				originalVecs[i].SetY(y);
				originalVecs[i].SetZ(z);
				i++;
			}
			if(op == 'f')
			{
				int k = 0;
				vecIndexPoints[j][k] = x;
				vecIndexPoints[j][++k] = y;
				vecIndexPoints[j][++k] = z;
				j++;
			}
		}
		void close();
	}
}

