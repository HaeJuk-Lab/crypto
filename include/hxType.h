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
 @file		hxType.h
 @brief
 */

#ifndef __HX_TYPE_H__
#define __HX_TYPE_H__

#include "hxPch.h"

struct hxsUint128
{
    uint64_t high;  // 상위 64비트
    uint64_t low;   // 하위 64비트

    hxsUint128( uint64_t h = 0, uint64_t l = 0 )
        : high( h ), low( l )
    {

    }

    // 덧셈
    hxsUint128 operator+( const hxsUint128& other ) const
    {
        hxsUint128 result;
        result.low = low + other.low;
        result.high = high + other.high + (result.low < low);  // carry 처리
        return result;
    }
};

struct hxsUint256
{
    hxsUint128 high;
    hxsUint128 low;

    hxsUint256( hxsUint128 h = {}, hxsUint128 l = {} ) : high( h ), low( l ) {}

    hxsUint256 operator+( const hxsUint256& other ) const {
        hxsUint256 result;
        result.low = low + other.low;
        result.high = high + other.high + (result.low.low < low.low);  // carry 처리
        return result;
    }
};



#endif // !__HX_TYPE_H__
