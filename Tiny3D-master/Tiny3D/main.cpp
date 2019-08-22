#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <string>
#include <iostream>
#include "BoxDemo.h"
#include "Math/ZCMath.h"
#pragma comment(lib, "winmm.lib")
using namespace std; 


HINSTANCE				g_hInstance;				//ʵ�����
static HWND				g_hWnd;					//���ھ��
string					g_title = "TinyD3D";		//���ڱ���
int						g_width = 800;			//���ڴ�С
int						g_height = 600;

shared_ptr<BoxDemo> g_pBoxDemo = make_shared<BoxDemo>();

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEX wcex;
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(wcex);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wcex.hIconSm = wcex.hIcon;
	wcex.hInstance = g_hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = (LPCWSTR)g_title.c_str();
	wcex.lpszMenuName = nullptr;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcex))
		return 0;

	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	HWND g_hWnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCWSTR)g_title.c_str(), (LPCWSTR)g_title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, g_hInstance, nullptr);

	if (!g_hWnd)
	{
		MessageBox(nullptr, (LPCWSTR)"create window failed!", (LPCWSTR)"error", MB_OK);
		return 0;
	}

	ShowWindow(g_hWnd, nShowCmd);
	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
 		else
 		{
 			g_pBoxDemo->Update(0.f);
 			g_pBoxDemo->Render();
 			InvalidateRect(g_hWnd, nullptr, true);
 			UpdateWindow(g_hWnd);
 		}
	}
	return static_cast<int>(msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	//˫�����ͼ
	static BITMAPINFO s_bitmapInfo;
	static HDC s_hdcBackbuffer;			//�󻺳��豸���	
	static HBITMAP s_hBitmap;
	static HBITMAP s_hOldBitmap;
	static void* s_pData;

	switch (message)
	{
	case WM_CREATE:
	{	
		g_pBoxDemo->Init(g_hInstance, hWnd);
		//��ʼ���豸�޹�λͼheader
		BITMAPINFOHEADER bmphdr = { 0 };
		bmphdr.biSize = sizeof(BITMAPINFOHEADER);
		bmphdr.biWidth = g_width;
		bmphdr.biHeight = -g_height;
		bmphdr.biPlanes = 1;
		bmphdr.biBitCount = 32;
		bmphdr.biSizeImage = g_height * g_width * 4;
		//�����󻺳���
		//�ȴ���һ���ڴ�dc
		s_hdcBackbuffer = CreateCompatibleDC(nullptr);
		//���ǰ�û�����dc
		HDC hdc = GetDC(hWnd);
		if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
			reinterpret_cast<void**>(&g_pBoxDemo->GetDevice()->GetFrameBuffer()), nullptr, 0)))
		{
			MessageBox(nullptr, (LPCWSTR)"create dib section failed!", (LPCWSTR)"error", MB_OK);
			return 0;
		}
		//��bitmapװ���ڴ�dc
		s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
		//�ͷ�dc
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		//��backbuffer���ݴ���frontbuffer
		BitBlt(ps.hdc, 0, 0, g_width, g_height, s_hdcBackbuffer, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY:
		SelectObject(s_hdcBackbuffer, s_hOldBitmap);
		DeleteDC(s_hdcBackbuffer);
		DeleteObject(s_hOldBitmap);
		PostQuitMessage(0);
		break;
		
	//��ֹ�������� ��ֹ��˸
	case WM_ERASEBKGND:
		return true;
		break;
	//����¼�
	//��걻����ʱ
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		g_pBoxDemo->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

		//����ͷ�ʱ
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		g_pBoxDemo->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));		
		return 0;

		//����ƶ�ʱ
	case WM_MOUSEMOVE:
		g_pBoxDemo->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}