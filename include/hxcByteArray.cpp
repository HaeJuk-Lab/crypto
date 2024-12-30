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
 @file		hxcByteArray.cpp
 @brief
 */
#include "hxcByteArray.h"

hxcByteArray::hxcByteArray( size_t size)
    : buffer( size )
{
}

// 데이터 삽입
void hxcByteArray::Append( const uint8_t* data, size_t len )
{
    buffer.insert( buffer.end(), data, data + len );
}

// 바이트 접근
uint8_t& hxcByteArray::operator[]( size_t index )
{
    return buffer[index];
}

// 길이 반환
size_t hxcByteArray::Length() const
{
    return buffer.size();
}

const uint8_t* hxcByteArray::Data() const
{
    return buffer.data();
}