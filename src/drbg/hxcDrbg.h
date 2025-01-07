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
 @file		hxcDrbg.h
 @brief
 */
#ifndef  __HXC_DRBG_H__
#define  __HXC_DRBG_H__

#include "hxPch.h"

class hxcDrbg
{
public:
	hxcDrbg() = default;
	virtual ~hxcDrbg() = default;

	virtual void Initialize( const std::vector<uint8_t>& _vSeed ) = 0;
	virtual std::vector<uint8_t> Generate( size_t _nSize ) = 0;
	virtual void ReSeed() = 0;

private:
	virtual void InCrementV() = 0;
};


#endif // ! __HXC_DRBG_H__
