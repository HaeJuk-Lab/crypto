#ifndef __HX_TYPE_H__
#define __HX_TYPE_H__

#include "hxPch.h"

struct hxsUint128
{
    uint64_t high;  // ���� 64��Ʈ
    uint64_t low;   // ���� 64��Ʈ

    hxsUint128( uint64_t h = 0, uint64_t l = 0 )
        : high( h ), low( l )
    {

    }

    // ����
    hxsUint128 operator+( const hxsUint128& other ) const
    {
        hxsUint128 result;
        result.low = low + other.low;
        result.high = high + other.high + (result.low < low);  // carry ó��
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
        result.high = high + other.high + (result.low.low < low.low);  // carry ó��
        return result;
    }
};



#endif // !__HX_TYPE_H__
