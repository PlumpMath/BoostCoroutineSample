#include "stdafx.h"
#include <boost/coroutine/coroutine.hpp>
using namespace boost::coroutines;

void loop(coroutine<int()>::caller_type& yield)
{
	printf("loop start.\n");
	for (int i = 0; i < 5; ++i) {
		yield(i);
	}
	printf("loop end.\n");
}

void sample1()
{
	printf("sample1 start.\n");
	coroutine<int()> routine(loop);
	while (routine) {
		int i = routine.get();
		printf("i = %d\n", i);
		routine();
	}
	printf("sample1 end.\n");
}