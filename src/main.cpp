/******************************************************************************
*  _   _    _    _____    _ _   _ _  __   _        _    ____ ____
* | | | |  / \  | ____|  | | | | | |/ /  | |      / \  | __ ) ___|
* | |_| | / _ \ |  _| _  | | | | | ' /   | |     / _ \ |  _ \___ \
* |  _  |/ ___ \| |__| |_| | |_| | . \   | |___ / ___ \| |_) |__) |
* |_| |_/_/   \_\_____\___/ \___/|_|\_\  |_____/_/   \_\____/____/
*
* Copyright (c) HAEJUK LABS All Rights Reserved.
*
*******************************************************************************/
/**
 @file		main.cpp
 @brief
 */

#include "../include/hxPch.h"

#ifdef __HX_WINDOWS__

BOOL APIENTRY DllMain( HMODULE hModule,	DWORD  ul_reason_for_call, LPVOID lpReserved
)
{
	switch( ul_reason_for_call )
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls( hModule ); 
		} break;
		case DLL_THREAD_ATTACH: {} break;
		case DLL_THREAD_DETACH: {} break;
		case DLL_PROCESS_DETACH:
		{

		} break;
	}
	return TRUE;
}

#else

int main( int argc, char** argv )
{
	return 0;
}

#endif 

