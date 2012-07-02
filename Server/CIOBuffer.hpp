#ifndef CIO_BUFFER_HPP_
#define CIO_BUFFER_HPP_

#include <windows.h>

#include <map>



typedef LONG (WINAPI * DETOUR_FUNC)(__in PVOID* ppv, __in PVOID pDetour);
typedef std::map<PVOID*, PVOID> HOOK_MAP;

class CIOBuffer
{
private:
	HOOK_MAP m_Hooks;
	BOOL m_bEnabled;
	BOOL Set(__in BOOL bInstall);
public:
	CHookManager();
	~CHookManager();
	VOID Add(__in PVOID* ppv, __in PVOID pDetour);
	VOID Remove(__in PVOID* ppv);
	BOOL Install();
	BOOL Disable();
};

#endif // CHOOK_MANAGER_HPP_
