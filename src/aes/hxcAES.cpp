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

namespace
{
  
}

hxcAES::hxcAES() 
    : m_ctx( std::make_unique<hxsAES_CTX>() ) 
    , m_pImpl( std::make_unique<hxcAESImpl>() )
{

}

ErrCode hxcAES::Init( const uint8_t* key, size_t key_len, const uint8_t* iv, bool use_cbc )
{
    ErrCode nRet = Err_Success;

    m_ctx->Init( key, key_len, iv );
    m_ctx->cbc_mode = use_cbc;

    return nRet;
}

ErrCode hxcAES::Generatorkey( INOUT uint8_t* _ppBuffer, size_t _nkeylen )
{
    ErrCode nRet = Err_Success;

    return nRet;
}

ErrCode hxcAES::CheckInitOpValues()
{
    ErrCode nRet = Err_Success;

    return nRet;
}


ErrCode hxcAES::Encrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    ErrCode nRet = Err_Success;

    for( size_t i = 0; i < length; i += 16 ) 
    {
        if( m_ctx->cbc_mode )
        { 
            // CBC ��� ��ȣȭ
            for( int j = 0; j < 16; j++ ) 
            {
                m_ctx->State[j / 4][j % 4] = m_ctx->IV[j] ^ input[i + j];
            }
            m_pImpl->AES_EncryptBlock( m_ctx->State, m_ctx->RoundKeys.data(), m_ctx->NumRounds );
            std::memcpy( output + i, m_ctx->State, 16 );
            std::memcpy( m_ctx->IV, output + i, 16 ); // IV ������Ʈ
        }
        else
        { 
            // ECB ��� ��ȣȭ
            std::memcpy( m_ctx->State, input + i, 16 );
            m_pImpl->AES_EncryptBlock( m_ctx->State, m_ctx->RoundKeys.data(), m_ctx->NumRounds );
            std::memcpy( output + i, m_ctx->State, 16 );
        }
    }

    return nRet;
}

ErrCode hxcAES::Decrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    ErrCode nRet = Err_Success;


    uint8_t temp[16];
    for( size_t i = 0; i < length; i += 16 )
    {
        std::memcpy( temp, input + i, 16 );
        std::memcpy( m_ctx->State, input + i, 16 );
        m_pImpl->AES_DecryptBlock( m_ctx->State, m_ctx->RoundKeys.data(), m_ctx->NumRounds );
        if( m_ctx->cbc_mode )
        { 
            // CBC ��� ��ȣȭ
            for( int j = 0; j < 16; j++ ) 
            {
                output[i + j] = m_ctx->State[j / 4][j % 4] ^ m_ctx->IV[j];
            }
            std::memcpy( m_ctx->IV, temp, 16 ); // IV ������Ʈ
        }
        else 
        { 
            // ECB ��� ��ȣȭ
            std::memcpy( output + i, m_ctx->State, 16 );
        }
    }

    return nRet;
}

size_t hxcAES::BlockSize() const
{
    return 16;
}
