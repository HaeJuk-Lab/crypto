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
 @file		hxcSEED.cpp
 @brief
 */
#include "hxcSEED.h"

hxcSEED::hxcSEED() 
    : m_ctx( std::make_unique<hxsSEED_CTX>() ) 
    , m_pImpl( std::make_unique<hxcSEEDImpl>() )
{

}

void hxcSEED::Init( const uint8_t* key, size_t key_len, const uint8_t* iv, bool use_cbc ) 
{
    m_pImpl->SEED_Init( m_ctx.get(), key, key_len );
    m_ctx->cbc_mode = use_cbc;
    if( iv && use_cbc )
    {
        memcpy( m_ctx->iv, iv, 16 );
    }
}

void hxcSEED::Encrypt( const uint8_t* input, uint8_t* output, size_t length ) 
{
    m_pImpl->SEED_Encrypt( m_ctx.get(), input, output, length );
}

void hxcSEED::Decrypt( const uint8_t* input, uint8_t* output, size_t length ) 
{
    m_pImpl->SEED_Decrypt( m_ctx.get(), input, output, length );
}

size_t hxcSEED::BlockSize() const
{
    return 16;
}