#include "stdafx.h"
#include <list>
#include <vector>
#include "InstantCoroutine.h"

void sample3()
{
	new TinyCoroutine([](Coroutine* coroutine){
		for (int i = 0; i < 3; i++){
			printf("aa %d\n", i);
			coroutine->yield();
		}
	});
	new TinyCoroutine([](Coroutine* coroutine){
		for (int i = 0; i < 2; i++){
			printf("bb %d\n", i);
			coroutine->yield();
		}
	});

	// ブロックの外側の変数をいじるラムダ式.
	/*
	int n = 0;
	printf("n = %d\n", n);
	new TinyCoroutine([&n](Coroutine* coroutine){
		n++;
		coroutine->yield();
		n++;
		printf("n1 = %d\n", n);
		coroutine->yield();
		n++;
		printf("n2 = %d\n", n);
	});
	*/

	printf("manager start.\n");
	while (CoroutineManager::instance()->go()){
		printf("manager sleep\n");
	}
	printf("manager end.\n");

//	printf("nn = %d\n", n);
}
