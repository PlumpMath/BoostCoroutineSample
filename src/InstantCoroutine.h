#pragma once

#include <boost/coroutine/coroutine.hpp>
#include <list>

class Coroutine{
private:
	// コルーチンのエントリポイント.
	static void s_loop(boost::coroutines::coroutine<int()>::caller_type& yield, Coroutine* coroutine);
public:
	Coroutine();
	virtual ~Coroutine(){}
	bool doContinue();
protected:
	virtual void run() = 0;
public:
	void yield(){
		(*m_yield)(0);
	}
private:
	boost::coroutines::coroutine<int()> m_coroutine;
	boost::coroutines::coroutine<int()>::caller_type* m_yield;
};

class TinyCoroutine : public Coroutine{
private:
	std::function<void(Coroutine*)> m_func;
public:
	TinyCoroutine(std::function<void(Coroutine*)> func) : m_func(func) {}
	void run(){
		m_func(this);
	}
};


class CoroutineManager{
public:
	static CoroutineManager* instance(){
		static CoroutineManager theInstance;
		return &theInstance;
	}
public:
	void add(Coroutine* coroutine);
	bool go();
private:
	std::list<Coroutine*> m_coroutines;
};
