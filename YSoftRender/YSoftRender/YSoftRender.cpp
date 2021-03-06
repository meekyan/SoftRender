// YSoftRender.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "Screen.h"
#include "tchar.h"
#include "Demo.h"

#ifndef UNICODE
#define UNICODE
#endif 

Screen* screen = NULL;
UINT32 First = 1;
Demo* MyDemo;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	screen = new Screen();
	int ret = screen->init(800, 600, _T("YSoftRender"));
	if (ret < 0) {
		printf("screen init failed(%d)!\n", ret);
		exit(ret);
	}
	
	/*UINT32* fb = (UINT32*)(screen->getFrameBuffer());
	UINT32** cb;
	cb = (UINT32**)malloc(800 * sizeof(UINT32));
	for (int i = 0; i < 800; i++)
	{
		cb[i] = fb + i * 800;
	}
	for(int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
		{
			cb[i][j] = 255 << 1;
		}
*/
	MyDemo = new Demo();
	if (First)
	{
		First = 0;
		UINT32* FrameBuffer = (UINT32*)(screen->getFrameBuffer());
		MyDemo->Init(FrameBuffer, hInstance, screen->wndHandle);
	}
	while (!screen->isExit()) {
		screen->dispatch();
		screen->dispatch();
		MyDemo->Update();
		MyDemo->SoftRender();
		screen->update();
		Sleep(1);
	}
	screen->close();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
