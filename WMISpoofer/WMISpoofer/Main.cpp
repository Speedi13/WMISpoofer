#include "MinHook\MinHook.h"
#include "WMIHook\WMIHook.hpp"

HINSTANCE hSelf = NULL;

DWORD WINAPI Initialize(
	void*
)
{
	MH_Initialize();

	WMIHook::Initialize(
		hSelf
	);

	return ERROR_SUCCESS;
}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,
	DWORD fdwReason,
	LPVOID
)
{
	if (
		fdwReason == DLL_PROCESS_ATTACH
		)
	{
		hSelf = hinstDLL;
		//for hooking faster hook the function from the dllmain
		//old method was calling  creating a thread
		if ( Initialize(NULL) == ERROR_SUCCESS)
			return TRUE;
	}
	else if (
		fdwReason == DLL_PROCESS_DETACH
		)
	{
		WMIHook::Uninitialize();
		MH_Uninitialize();
	}

	return FALSE;
}
