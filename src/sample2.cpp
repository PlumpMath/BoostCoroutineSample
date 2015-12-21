#include "stdafx.h"
#include "InstantCoroutine.h"
#include <string>

class MyCoroutine : public Coroutine{
public:
	MyCoroutine(std::string name, int cnt){
		m_name = name;
		m_cnt = cnt;
		printf("%s start.\n", m_name.c_str());
	}
	~MyCoroutine(){
		printf("%s end.\n", m_name.c_str());
	}
	void run(){
		for (int i = 0; i < m_cnt; i++){
			yield();
			printf("%s %d\n", m_name.c_str(), i);
		}
	}
private:
	std::string m_name;
	int m_cnt;
};

void sample2()
{
	new MyCoroutine("hello", 4);
	new MyCoroutine("world", 2);
	
	printf("manager start.\n");
	while (CoroutineManager::instance()->go()){
		printf("manager sleep\n");
	}
	printf("manager end.\n");
}
