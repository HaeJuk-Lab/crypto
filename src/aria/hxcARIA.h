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
 @file		hxcARIA.h
 @brief
 */
#ifndef __HXC_ARIA_H__
#define __HXC_ARIA_H__

#include "hxPch.h"
#include "hxcCipher.hpp"

class hxcARIA : public hxcCipher 
{
    DECLARE_NO_COPY_CLASS( hxcARIA );

public:
    hxcARIA();
    virtual ~hxcARIA() = default;
    void Init( const uint8_t* key, size_t key_len, const uint8_t* iv = nullptr, bool use_cbc = false ) override;
    void Encrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    void Decrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    size_t BlockSize() const override;

private:
    std::unique_ptr<hxsARIA_CTX> ctx;  // ARIA ���ؽ�Ʈ�� unique_ptr�� ����

};

#endif //!__HXC_ARIA_H__