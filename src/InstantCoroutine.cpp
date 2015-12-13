#include "stdafx.h"
#include "InstantCoroutine.h"

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
// Coroutine
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
// �R���[�`���̃G���g���|�C���g.
void Coroutine::s_loop(boost::coroutines::coroutine<int()>::caller_type& yield, Coroutine* coroutine)
{
	coroutine->m_yield = &yield;

	// ���̎��_�ł͂܂� Coroutine �C���X�^���X�����������ꂫ���ĂȂ��̂ŁArun�͌ĂׂȂ��B�Ȃ̂ŁA��x yield �Ŕ�����.
	yield(0);

	// ����� doContinue�Ăяo�����ɂ����ɓ��B����.
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
