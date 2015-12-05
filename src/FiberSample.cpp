// FiberSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <boost/coroutine/coroutine.hpp>

LPVOID g_lpMainFiber;
LPVOID g_lpSubFiber;

void WINAPI SubFiberRoutine(LPVOID lpFiberParameter)
{
	printf("fiber1\n");
	SwitchToFiber(g_lpMainFiber);
	printf("fiber2\n");
	SwitchToFiber(g_lpMainFiber);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ConvertThreadToFiber(NULL);

	g_lpMainFiber = ::GetCurrentFiber();

	printf("main1\n");
	g_lpSubFiber = ::CreateFiber(0, SubFiberRoutine, NULL);
	printf("main2\n");
	SwitchToFiber(g_lpSubFiber);
	printf("main3\n");
	SwitchToFiber(g_lpSubFiber);
	printf("main4\n");
	SwitchToFiber(g_lpSubFiber);
	printf("main5\n");


	return 0;
}
