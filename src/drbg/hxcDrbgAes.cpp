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
 @file		hxcDrbgAes.cpp
 @brief
 */
#include "hxcDrbgAes.h"
#include "../exrpot/hxAesExrpot.h"
#include "../aes/hxcAES.h"
#include "../noisecollector/hxcNoiseCollector.h"

hxcDrbgAes::hxcDrbgAes()
    : m_pImpl( std::make_unique<hxcAES>() )
    , m_pColletor( std::make_unique<hxcNoiseCollector>() )
    , m_nReseedInterval(0)
    , m_nCounter(0)
{
    std::fill( std::begin( m_nkey ), std::end( m_nkey ), 0 );
    std::fill( std::begin( m_nIV ), std::end( m_nIV ), 0 );
}

hxcDrbgAes::~hxcDrbgAes()
{
    std::fill( std::begin( m_nkey ), std::end( m_nkey ), 0 );
    std::fill( std::begin( m_nIV ), std::end( m_nIV ), 0 );
}

void hxcDrbgAes::Initialize( const std::vector<uint8_t>& _vSeed )
{
    memcpy( m_nkey, _vSeed.data(), 32 );       // AES-256
    memcpy( m_nIV, _vSeed.data() + 32, 16 );    // 초기 벡터 (IV)
    
    ErrCode nRet = m_pImpl->Init( m_nkey, 32 );            // AES 키 설정 (기존 AES 코드 재활용)
    if( Err_Success != nRet )
    {
        // TODO : LOG 
    }
    m_nCounter = 0;
}

std::vector<uint8_t> hxcDrbgAes::Generate( size_t _nSize )
{
    std::vector<uint8_t> randomData( _nSize );

    for( size_t i = 0; i < _nSize; i += 16 )
    {
        m_pImpl->Encrypt( m_nIV, m_nIV, 16 );  // CTR 모드: V를 암호화해 난수 생성
        memcpy( &randomData[i], m_nIV, min( _nSize - i, 16 ) );
        InCrementV();
    }

    m_nCounter++;
    if( m_nCounter >= m_nReseedInterval ) 
    {
        ReSeed();
    }

    return randomData;
}

void hxcDrbgAes::ReSeed()
{
    std::vector<uint8_t> newSeed = m_pColletor->CollectNoise();

    Initialize( newSeed );
}

void hxcDrbgAes::InCrementV()
{
    for( int i = 15; i >= 0; --i )
    {
        if( ++m_nIV[i] ) 
            break;
    }
}
