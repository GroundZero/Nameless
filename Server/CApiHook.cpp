#include "CApiHook.hpp"

void CApiHook::AddApi(__in API_HOOK apiHook)
{
	*(PVOID*)apiHook.Function.pTarget = (PVOID)apiHook.Function.dwLocation;

	this->Add((PVOID*)apiHook.Function.pTarget, apiHook.pHook);
}
void CApiHook::RemoveApi(__in API_HOOK apiHook)
{
	this->Remove((PVOID*)apiHook.Function.pTarget);
}

CApiHook::CApiHook()
{

}

CApiHook::~CApiHook()
{

}