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
 @file		hxcDrbgHMAC.cpp
 @brief
 */
#include "hxcDrbgHMAC.h"
#include "../sha/hxcSHA256.h"
#include "../noisecollector/hxcNoiseCollector.h"

hxcDrbgHMAC::hxcDrbgHMAC()
    : m_pColletor( std::make_unique<hxcNoiseCollector>() )
    , m_nReseedInterval( 0 )
    , m_nCounter( 0 )
{
    std::fill( std::begin( m_nkey ), std::end( m_nkey ), 0 );
    std::fill( std::begin( m_nIV ), std::end( m_nIV ), 0 );

}

hxcDrbgHMAC::~hxcDrbgHMAC()
{
    std::fill( std::begin( m_nkey ), std::end( m_nkey ), 0 );
    std::fill( std::begin( m_nIV ), std::end( m_nIV ), 0 );
}

void hxcDrbgHMAC::Initialize( const std::vector<uint8_t>& _vSeed )
{
    Hmac( _vSeed, std::vector<uint8_t>( m_nkey, m_nkey + 32 ) );
    m_nCounter = 0;
}

std::vector<uint8_t> hxcDrbgHMAC::Generate( size_t _nSize )
{
    std::vector<uint8_t> randomData( _nSize );

    for( size_t i = 0; i < _nSize; i += 32 )
    {
        Hmac( std::vector<uint8_t>( m_nIV, m_nIV + 16 ), std::vector<uint8_t>( m_nkey, m_nkey + 32 ) );
        std::memcpy( &randomData[i], m_nIV, min( _nSize - i, 32 ) );
    }

    m_nCounter++;
    if( m_nCounter >= m_nReseedInterval )
    {
        ReSeed();
    }

    return randomData;
}

void hxcDrbgHMAC::ReSeed()
{
    std::vector<uint8_t> newSeed = m_pColletor->CollectNoise();
    Initialize( newSeed );
}

void hxcDrbgHMAC::InCrementV()
{
    // DONOT USED
}

void hxcDrbgHMAC::Hmac( const std::vector<uint8_t>& _vData, const std::vector<uint8_t>& _vKey ) 
{
    hxcSHA256 sha256;
    std::vector<uint8_t> innerPad( 64, 0x36 );  // Inner pad
    std::vector<uint8_t> outerPad( 64, 0x5C );  // Outer pad

    std::vector<uint8_t> keyTemp = _vKey;
    if( _vKey.size() > 64 )
    {
        sha256.Init();
        sha256.Update( _vKey.data(), _vKey.size() );
        keyTemp.resize( sha256.HashSize() );
        sha256.Final( keyTemp.data() );
    }
    keyTemp.resize( 64, 0x00 );

    for( size_t i = 0; i < 64; ++i )
    {
        innerPad[i] ^= keyTemp[i];
        outerPad[i] ^= keyTemp[i];
    }

    sha256.Update( innerPad.data(), innerPad.size() );
    sha256.Update( _vData.data(), _vData.size() );
    std::vector<uint8_t> innerHash;

    innerHash.resize( sha256.HashSize() );
    sha256.Final( innerHash.data() );

    sha256.Update( outerPad.data(), outerPad.size() );
    sha256.Update( innerHash.data(), innerHash.size() );

    std::vector<uint8_t> result;
    result.resize( sha256.HashSize() );
    sha256.Final( result.data() );
    std::memcpy( m_nIV, result.data(), 16 );
}