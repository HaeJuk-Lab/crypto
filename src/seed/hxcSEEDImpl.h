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
 @file		hxcSEEDImpl.h
 @brief
 */
#ifndef __HXC_SEED_IMPL_H__
#define __HXC_SEED_IMPL_H__

#include "hxPch.h"


 // Constant parameters for SEED
constexpr uint32_t KC[16] = 
{
    0x9e3779b9, 0x3c6ef373, 0x78dde6e6, 0xf1bbcdc, 0xe3779b99, 0xc6ef3723, 0x8dde6e67, 0x1bbcdcaf,
    0x3779b9df, 0x6ef3723b, 0xdde6e677, 0xbbcdcafe, 0x779b9df3, 0xef3723d7, 0xde6e677b, 0xbcdcafe7
};

// SEED context structure
struct hxsSEED_CTX
{
    std::array<uint32_t, 32> roundKeys;  // SEED uses 32 round keys
    bool isKeySet = false;               // To check if the key has been initialized
    bool cbc_mode = false;               // Flag for CBC mode
    uint8_t iv[16] = { 0 };                // Initialization vector

    hxsSEED_CTX() = default;
    void reset() { isKeySet = false; roundKeys.fill( 0 ); cbc_mode = false; memset( iv, 0, 16 ); }
};

class hxcSEEDImpl
{
    DECLARE_NO_COPY_CLASS( hxcSEEDImpl );

public:
    hxcSEEDImpl() = default;
    virtual ~hxcSEEDImpl() = default; 
    void SEED_Init( hxsSEED_CTX* _pCtx, const uint8_t* _pKey, size_t _nkeylen )
    {
        if( _nkeylen != 16 )
        {
            throw std::invalid_argument( "SEED key length must be 16 bytes." );
        }

        uint32_t K0 = (_pKey[0] << 24) | (_pKey[1] << 16) | (_pKey[2] << 8) | _pKey[3];
        uint32_t K1 = (_pKey[4] << 24) | (_pKey[5] << 16) | (_pKey[6] << 8) | _pKey[7];
        uint32_t K2 = (_pKey[8] << 24) | (_pKey[9] << 16) | (_pKey[10] << 8) | _pKey[11];
        uint32_t K3 = (_pKey[12] << 24) | (_pKey[13] << 16) | (_pKey[14] << 8) | _pKey[15];

        for( int i = 0; i < 16; i++ ) 
        {
            _pCtx->roundKeys[2 * i] = K0 + KC[i];
            _pCtx->roundKeys[2 * i + 1] = K1 - KC[i];
            uint32_t T = K0;
            K0 = (K1 + K2) % 0xFFFFFFFF;
            K1 = K2;
            K2 = K3;
            K3 = T;
        }
        _pCtx->isKeySet = true;
    }

    void SEED_Encrypt( hxsSEED_CTX* _pCtx, const uint8_t* _pInput, uint8_t* _pOutput, size_t _nLength )
    {
        if( !_pCtx->isKeySet )
        {
            throw std::runtime_error( "SEED key is not set." );
        }

        for( size_t i = 0; i < _nLength; i += 16 )
        {
            for( int j = 0; j < 16; j++ ) 
            {
                _pOutput[i + j] = _pInput[i + j] ^ _pCtx->iv[j];  // Simple XOR (for demonstration)
            }
            memcpy( _pCtx->iv, _pOutput + i, 16 );
        }
    }

    void SEED_Decrypt( hxsSEED_CTX* _pCtx, const uint8_t* _pInput, uint8_t* _pOutput, size_t _nLength )
    {
        if( !_pCtx->isKeySet )
        {
            throw std::runtime_error( "SEED key is not set." );
        }

        for( size_t i = 0; i < _nLength; i += 16 )
        {
            uint8_t temp[16];
            memcpy( temp, _pInput + i, 16 );
            for( int j = 0; j < 16; j++ )
            {
                _pOutput[i + j] = _pInput[i + j] ^ _pCtx->iv[j];  // Simple XOR (for demonstration)
            }
            memcpy( _pCtx->iv, temp, 16 );
        }
    }

};


#endif //!__HXC_SEED_IMPL_H__