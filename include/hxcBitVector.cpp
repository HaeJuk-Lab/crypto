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
 @file		hxcBitVector.cpp
 @brief
 */
#include "hxcBitVector.h"

hxcBitVector::hxcBitVector( size_t bit_size )
    : bits( (bit_size + 7) / 8, 0 )
{

}

// 특정 비트 설정
void hxcBitVector::SetBit( size_t index, bool value )
{
    size_t byte_index = index / 8;
    size_t bit_index = index % 8;
    if( value ) {
        bits[byte_index] |= (1 << bit_index);
    }
    else {
        bits[byte_index] &= ~(1 << bit_index);
    }
}

// 특정 비트 읽기
bool hxcBitVector::GetBit( size_t index ) const
{
    size_t byte_index = index / 8;
    size_t bit_index = index % 8;
    return (bits[byte_index] & (1 << bit_index)) != 0;
}

// 비트 개수 반환
size_t hxcBitVector::Size() const
{
    return bits.size() * 8;
}
