#include "CRajan.hpp"

API_HOOK CreateWindowExAHook = { CreateWindowExA_Hook,  { &_CreateWindowExA, reinterpret_cast<DWORD>(&CreateWindowExA) } };
API_HOOK RegisterClassExAHook = { RegisterClassExA_Hook,  { &_RegisterClassExA, reinterpret_cast<DWORD>(&RegisterClassExA) } };

inline void __cdecl DebugPrintA(char *format, ...)
{
	static char buff[4096];
	static HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
	static DWORD written;
	va_list va;
	va_start(va, format);
	vsprintf_s(buff, format, va);
	WriteFile(outh, buff, strlen(buff), &written, NULL);
	va_end(va);
}


LRESULT CALLBACK WndProcHook(HWND hWnd,UINT uMessage,WPARAM wParam,LPARAM lParam)
{
	if(uMessage == WM_COPYDATA)
	{
		RajanClass->HandleMessage(reinterpret_cast<PCOPYDATASTRUCT>(lParam));
		return TRUE;
	}

	else if(uMessage == WM_CREATE)
		DebugPrintA("HWND: %i\n",hWnd);

	return Maple_WndProc(hWnd,uMessage,wParam,lParam);
}



ATOM WINAPI RegisterClassExA_Hook(__in WNDCLASSEXA *wndClass)
{
	if(!strcmp(wndClass->lpszClassName, "MapleStoryClass"))
	{
		Maple_WndProc = wndClass->lpfnWndProc;
		wndClass->lpfnWndProc = WndProcHook;
		DebugPrintA("Got WndProc\n");
	}
	return _RegisterClassExA(wndClass);
}
HWND WINAPI CreateWindowExA_Hook(__in DWORD dwExStyle, __in_opt LPCSTR lpClassName,
	__in_opt LPCSTR lpWindowName, __in DWORD dwStyle, __in int X, __in int Y, __in int nWidth,
	__in int nHeight, __in_opt HWND hWndParent, __in_opt HMENU hMenu, __in_opt HINSTANCE hInstance,
	__in_opt LPVOID lpParam)
{
	if(!strcmp(lpClassName,"StartUpDlgClass") && !strcmp(lpWindowName, "MapleStory"))
	{
		DebugPrintA("Window was blocked\n");
		return NULL;
	}
	if (!strcmp(lpClassName, "NexonADBallon") && !strcmp(lpWindowName, "ad.")) 	
	{  	
		DebugPrintA("Window was blocked\n");
		return NULL;
	} 	
	if(!strcmp(lpClassName, "MapleStoryClass"))
	{
		RajanClass->hWnd = _CreateWindowExA(dwExStyle,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,hMenu,
			hInstance,lpParam);

		return RajanClass->hWnd;
	}

	return _CreateWindowExA(dwExStyle,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,hMenu,
		hInstance,lpParam);
}


CRajan::CRajan()
{
	this->hWnd = NULL;
	this->m_apiHook = new CApiHook();


	this->m_apiHook->AddApi(CreateWindowExAHook);
	this->m_apiHook->AddApi(RegisterClassExAHook);
	this->m_apiHook->AddApi(GetForegroundWindowHook);



	if(this->m_apiHook->Install())
	DebugPrintA("Installed\n");

	RajanClass = this;
}
CRajan::~CRajan()
{
this->m_apiHook->Disable();	
}

void CRajan::HandleMessage(PCOPYDATASTRUCT data)
{
	DebugPrintA("Handling Message, size: %i\n",data->cbData);
	
	DebugPrintA("%s\n",data->lpData);
}
void CRajan::SendMessage(PCOPYDATASTRUCT data)
{
	
}

