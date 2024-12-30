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
 @file		hxcByteArray.h
 @brief
 */

#ifndef __HXC_BYTE_ARRAY_H__
#define __HXC_BYTE_ARRAY_H__
#include "include/hxPch.h"

class hxcByteArray 
{
    DECLARE_NO_COPY_CLASS( hxcByteArray );

public:
    hxcByteArray( size_t size = 0 );
    ~hxcByteArray() = default;

    // ������ ����
    void Append( const uint8_t* data, size_t len );
    
    // ����Ʈ ����
    uint8_t& operator[]( size_t index );
    
    // ���� ��ȯ
    size_t Length() const;

    const uint8_t* Data() const;

private:
    std::vector<uint8_t> buffer;
};

#endif // !__HXC_BYTE_ARRAY_H__
