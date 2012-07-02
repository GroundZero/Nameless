#ifndef CRAJAN_HPP_
#define CRAJAN_HPP_

#include "CApiHook.hpp"


typedef ATOM (WINAPI* Win32_RegisterClassExA)(__in CONST WNDCLASSEXA *wndClass);
typedef HWND (WINAPI* Win32_CreateWindowExA)(__in DWORD dwExStyle, __in_opt LPCSTR lpClassName, __in_opt LPCSTR lpWindowName, __in DWORD dwStyle, __in int X, __in int Y, __in int nWidth, __in int nHeight, __in_opt HWND hWndParent, __in_opt HMENU hMenu, __in_opt HINSTANCE hInstance, __in_opt LPVOID lpParam);

static Win32_RegisterClassExA _RegisterClassExA = NULL;
static Win32_CreateWindowExA _CreateWindowExA = NULL;
static WNDPROC Maple_WndProc = NULL;

static ATOM WINAPI RegisterClassExA_Hook(__in WNDCLASSEXA *wndClass);
static HWND WINAPI CreateWindowExA_Hook(__in DWORD dwExStyle, __in_opt LPCSTR lpClassName, __in_opt LPCSTR lpWindowName, __in DWORD dwStyle, __in int X, __in int Y, __in int nWidth, __in int nHeight, __in_opt HWND hWndParent, __in_opt HMENU hMenu, __in_opt HINSTANCE hInstance, __in_opt LPVOID lpParam);

static LRESULT CALLBACK WndProcHook(HWND hWnd,UINT uMessage,WPARAM wParam,LPARAM lParam);

class CRajan
{
private:
	CApiHook* m_apiHook;
public:
	CRajan();
	~CRajan();

	void HandleMessage(PCOPYDATASTRUCT data);
	void SendMessage(PCOPYDATASTRUCT data);

	HWND hWnd;
};

static CRajan* RajanClass;

#endif
