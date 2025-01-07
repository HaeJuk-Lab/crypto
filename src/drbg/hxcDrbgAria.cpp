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
 @file		hxcDrbgAria.cpp
 @brief
 */
#include "hxcDrbgAria.h"
#include "../aria/hxcARIA.h"
#include "../noisecollector/hxcNoiseCollector.h"

hxcDrbgAria::hxcDrbgAria()
    : m_pImpl( std::make_unique<hxcARIA>() )
    , m_pColletor( std::make_unique<hxcNoiseCollector>() )
    , m_nReseedInterval( 0 )
    , m_nCounter( 0 )
{
    std::fill( std::begin( m_stKey.nkey ), std::end( m_stKey.nkey ), 0 );
    std::fill( std::begin( m_stKey.nIv ), std::end( m_stKey.nIv ), 0 );
}

hxcDrbgAria::~hxcDrbgAria()
{
    std::fill( std::begin( m_stKey.nkey ), std::end( m_stKey.nkey ), 0 );
    std::fill( std::begin( m_stKey.nIv ), std::end( m_stKey.nIv ), 0 );
}

void hxcDrbgAria::Initialize( const std::vector<uint8_t>& _vSeed )
{
    memcpy( m_stKey.nkey, _vSeed.data(), 32 );  // ARIA-256
    memcpy( m_stKey.nIv, _vSeed.data() + 32, 16 );
    
    m_stKey.eKeySize = hxeAriaKeySize::eAria256;
    
    m_pImpl->Init( &m_stKey );  // ARIA 키 설정

    m_nCounter = 0;
}

std::vector<uint8_t> hxcDrbgAria::Generate( size_t _nSize )
{
    std::vector<uint8_t> randomData( _nSize );
    for( size_t i = 0; i < _nSize; i += 16 )
    {
        m_pImpl->Encrypt( m_stKey.nIv, m_stKey.nIv, 16 );  // V를 암호화
        memcpy( &randomData[i], m_stKey.nIv, min( _nSize - i, 16 ) );
        InCrementV();
    }

    m_nCounter++;
    if( m_nCounter >= m_nReseedInterval )
    {
        ReSeed();
    }

    return randomData;
}

void hxcDrbgAria::ReSeed()
{
    std::vector<uint8_t> newSeed = m_pColletor->CollectNoise();
    Initialize( newSeed );
}

void hxcDrbgAria::InCrementV()
{
    for( int i = 15; i >= 0; --i ) {
        if( ++m_stKey.nIv[i] ) break;
    }
}
