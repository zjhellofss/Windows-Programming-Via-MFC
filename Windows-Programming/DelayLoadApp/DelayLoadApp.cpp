#include <windows.h>
// uncomment these lines to remove .libs from command line
#pragma comment(lib, "Delayimp.lib")
const wchar_t* g_szModuleName = L"user32.dll";

bool IsMouduleBeLoaded()
{
	HMODULE hmod = GetModuleHandle(g_szModuleName);
	if (hmod == NULL)
	{
		return false;
	}else
	{
		return true;
	}
}

int main()
{
	//判断user32.dll是否被载入
	bool f1 = IsMouduleBeLoaded();
	MessageBox(NULL, L"Hello", L"Hello", MB_OK);
	f1 = IsMouduleBeLoaded();
	return 0;
}
