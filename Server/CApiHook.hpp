#ifndef CAPI_HOOK_HPP_
#define CAPI_HOOK_HPP_

#include "CHookManager.hpp"


typedef struct _API_FUNCTION
{
	PVOID pTarget;
	DWORD dwLocation;
} API_FUNCTION;

typedef struct _API_HOOK
{
	PVOID           pHook;
	_API_FUNCTION  Function;
} API_HOOK;


class CApiHook : public CHookManager
{
public:
	CApiHook();
	~CApiHook();
	VOID AddApi(__in API_HOOK apiHook);
	VOID RemoveApi(__in API_HOOK apiHook);
};

#endif
