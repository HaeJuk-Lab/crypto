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
 @file		hxcSHA384.cpp
 @brief
 */
#include "hxcSHA384.h"

hxcSHA384::hxcSHA384()
    : ctx( std::make_unique<hxsSHA384_CTX>() ) 
{

}

void hxcSHA384::Init() 
{
    ctx->Reset();
}

void hxcSHA384::Update( const uint8_t* data, size_t len ) 
{
    size_t i, index, partLen;

    index = (ctx->count / 8) % 128;
    ctx->count += len * 8;
    partLen = 128 - index;

    if( len >= partLen ) {
        memcpy( &ctx->buffer[index], data, partLen );
        SHA384_Transform( ctx->state, ctx->buffer );

        for( i = partLen; i + 127 < len; i += 128 ) {
            SHA384_Transform( ctx->state, &data[i] );
        }
        index = 0;
    }
    else {
        i = 0;
    }

    memcpy( &ctx->buffer[index], &data[i], len - i );
}

void hxcSHA384::Final( uint8_t* hash ) 
{
    uint8_t finalCount[16];
    uint32_t i;

    for( i = 0; i < 16; i++ ) {
        finalCount[i] = (ctx->count >> ((15 - i) * 8)) & 0xFF;
    }

    SHA384_Update( ctx, (const uint8_t*)"\x80", 1 );

    while( (ctx->count / 8) % 128 != 112 ) {
        SHA384_Update( ctx, (const uint8_t*)"\0", 1 );
    }

    SHA384_Update( ctx, finalCount, 16 );

    for( i = 0; i < 6; i++ ) {
        hash[i * 8] = (ctx->state[i] >> 56) & 0xFF;
        hash[i * 8 + 1] = (ctx->state[i] >> 48) & 0xFF;
        hash[i * 8 + 2] = (ctx->state[i] >> 40) & 0xFF;
        hash[i * 8 + 3] = (ctx->state[i] >> 32) & 0xFF;
        hash[i * 8 + 4] = (ctx->state[i] >> 24) & 0xFF;
        hash[i * 8 + 5] = (ctx->state[i] >> 16) & 0xFF;
        hash[i * 8 + 6] = (ctx->state[i] >> 8) & 0xFF;
        hash[i * 8 + 7] = ctx->state[i] & 0xFF;
    }
}

size_t hxcSHA384::HashSize() const 
{
    return 48;
}
void hxcSHA384::Transform( uint64_t state[8], const uint8_t buffer[128] ) 
{
    uint64_t W[80];
    uint64_t a, b, c, d, e, f, g, h, t1, t2;
    static const uint64_t K[80] = {
        0x428A2F98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F, 0xE9B5DBA58189DBBC,
        0x3956C25BF348B538, 0x59F111F1B605D019, 0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118,
        // ... (remaining constants)
    };

    for( int i = 0; i < 16; i++ ) {
        W[i] = ((uint64_t)buffer[i * 8] << 56) | ((uint64_t)buffer[i * 8 + 1] << 48) |
            ((uint64_t)buffer[i * 8 + 2] << 40) | ((uint64_t)buffer[i * 8 + 3] << 32) |
            ((uint64_t)buffer[i * 8 + 4] << 24) | ((uint64_t)buffer[i * 8 + 5] << 16) |
            ((uint64_t)buffer[i * 8 + 6] << 8) | (uint64_t)buffer[i * 8 + 7];
    }

    for( int i = 16; i < 80; i++ ) {
        W[i] = W[i - 16] + (W[i - 15] >> 1 | W[i - 15] << (64 - 1));
    }

    a = state[0]; b = state[1]; c = state[2]; d = state[3];
    e = state[4]; f = state[5]; g = state[6]; h = state[7];

    for( int i = 0; i < 80; i++ ) {
        t1 = h + (e >> 14 | e << (64 - 14)) + ((e & f) ^ (~e & g)) + K[i] + W[i];
        t2 = (a >> 28 | a << (64 - 28)) + ((a & b) ^ (a & c) ^ (b & c));
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}
