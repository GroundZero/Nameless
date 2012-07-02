#include "CHookManager.hpp"

CHookManager::CHookManager()
{
	m_bEnabled = FALSE;
}

CHookManager::~CHookManager()
{
	Disable();
}

VOID CHookManager::Add(__in PVOID* ppv, __in PVOID pDetour)
{
	m_Hooks[ppv] = pDetour;

	if (Disable())
		Install();
}

VOID CHookManager::Remove(__in PVOID* ppv)
{
	m_Hooks.erase(ppv);

	if (Disable())
		Install();
}

BOOL CHookManager::Set(BOOL bInstall)
{
	DETOUR_FUNC DetourSet;
	LONG        lError;

	if (m_bEnabled == bInstall || m_Hooks.empty())
		return FALSE;

	if (DetourTransactionBegin() != NO_ERROR)
		return FALSE;

	DetourSet = bInstall ? DetourAttach : DetourDetach;

	if (DetourUpdateThread(GetCurrentThread()) == NO_ERROR)
	{
		for(HOOK_MAP::iterator it = this->m_Hooks.begin();  it != this->m_Hooks.end();it++)
		{
			
			lError = DetourSet((*it).first, (*it).second);
			if (lError != NO_ERROR)
				break;
		}
		if (lError == NO_ERROR)
		{
			if (DetourTransactionCommit() == NO_ERROR)
			{
				m_bEnabled = bInstall;
				return TRUE;
			}
		}
	}

	DetourTransactionAbort();
	return FALSE;
}

inline BOOL CHookManager::Install()
{
	return Set(TRUE);
}

inline BOOL CHookManager::Disable()
{
	return Set(FALSE);
}
