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
 @file		hxcBitVector.h
 @brief
 */

#ifndef __HXC_BIT_VECTOR_H__
#define __HXC_BIT_VECTOR_H__

#include "include/hxPch.h"

class hxcBitVector 
{
    DECLARE_NO_COPY_CLASS( hxcBitVector );

public:
    hxcBitVector( size_t bit_size = 0 );
    ~hxcBitVector() = default;

    // Ư�� ��Ʈ ����
    void SetBit( size_t index, bool value );

    // Ư�� ��Ʈ �б�
    bool GetBit( size_t index ) const;

    // ��Ʈ ���� ��ȯ
    size_t Size() const;

private:
    std::vector<uint8_t> bits;
};

#endif // !__HXC_BIT_VECTOR_H__
