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
        Transform( ctx->state, ctx->buffer );

        for( i = partLen; i + 127 < len; i += 128 ) {
            Transform( ctx->state, &data[i] );
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

    for( i = 0; i < 16; i++ )
    {
        finalCount[i] = (ctx->count >> ((15 - i) * 8)) & 0xFF;
    }

    Update( (const uint8_t*)"\x80", 1 );

    while( (ctx->count / 8) % 128 != 112 ) 
    {
        Update( (const uint8_t*)"\0", 1 );
    }

    Update( finalCount, 16 );

    for( i = 0; i < 6; i++ )
    {
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
        0xD807AA98A3030242, 0x12835B0145706FBE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
        0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235, 0xC19BF174CF692694,
        0xE49B69C19EF14AD2, 0xEFBE4786384F25E3, 0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65,
        0x2DE92C6F592B0275, 0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5,
        0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F, 0xBF597FC7BEEF0EE4,
        0xC6E00BF33DA88FC2, 0xD5A79147930AA725, 0x06CA6351E003826F, 0x142929670A0E6E70,
        0x27B70A8546D22FFC, 0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
        0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6, 0x92722C851482353B,
        0xA2BFE8A14CF10364, 0xA81A664BBC423001, 0xC24B8B70D0F89791, 0xC76C51A30654BE30,
        0xD192E819D6EF5218, 0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8,
        0x19A4C116B8D2D0C8, 0x1E376C085141AB53, 0x2748774CDF8EEB99, 0x34B0BCB5E19B48A8,
        0x391C0CB3C5C95A63, 0x4ED8AA4AE3418ACB, 0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3,
        0x748F82EE5DEFB2FC, 0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
        0x90BEFFFA23631E28, 0xA4506CEBDE82BDE9, 0xBEF9A3F7B2C67915, 0xC67178F2E372532B,
        0xCA273ECEEA26619C, 0xD186B8C721C0C207, 0xEADA7DD6CDE0EB1E, 0xF57D4F7FEE6ED178,
        0x06F067AA72176FBA, 0x0A637DC5A2C898A6, 0x113F9804BEF90DAE, 0x1B710B35131C471B,
        0x28DB77F523047D84, 0x32CAAB7B40C72493, 0x3C9EBE0A15C9BEBC, 0x431D67C49C100D4C,
        0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A, 0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817
    };

    for( int i = 0; i < 16; i++ )
    {
        W[i] = ((uint64_t)buffer[i * 8] << 56) | ((uint64_t)buffer[i * 8 + 1] << 48) |
            ((uint64_t)buffer[i * 8 + 2] << 40) | ((uint64_t)buffer[i * 8 + 3] << 32) |
            ((uint64_t)buffer[i * 8 + 4] << 24) | ((uint64_t)buffer[i * 8 + 5] << 16) |
            ((uint64_t)buffer[i * 8 + 6] << 8) | (uint64_t)buffer[i * 8 + 7];
    }

    for( int i = 16; i < 80; i++ )
    {
        W[i] = W[i - 16] + (W[i - 15] >> 1 | W[i - 15] << (64 - 1));
    }

    a = state[0]; b = state[1]; c = state[2]; d = state[3];
    e = state[4]; f = state[5]; g = state[6]; h = state[7];

    for( int i = 0; i < 80; i++ ) 
    {
        t1 = h + (e >> 14 | e << (64 - 14)) + ((e & f) ^ (~e & g)) + K[i] + W[i];
        t2 = (a >> 28 | a << (64 - 28)) + ((a & b) ^ (a & c) ^ (b & c));
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}
