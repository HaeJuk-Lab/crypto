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
 @file		hxcSHA256.cpp
 @brief
 */

#include "hxcSHA256.h"

hxcSHA256::hxcSHA256()
    : ctx( std::make_unique<hxsSHA256_CTX>() ) 
{

}

void hxcSHA256::Init() 
{
    ctx->Reset();
}

void hxcSHA256::Update( const uint8_t* data, size_t len ) 
{
    size_t i, index, partLen;

    index = (ctx->count / 8) % 64;
    ctx->count += len * 8;
    partLen = 64 - index;

    if( len >= partLen )
    {
        memcpy( &ctx->buffer[index], data, partLen );
        Transform( ctx->state, ctx->buffer );

        for( i = partLen; i + 63 < len; i += 64 ) 
        {
            Transform( ctx->state, &data[i] );
        }
        index = 0;
    }
    else {
        i = 0;
    }

    memcpy( &ctx->buffer[index], &data[i], len - i );
}

void hxcSHA256::Final( uint8_t* hash )
{
    uint8_t finalCount[8];
    uint32_t i;

    for( i = 0; i < 8; i++ ) 
    {
        finalCount[i] = (ctx->count >> ((7 - i) * 8)) & 0xFF;
    }

   Update( (const uint8_t*)"\x80", 1 );

    while( (ctx->count / 8) % 64 != 56 ) 
    {
        Update( (const uint8_t*)"\0", 1 );
    }

    Update( finalCount, 8 );

    for( i = 0; i < 8; i++ )
    {
        hash[i * 4] = (ctx->state[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (ctx->state[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (ctx->state[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = ctx->state[i] & 0xFF;
    }
}

size_t hxcSHA256::HashSize() const 
{
    return 32;
}

void hxcSHA256::Transform( uint32_t state[8], const uint8_t buffer[64] ) 
{
    uint32_t W[64];
    uint32_t a, b, c, d, e, f, g, h, t1, t2;
    static const uint32_t K[64] = 
    {
        0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
        0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
        0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
        0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
        0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
        0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
        0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
        0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
    };

    for( int i = 0; i < 16; i++ )
    {
        W[i] = (buffer[i * 4] << 24) | (buffer[i * 4 + 1] << 16) | (buffer[i * 4 + 2] << 8) | buffer[i * 4 + 3];
    }

    for( int i = 16; i < 64; i++ ) 
    {
        W[i] = W[i - 16] + (W[i - 15] >> 7 | W[i - 15] << (32 - 7));
    }

    a = state[0]; b = state[1]; c = state[2]; d = state[3];
    e = state[4]; f = state[5]; g = state[6]; h = state[7];

    for( int i = 0; i < 64; i++ )
    {
        t1 = h + (e >> 6 | e << (32 - 6)) + ((e & f) ^ (~e & g)) + K[i] + W[i];
        t2 = (a >> 2 | a << (32 - 2)) + ((a & b) ^ (a & c) ^ (b & c));
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}
