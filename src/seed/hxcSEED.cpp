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

ErrCode hxcSEED::Init( const uint8_t* key, size_t key_len, const uint8_t* iv, bool use_cbc )
{
    ErrCode nRet = Err_Success;
    m_pImpl->SEED_Init( m_ctx.get(), key, key_len );
    m_ctx->cbc_mode = use_cbc;
    if( iv && use_cbc )
    {
        memcpy( m_ctx->iv, iv, 16 );
    }
    return nRet;
}

ErrCode hxcSEED::Generatorkey(INOUT uint8_t* _ppBuffer, size_t _nkeylen )
{
    ErrCode nRet = Err_Success;
    //-----------------------------------------------------------------------------------------------
    // 초기화 체크 
    nRet = CheckInitOpValues();
    if( Err_Success != nRet )
    {
        return nRet;
    }


    return nRet;
}

ErrCode hxcSEED::CheckInitOpValues()
{
    ErrCode nRet = Err_Success;

    return nRet;
}

ErrCode hxcSEED::Encrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    ErrCode nRet = Err_Success;

    //-----------------------------------------------------------------------------------------------
    // 초기화 체크 
    nRet = CheckInitOpValues();
    if( Err_Success != nRet )
    {
        return nRet;
    }

    m_pImpl->SEED_Encrypt( m_ctx.get(), input, output, length );
    
    return nRet;
}

ErrCode hxcSEED::Decrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    ErrCode nRet = Err_Success;
    
    //-----------------------------------------------------------------------------------------------
    // 초기화 체크 
    nRet = CheckInitOpValues();
    if( Err_Success != nRet )
    {
        return nRet;
    }

    m_pImpl->SEED_Decrypt( m_ctx.get(), input, output, length );

    return nRet;
}

size_t hxcSEED::BlockSize() const
{
    return 16;
}