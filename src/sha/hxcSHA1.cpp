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
 @file		hxcSHA1.cpp
 @brief
 */

#include "hxcSHA1.h"


hxcSHA1::hxcSHA1() 
    : ctx( std::make_unique<hxsSHA1_CTX>() ) 
{

}

void hxcSHA1::Init() 
{
    ctx->Reset();
}

void hxcSHA1::Update( const uint8_t* data, size_t len ) 
{
    size_t i, index, partLen;

    index = (ctx->count / 8) % 64;
    ctx->count += len * 8;
    partLen = 64 - index;

    // 데이터 처리
    if( len >= partLen ) 
    {
        std::memcpy( &ctx->buffer[index], data, partLen );
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

    std::memcpy( &ctx->buffer[index], &data[i], len - i );
}

void hxcSHA1::Final( uint8_t* hash ) 
{
    uint8_t finalCount[8];
    uint32_t i;

    for( i = 0; i < 8; i++ ) 
    {
        finalCount[i] = static_cast<uint8_t>((ctx->count >> ((7 - i) * 8)) & 0xFF);
    }

    Update( reinterpret_cast<const uint8_t*>("\x80"), 1 );

    while( (ctx->count / 8) % 64 != 56 )
    {
        Update( reinterpret_cast<const uint8_t*>("\0"), 1 );
    }

    Update( finalCount, 8 );

    for( i = 0; i < 5; i++ ) 
    {
        hash[i * 4] = (ctx->state[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (ctx->state[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (ctx->state[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = ctx->state[i] & 0xFF;
    }
}

size_t hxcSHA1::HashSize() const 
{
    return 20;
}

// SHA1 내부 라운드 함수
void hxcSHA1::Transform( uint32_t state[5], const uint8_t buffer[64] ) 
{
    uint32_t a, b, c, d, e, t, W[80];

    for( int i = 0; i < 16; i++ ) 
    {
        W[i] = (buffer[i * 4] << 24) |
            (buffer[i * 4 + 1] << 16) |
            (buffer[i * 4 + 2] << 8) |
            (buffer[i * 4 + 3]);
    }

    for( int i = 16; i < 80; i++ ) 
    {
        W[i] = W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16];
        W[i] = (W[i] << 1) | (W[i] >> 31);  // 좌측 순환
    }

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];

    // 메인 라운드
    for( int i = 0; i < 80; i++ ) 
    {
        if( i < 20 ) 
        {
            t = ((b & c) | ((~b) & d)) + 0x5A827999;
        }
        else if( i < 40 ) 
        {
            t = (b ^ c ^ d) + 0x6ED9EBA1;
        }
        else if( i < 60 ) 
        {
            t = ((b & c) | (b & d) | (c & d)) + 0x8F1BBCDC;
        }
        else
        {
            t = (b ^ c ^ d) + 0xCA62C1D6;
        }

        t += (a << 5) | (a >> 27);
        t += e + W[i];
        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = t;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}
