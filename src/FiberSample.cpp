// FiberSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <list>
#include <vector>
#include <boost/coroutine/coroutine.hpp>
using namespace boost::coroutines;
/*
class Coroutine{
private:
	static void s_loop(coroutine<int()>::caller_type& yield){
		
	}
public:
	Coroutine();
	virtual void run() = 0;
	void doContinue(){
		if (m_coroutine){
			m_coroutine();
		}
	}
protected:
	void wait(){
		return;
	}
private:
	coroutine<int()> m_coroutine;
};

class CoroutineManager{
public:
	static CoroutineManager* instance(){
		static CoroutineManager theInstance;
		return &theInstance;
	}
public:
	void add(Coroutine* coroutine){
		m_coroutines.push_back(coroutine);
	}
	void go(){
		for (Coroutine* coroutine : m_coroutines){
			coroutine->doContinue();
		}
	}
private:
	std::list<Coroutine*> m_coroutines;
};

Coroutine::Coroutine()
: m_coroutine(s_loop)
{
	CoroutineManager::instance()->add(this);
}
*/
void loop(coroutine<int()>::caller_type& yield, int param)
{
	printf("param = %d\n", param);
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
	using std::placeholders::_1;
	coroutine<int()> routine( std::bind(loop, _1, 2000) );
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
