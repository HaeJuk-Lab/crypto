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
 @file		hxcNoiseCollectorImpl.h
 @brief
 */
#ifdef __HX_WINDOWS__

#ifndef __HXC_NOISE_COLLECTOR_IMPL_H__
#define __HXC_NOISE_COLLECTOR_IMPL_H__

#include "hxPch.h"
#include "../hxcNoiseCollectorImplInterface.h"

class hxcNoiseCollectorImpl : public hxcNoiseCollectorImplInterface
{
	DECLARE_NO_COPY_CLASS( hxcNoiseCollectorImpl );

public:
	hxcNoiseCollectorImpl();
	virtual ~hxcNoiseCollectorImpl();
	ErrCode CollectPID( std::vector<uint8_t>& _vNoise ) override;
	ErrCode CollectHeapAddress( std::vector<uint8_t>& _vNoise ) override;
	ErrCode CollectHeapData( std::vector<uint8_t>& _vNoise ) override;
	ErrCode CollectRandomDevice( std::vector<uint8_t>& _vNoise ) override;
	ErrCode CollectProcessName( std::vector<uint8_t>& _vNoise ) override;
	ErrCode Reset() override;
private:

};

#endif //!__HXC_NOISE_COLLECTOR_IMPL_H__

#endif //__HX_WINDOWS__