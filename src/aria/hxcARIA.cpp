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
 @file		hxcARIA.cpp
 @brief
 */
#include "hxcARIA.h"

hxcARIA::hxcARIA() 
    : m_ctx( std::make_unique<hxsARIA_CTX>() ) 
    , m_pImpl( std::make_unique<hxcARIAImpl>() )
{

}

void hxcARIA::Init( const uint8_t* key, size_t key_len, const uint8_t* iv, bool use_cbc )
{
    m_ctx->Init( key, key_len, iv );
    m_ctx->cbc_mode = use_cbc;
}

void hxcARIA::Encrypt( const uint8_t* input, uint8_t* output, size_t length ) 
{
    for( size_t i = 0; i < length; i += 16 )
    {
        if( m_ctx->cbc_mode )
        { 
            // CBC 모드 암호화
            for( int j = 0; j < 16; j++ )
            {
                m_ctx->State[j / 4][j % 4] = m_ctx->IV[j] ^ input[i + j];
            }
            m_pImpl->ARIA_EncryptBlock( m_ctx->State, m_ctx->RoundKeys.data(), m_ctx->NumRounds );
            std::memcpy( output + i, m_ctx->State, 16 );
            std::memcpy( m_ctx->IV, output + i, 16 ); // IV 업데이트
        }
        else
        {
            // ECB 모드 암호화
            std::memcpy( m_ctx->State, input + i, 16 );
            m_pImpl->ARIA_EncryptBlock( m_ctx->State, m_ctx->RoundKeys.data(), m_ctx->NumRounds );
            std::memcpy( output + i, m_ctx->State, 16 );
        }
    }
}

void hxcARIA::Decrypt( const uint8_t* input, uint8_t* output, size_t length ) 
{
    uint8_t temp[16];
    for( size_t i = 0; i < length; i += 16 )
    {
        std::memcpy( temp, input + i, 16 );
        std::memcpy( m_ctx->State, input + i, 16 );
        m_pImpl->ARIA_DecryptBlock( m_ctx->State, m_ctx->RoundKeys.data(), m_ctx->NumRounds );
        if( m_ctx->cbc_mode )
        {
            // CBC 모드 복호화
            for( int j = 0; j < 16; j++ ) 
            {
                output[i + j] = m_ctx->State[j / 4][j % 4] ^ m_ctx->IV[j];
            }
            std::memcpy( m_ctx->IV, temp, 16 ); // IV 업데이트
        }
        else 
        {
            // ECB 모드 복호화
            std::memcpy( output + i, m_ctx->State, 16 );
        }
    }
}

size_t hxcARIA::BlockSize() const 
{
    return 16;
}