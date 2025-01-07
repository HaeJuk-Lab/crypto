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
 @file		hxcARIAImpl.h
 @brief
 */
#ifndef __HXC_ARIA_IMPL_H__
#define __HXC_ARIA_IMPL_H__
#include "hxPch.h"
#include "../export/hxAriaExport.h"

static const uint8_t sbox[256] =
{
    // ARIA S-box (예시)
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// ARIA Inverse S-box (continuation)
static const uint8_t inv_sbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};


struct hxsARIA_CTX 
{
    uint8_t State[4][4];                  // 상태 배열 (128비트 블록)
    std::array<uint32_t, 16 * 15> RoundKeys;  // 최대 15 라운드 * 4(32비트 키)
    uint8_t IV[ARIA_BLOCK_MODE_IV_SIZE];       // 초기화 벡터 (CBC 모드용)
    uint8_t NumRounds;                    // 라운드 수 (12, 14, 16)
    hxeAriaMode eMode;                    // CBC 모드 플래그

    hxsARIA_CTX() 
    {
        std::memset( State, 0, sizeof( State ) );
        std::memset( IV, 0, sizeof( IV ) );
        NumRounds = 0;
        eMode = hxeAriaMode::eAriaCBCMode;
    }

    void Init( const uint8_t* key, size_t key_len, const uint8_t* iv ) 
    {
        if( key_len == hxeAriaKeySize::eAria128 )
            NumRounds = hxeAriaRoundKey::eAria128RoundNum;  // 128비트 키
        else if( key_len == hxeAriaKeySize::eAria192 )
            NumRounds = hxeAriaRoundKey::eAria192RoundNum;  // 192비트 키
        else if( key_len == hxeAriaKeySize::eAria256 )
            NumRounds = hxeAriaRoundKey::eAria256RoundNum;  // 256비트 키
        else throw std::runtime_error( "Invalid key length" );

        KeyExpansion( key, key_len );
        if( iv ) 
        {
            std::memcpy( IV, iv, ARIA_BLOCK_MODE_IV_SIZE );
        }
    }

    void KeyExpansion( const uint8_t* key, size_t key_len ) 
    {

        static const uint32_t C[3] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC };

        size_t Nk = key_len / 4;  // Nk: 키 길이 (32비트 단위)
        size_t Nr = NumRounds;    // 라운드 수 (12, 14, 16)

        for( size_t i = 0; i < Nk; i++ ) 
        {
            RoundKeys[i] = (key[4 * i] << 24) | (key[4 * i + 1] << 16) |
                (key[4 * i + 2] << 8) | key[4 * i + 3];
        }

        for( size_t i = Nk; i < 4 * (Nr + 1); i++ ) 
        {
            uint32_t temp = RoundKeys[i - 1];
            if( i % Nk == 0 )
            {
                temp = (temp << 8) | (temp >> 24);  // Rotate left by 8 bits
                temp ^= C[i / Nk - 1];
            }
            RoundKeys[i] = RoundKeys[i - Nk] ^ temp;
        }
    }
};




class hxcARIAImpl
{
	DECLARE_NO_COPY_CLASS( hxcARIAImpl );

public:
    hxcARIAImpl() = default;
	virtual ~hxcARIAImpl() = default;

    void SubBytes( uint8_t state[4][4] ) 
    {

        for( int i = 0; i < 4; i++ ) 
        {
            for( int j = 0; j < 4; j++ )
            {
                state[i][j] = sbox[state[i][j]];
            }
        }
    }

    void MixColumns( uint8_t state[4][4] ) 
    {
        for( int i = 0; i < 4; i++ ) 
        {
            uint8_t t = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
            uint8_t u = state[0][i];
            state[0][i] ^= t ^ u;
            state[1][i] ^= t ^ state[1][i];
            state[2][i] ^= t ^ state[2][i];
            state[3][i] ^= t ^ state[3][i];
        }
    }

    void InvSubBytes( uint8_t state[4][4] ) 
    {

        for( int i = 0; i < 4; i++ ) 
        {
            for( int j = 0; j < 4; j++ ) 
            {
                state[i][j] = inv_sbox[state[i][j]];
            }
        }
    }
    void AddRoundKey( uint8_t state[4][4], const uint32_t* RoundKey ) 
    {
        for( int i = 0; i < 4; i++ ) 
        {
            for( int j = 0; j < 4; j++ ) 
            {
                state[j][i] ^= (RoundKey[i] >> (24 - j * 8)) & 0xFF;
            }
        }
    }

    void ShiftRows( uint8_t state[4][4] ) 
    {
        uint8_t temp;
        temp = state[1][0];
        state[1][0] = state[1][1];
        state[1][1] = state[1][2];
        state[1][2] = state[1][3];
        state[1][3] = temp;

        temp = state[2][0];
        state[2][0] = state[2][2];
        state[2][2] = temp;
        temp = state[2][1];
        state[2][1] = state[2][3];
        state[2][3] = temp;

        temp = state[3][3];
        state[3][3] = state[3][2];
        state[3][2] = state[3][1];
        state[3][1] = state[3][0];
        state[3][0] = temp;
    }

    void InvShiftRows( uint8_t state[4][4] ) 
    {
        uint8_t temp;
        temp = state[1][3];
        state[1][3] = state[1][2];
        state[1][2] = state[1][1];
        state[1][1] = state[1][0];
        state[1][0] = temp;

        temp = state[2][0];
        state[2][0] = state[2][2];
        state[2][2] = temp;
        temp = state[2][1];
        state[2][1] = state[2][3];
        state[2][3] = temp;
    }

    void InvMixColumns( uint8_t state[4][4] ) 
    {
        for( int i = 0; i < 4; i++ ) 
        {
            uint8_t t = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
            uint8_t u = state[0][i];
            state[0][i] ^= t ^ u;
            state[1][i] ^= t ^ state[1][i];
            state[2][i] ^= t ^ state[2][i];
            state[3][i] ^= t ^ state[3][i];
        }
    }


    void ARIA_EncryptBlock( uint8_t state[4][4], const uint32_t* RoundKeys, uint8_t num_rounds ) 
    {
        AddRoundKey( state, RoundKeys );
        for( int round = 1; round < num_rounds; round++ ) 
        {
            SubBytes( state );
            ShiftRows( state );
            MixColumns( state );
            AddRoundKey( state, RoundKeys + round * 4 );
        }
        SubBytes( state );
        ShiftRows( state );
        AddRoundKey( state, RoundKeys + num_rounds * 4 );
    }

    void ARIA_DecryptBlock( uint8_t state[4][4], const uint32_t* RoundKeys, uint8_t num_rounds ) 
    {
        AddRoundKey( state, RoundKeys + num_rounds * 4 );
        for( int round = num_rounds - 1; round > 0; round-- )
        {
            InvShiftRows( state );
            InvSubBytes( state );
            AddRoundKey( state, RoundKeys + round * 4 );
            InvMixColumns( state );
        }
        InvShiftRows( state );
        InvSubBytes( state );
        AddRoundKey( state, RoundKeys );
    }

};


#endif //! __HXC_ARIA_IMPL_H__
