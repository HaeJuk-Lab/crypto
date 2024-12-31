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
 @file		hxcAES.h
 @brief
 */
#ifndef __HXC_AES_H__
#define __HXC_AES_H__

#include "hxPch.h"
#include "hxcCipher.hpp"

class hxcAES : public hxcCipher 
{
    DECLARE_NO_COPY_CLASS( hxcAES );


public:
    hxcAES() : ctx( std::make_unique<hxsAES_CTX>() ) {}
    virtual ~hxcAES() = default; 

    void Init( const uint8_t* key, size_t key_len, const uint8_t* iv = nullptr, bool use_cbc = false ) override 
    {
        AES_Init( ctx.get(), key, key_len );
        ctx->cbc_mode = use_cbc;
        if( iv && use_cbc ) {
            memcpy( ctx->iv, iv, 16 );
        }
    }

    void Encrypt( const uint8_t* input, uint8_t* output, size_t length ) override 
    {
        AES_Encrypt( ctx.get(), input, output, length );
    }

    void Decrypt( const uint8_t* input, uint8_t* output, size_t length ) override
    {
        AES_Decrypt( ctx.get(), input, output, length );
    }

    size_t BlockSize() const override 
    {
        return 16;
    }

private:
    std::unique_ptr<hxsAES_CTX> ctx;  // AES 컨텍스트를 unique_ptr로 관리

};


#endif // !__HXC_AES_H__

