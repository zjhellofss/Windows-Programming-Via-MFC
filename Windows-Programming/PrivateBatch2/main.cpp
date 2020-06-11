#include <iostream>
#include <Windows.h>
#include <strsafe.h>

/**
 * todo 存在不明原因的内存访问错误
 *
 */
PTP_CLEANUP_GROUP g_pCleanupGroup = NULL;

class ThreadPool
{
public:
	ThreadPool(): m_bIsinit(false), m_pThreadPool(NULL)
	{
	}

	~ThreadPool();
	bool Init();
	void Run();
private:
	bool m_bIsinit;
	PTP_POOL m_pThreadPool;
	TP_CALLBACK_ENVIRON m_callbackEnvironment;
};

ThreadPool::~ThreadPool()
{
	if (m_pThreadPool != NULL && m_bIsinit)
	{
		CloseThreadpool(m_pThreadPool);
		DestroyThreadpoolEnvironment(&m_callbackEnvironment);
	}
}

bool ThreadPool::Init()
{
	if (m_pThreadPool != NULL)
	{
		if (m_pThreadPool != NULL)
		{
			CloseThreadpool(m_pThreadPool);
		}

		DestroyThreadpoolEnvironment(&m_callbackEnvironment);
	}

	m_pThreadPool = CreateThreadpool(NULL);
	if (m_pThreadPool == NULL)
	{
		return false;
	}

	SetThreadpoolThreadMaximum(m_pThreadPool, 4);
	if (!SetThreadpoolThreadMinimum(m_pThreadPool, 2))
	{
		return false;
	}

	InitializeThreadpoolEnvironment(&m_callbackEnvironment);

	SetThreadpoolCallbackPool(&m_callbackEnvironment, m_pThreadPool);
	this->m_bIsinit = true;
	return true;
}

int lastWorkTime = 0;
bool g_bEnding = false;
VOID SimpleHandler(PTP_CALLBACK_INSTANCE Instance, PVOID Context)
{
	// Ensure not bad random
	int workTime = ((rand() % 4) + 1);
	while (workTime == lastWorkTime)
	{
		workTime = ((rand() % 4) + 1);
	}
	lastWorkTime = workTime;


	std::cout << "Handler started" << std::endl;
	Sleep(workTime * 1000);

	std::cout << "Handler ending" << std::endl;
	if (!g_bEnding)
	{
		g_bEnding = true;
	}
}


void ThreadPool::Run()
{
	srand(GetTickCount());

	if (TrySubmitThreadpoolCallback((PTP_SIMPLE_CALLBACK)
	                                SimpleHandler, "NULL", &m_callbackEnvironment))
	{
		std::cout << "Submit" << std::endl;
	}
	else
	{
		std::cout << "Can not Submit" << std::endl;
	}
}


int main()
{
	ThreadPool p;
	bool bRes = p.Init();
	if (bRes)
	{
		p.Run();
	}
	while(!g_bEnding)
	{
		;
	}
	return 0;
}
