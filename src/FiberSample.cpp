// FiberSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <boost/coroutine/coroutine.hpp>
using namespace boost::coroutines;

void loop(coroutine<int()>::caller_type& yield)
{
	for (int i = 0; i < 10; ++i) {
		yield(i);
	}
}

void loop2(coroutine<int()>::caller_type& yield)
{
	for (int i = 0; i < 10; ++i) {
		yield(i * 100);
	}
}

template<typename P>
void enumerate(P predicate)
{
	coroutine<int()> routine(loop);
	coroutine<int()> routine2(loop2);

	while (routine || routine2) {
		if (routine){
			int i = routine.get();
			predicate(i);
			routine();
		}
		if (routine2){
			int i = routine2.get();
			predicate(i);
			routine2();
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	enumerate([](int i){ std::cout << i << " "; });
	std::cout << std::endl;

	return 0;
}
