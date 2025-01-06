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

ErrCode hxcARIA::Init( const hxsAria* _pKey )
{
    ErrCode nRet = Err_Success;

    m_ctx->eMode = _pKey->eMode;
    if( hxeAriaKeySize::eAria128 == _pKey->eKeySize )
    {
        const hxsAria128* pKey = reinterpret_cast<const  hxsAria128*>(_pKey);
        m_ctx->Init( pKey->nkey, pKey->eKeySize, pKey->nIv );
    }
    else if( hxeAriaKeySize::eAria192 == _pKey->eKeySize )
    {
        const hxsAria192* pKey = reinterpret_cast<const  hxsAria192*>(_pKey);
        m_ctx->Init( pKey->nkey, pKey->eKeySize, pKey->nIv );
    }
    else if( hxeAriaKeySize::eAria256 == _pKey->eKeySize )
    {
        const hxsAria256* pKey = reinterpret_cast<const  hxsAria256*>(_pKey);
        m_ctx->Init( pKey->nkey, pKey->eKeySize, pKey->nIv );
    }
    
    return nRet;
}

ErrCode hxcARIA::Generatorkey( INOUT hxsAria* _pKey, size_t _nlength )
{
    ErrCode nRet = Err_Success;
    
    //-----------------------------------------------------------------------------------------------
    // 초기화 체크 
    nRet = CheckInitOpValues();
    if( Err_Success != nRet )
    {
        return nRet;
    }

    _pKey->eMode = hxeAriaMode::eAriaCBCMode;

    if( hxeAriaKeySize::eAria128 == _nlength )
    {
        hxsAria128* pKey = reinterpret_cast<hxsAria128*>(_pKey);
        if( nullptr != pKey )
        {
            //---------------------------------------------------------------------------
            // 초기화 
            std::fill( std::begin( pKey->nkey ), std::end( pKey->nkey ), 0 );
            std::fill( std::begin( pKey->nIv ), std::end( pKey->nIv ), 0 );
            pKey->eKeySize = hxeAriaKeySize::eAria128;

            //---------------------------------------------------------------------------
            // Gen 16Byte Random Key    
            this->GeneratorRandomData( pKey->nkey, _nlength );

            //---------------------------------------------------------------------------
            // Gen 16Byte Random Iv
            this->GeneratorRandomData( pKey->nIv, ARIA_BLOCK_MODE_IV_SIZE );

            return nRet;
        }
    }
    else if( hxeAriaKeySize::eAria192 == _nlength )
    {
        hxsAria192* pKey = reinterpret_cast<hxsAria192*>(_pKey);
        if( nullptr != pKey )
        {
            //---------------------------------------------------------------------------
            // 초기화 
            std::fill( std::begin( pKey->nkey ), std::end( pKey->nkey ), 0 );
            std::fill( std::begin( pKey->nIv ), std::end( pKey->nIv ), 0 );
            pKey->eKeySize = hxeAriaKeySize::eAria192;

            //---------------------------------------------------------------------------
            // Gen 16Byte Random Key    
            this->GeneratorRandomData( pKey->nkey, _nlength );

            //---------------------------------------------------------------------------
            // Gen 16Byte Random Iv
            this->GeneratorRandomData( pKey->nIv, ARIA_BLOCK_MODE_IV_SIZE );

            return nRet;
        }
    }
    else if( hxeAriaKeySize::eAria256 == _nlength )
    {
        hxsAria256* pKey = reinterpret_cast<hxsAria256*>(_pKey);
        if( nullptr != pKey )
        {
            //---------------------------------------------------------------------------
            // 초기화 
            std::fill( std::begin( pKey->nkey ), std::end( pKey->nkey ), 0 );
            std::fill( std::begin( pKey->nIv ), std::end( pKey->nIv ), 0 );
            pKey->eKeySize = hxeAriaKeySize::eAria256;

            //---------------------------------------------------------------------------
            // Gen 16Byte Random Key    
            this->GeneratorRandomData( pKey->nkey, _nlength );

            //---------------------------------------------------------------------------
            // Gen 16Byte Random Iv
            this->GeneratorRandomData( pKey->nIv, ARIA_BLOCK_MODE_IV_SIZE );

            return nRet;
        }
    }
    return nRet;
}

ErrCode hxcARIA::CheckInitOpValues()
{
    ErrCode nRet = Err_Success;

    return nRet;
}

ErrCode hxcARIA::Encrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    ErrCode nRet = Err_Success;

    //-----------------------------------------------------------------------------------------------
    // 초기화 체크 
    nRet = CheckInitOpValues();
    if( Err_Success != nRet )
    {
        return nRet;
    }

    for( size_t i = 0; i < length; i += 16 )
    {
        if( hxeAriaMode::eAriaCBCMode == m_ctx->eMode )
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
    return nRet;
}

ErrCode hxcARIA::Decrypt( const uint8_t* input, uint8_t* output, size_t length )
{
    ErrCode nRet = Err_Success;

    //-----------------------------------------------------------------------------------------------
    // 초기화 체크 
    nRet = CheckInitOpValues();
    if( Err_Success != nRet )
    {
        return nRet;
    }


    uint8_t temp[16];
    for( size_t i = 0; i < length; i += 16 )
    {
        std::memcpy( temp, input + i, 16 );
        std::memcpy( m_ctx->State, input + i, 16 );
        m_pImpl->ARIA_DecryptBlock( m_ctx->State, m_ctx->RoundKeys.data(), m_ctx->NumRounds );
        if( hxeAriaMode::eAriaCBCMode == m_ctx->eMode )
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
    return nRet;
}

size_t hxcARIA::BlockSize() const 
{
    return 16;
}