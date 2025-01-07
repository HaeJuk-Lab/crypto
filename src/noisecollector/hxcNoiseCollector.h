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
 @file		hxcNoiseCollector.h
 @brief
 */
#ifndef __HXC_NOISE_COLLECTOR_H__
#define __HXC_NOISE_COLLECTOR_H__

#include "hxPch.h"

class hxcNoiseCollectorImpl;

class hxcNoiseCollector
{
	DECLARE_NO_COPY_CLASS( hxcNoiseCollector );

public:
	hxcNoiseCollector();
	virtual ~hxcNoiseCollector();
	std::vector<uint8_t> CollectNoise(int _nRepeatCount = 0 );

private:
	std::unique_ptr<hxcNoiseCollectorImpl> m_pImpl;
};

#endif //! __HXC_NOISE_COLLECTOR_H__