#include "stdafx.h"
#include "InstantCoroutine.h"

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
// Coroutine
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
// コルーチンのエントリポイント.
void Coroutine::s_loop(boost::coroutines::coroutine<int()>::caller_type& yield, Coroutine* coroutine)
{
	coroutine->m_yield = &yield;

	// この時点ではまだ Coroutine インスタンスが初期化されきってないので、runは呼べない。なので、一度 yield で抜ける.
	yield(0);

	// 次回の doContinue呼び出し時にここに到達する.
	coroutine->run();
}

Coroutine::Coroutine()
	: m_coroutine(std::bind(s_loop, std::placeholders::_1, this))
{
	CoroutineManager::instance()->add(this);
}

bool Coroutine::doContinue()
{
	if (m_coroutine){
		m_coroutine();
		return true;
	}
	else{
		return false;
	}
}

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
// CoroutineManager
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
void CoroutineManager::add(Coroutine* coroutine)
{
	m_coroutines.push_back(coroutine);
}

bool CoroutineManager::go()
{
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
