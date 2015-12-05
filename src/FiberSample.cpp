// FiberSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <list>
#include <vector>
#include <boost/coroutine/coroutine.hpp>
using namespace boost::coroutines;

class Coroutine{
private:
	static void s_loop(coroutine<int()>::caller_type& yield, Coroutine* coroutine){
		coroutine->m_yield = &yield;

		// この時点ではまだ Coroutine インスタンスが初期化されきってないので、runは呼べない。なので、一度 yield で抜ける.
		yield(0);
		
		// 次回の doContinue呼び出し時にここに到達する.
		coroutine->run();
	}
public:
	Coroutine();
	virtual ~Coroutine(){}
	bool doContinue(){
		if (m_coroutine){
			m_coroutine();
			return true;
		}
		else{
			return false;
		}
	}
protected:
	virtual void run() = 0;
	void yield(){
		(*m_yield)(0);
	}
private:
	coroutine<int()> m_coroutine;
	coroutine<int()>::caller_type* m_yield;
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
	bool go(){
		bool any_did = false;
		for (auto it = m_coroutines.begin(); it != m_coroutines.end();){
			Coroutine* coroutine = *it;
			bool did = coroutine->doContinue();
			any_did |= did;
			if (!did){
				delete coroutine;
				m_coroutines.erase(it++);
			}
			else{
				it++;
			}
		}
		return any_did;
	}
private:
	std::list<Coroutine*> m_coroutines;
};

Coroutine::Coroutine()
	: m_coroutine(std::bind(s_loop, std::placeholders::_1, this))
{
	CoroutineManager::instance()->add(this);
}

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


int _tmain(int argc, _TCHAR* argv[])
{
	printf("main1\n");
	new MyCoroutine();
	new MyCoroutine();
	printf("main2\n");
	while(CoroutineManager::instance()->go()){
		printf("main sleep\n");
	}
	printf("main3\n");
	return 0;
}
