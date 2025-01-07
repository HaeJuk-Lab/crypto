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
 @file		hxcNoiseCollectorImpl.cpp
 @brief
 */
#ifdef __HX_MACOS__

#include "hxcNoiseCollectorImpl.h"

hxcNoiseCollectorImpl::hxcNoiseCollectorImpl()
{

}

hxcNoiseCollectorImpl::~hxcNoiseCollectorImpl()
{

}

ErrCode hxcNoiseCollectorImpl::CollectPID( std::vector<uint8_t>& _vNoise )
{
	ErrCode nRet = Err_Success;

	return nRet;
}

ErrCode hxcNoiseCollectorImpl::CollectHeapAddress( std::vector<uint8_t>& _vNoise )
{
	ErrCode nRet = Err_Success;

	return nRet;
}

ErrCode hxcNoiseCollectorImpl::CollectHeapData( std::vector<uint8_t>& _vNoise )
{
	ErrCode nRet = Err_Success;

	return nRet;
}

ErrCode hxcNoiseCollectorImpl::CollectRandomDevice( std::vector<uint8_t>& _vNoise )
{
	ErrCode nRet = Err_Success;

	return nRet;
}

ErrCode hxcNoiseCollectorImpl::CollectProcessName( std::vector<uint8_t>& _vNoise )
{
	ErrCode nRet = Err_Success;

	return nRet;

}

ErrCode hxcNoiseCollectorImpl::Reset()
{
	ErrCode nRet = Err_Success;

	return nRet;
}
#endif //__HX_MACOS__