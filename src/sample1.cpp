#include "stdafx.h"
#include <boost/coroutine/coroutine.hpp>

void loop(boost::coroutines::coroutine<int()>::caller_type& yield)
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
	boost::coroutines::coroutine<int()> routine(loop);
	while (routine) {
		int n = routine.get();
		printf("n = %d\n", n);
		routine();
	}
	printf("sample1 end.\n");
}