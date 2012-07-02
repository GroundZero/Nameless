#include <Windows.h>
#include "CRajan.hpp"

void Init()
{
	new CRajan();
}


int WINAPI DllMain( HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved )
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&Init,NULL,NULL,NULL);
	}
	return 1;
}

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	return 1;
}