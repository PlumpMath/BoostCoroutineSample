#include "stdafx.h"
#include <list>
#include <vector>
#include "InstantCoroutine.h"

class MyCoroutine : public Coroutine{
protected:
	~MyCoroutine(){
		printf("remove hello\n");
	}
	void run(){
		for (int i = 0; i < 3; i++){
			yield();
			printf("hello %d\n", i);
		}
	}
};

void sample2()
{
	printf("main1\n");
	new MyCoroutine();
	new MyCoroutine();
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
	printf("main2\n");
	while (CoroutineManager::instance()->go()){
		printf("main sleep\n");
	}
	printf("main3\n");
	printf("nn = %d\n", n);
}
