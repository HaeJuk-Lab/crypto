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
 @file		hxcNoiseCollectorImplInterface.h
 @brief
 */
#ifndef __HXC_NOISE_COLLECTOR_IMPL_INTERFACE_H__
#define __HXC_NOISE_COLLECTOR_IMPL_INTERFACE_H__

#include "hxPch.h"

class hxcNoiseCollectorImplInterface
{
	DECLARE_NO_COPY_CLASS( hxcNoiseCollectorImplInterface );

public:
    hxcNoiseCollectorImplInterface() = default;
	virtual ~hxcNoiseCollectorImplInterface() = default;

    virtual ErrCode CollectPID( std::vector<uint8_t>& _vNoise ) = 0;
    virtual ErrCode CollectHeapAddress( std::vector<uint8_t>& _vNoise ) = 0;
    virtual ErrCode CollectHeapData( std::vector<uint8_t>& _vNoise ) = 0;
    virtual ErrCode CollectRandomDevice( std::vector<uint8_t>& _vNoise ) = 0;
    virtual ErrCode CollectProcessName( std::vector<uint8_t>& _vNoise ) = 0;
    virtual ErrCode Reset();
};

#endif // !__HXC_NOISE_COLLECTOR_H__
