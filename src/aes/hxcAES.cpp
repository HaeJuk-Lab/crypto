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
 @file		hxcAES.cpp
 @brief
 */
#include "hxcAES.h"

hxcAES::hxcAES() 
    : ctx( std::make_unique<hxsAES_CTX>() ) 
{

}

void hxcAES::Init( const uint8_t* key, size_t key_len, const uint8_t* iv, bool use_cbc )
{
    AES_Init( ctx.get(), key, key_len );
    ctx->cbc_mode = use_cbc;
    if( iv && use_cbc ) {
        memcpy( ctx->iv, iv, 16 );
    }
}

void hxcAES::Encrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    AES_Encrypt( ctx.get(), input, output, length );
}

void hxcAES::Decrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    AES_Decrypt( ctx.get(), input, output, length );
}

size_t hxcAES::BlockSize() const
{
    return 16;
}