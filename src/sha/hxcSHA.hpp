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
 @file		hxcSHA.hpp
 @brief
 */

#ifndef __HXC_SHA_HPP__
#define __HXC_SHA_HPP__

 // SHA1 컨텍스트 구조체
struct hxsSHA1_CTX 
{
    uint32_t state[5];     // 상태 변수 (160비트)
    uint64_t count;        // 처리된 비트 수
    uint8_t buffer[64];    // 데이터 버퍼 (512비트)

    hxsSHA1_CTX() 
    {
        Reset();
    }

    // 컨텍스트 초기화
    void Reset() 
    {
        state[0] = 0x67452301;
        state[1] = 0xEFCDAB89;
        state[2] = 0x98BADCFE;
        state[3] = 0x10325476;
        state[4] = 0xC3D2E1F0;
        count = 0;
        std::memset( buffer, 0, sizeof( buffer ) );
    }
};

struct hxsSHA256_CTX 
{
    uint32_t state[8];     // 상태 변수 (256비트)
    uint64_t count;        // 처리된 비트 수
    uint8_t buffer[64];    // 데이터 버퍼 (512비트)

    hxsSHA256_CTX() 
    {
        Reset();
    }

    void Reset() 
    {
        state[0] = 0x6A09E667;
        state[1] = 0xBB67AE85;
        state[2] = 0x3C6EF372;
        state[3] = 0xA54FF53A;
        state[4] = 0x510E527F;
        state[5] = 0x9B05688C;
        state[6] = 0x1F83D9AB;
        state[7] = 0x5BE0CD19;
        count = 0;
        std::memset( buffer, 0, sizeof( buffer ) );
    }
};


// SHA384 컨텍스트 구조체
struct hxsSHA384_CTX 
{
    uint64_t state[8];     // 상태 변수 (384비트)
    uint64_t count;        // 처리된 비트 수
    uint8_t buffer[128];   // 데이터 버퍼 (1024비트)

    hxsSHA384_CTX() 
    {
        Reset();
    }

    void Reset()
    {
        state[0] = 0xCBBB9D5DC1059ED8;
        state[1] = 0x629A292A367CD507;
        state[2] = 0x9159015A3070DD17;
        state[3] = 0x152FECD8F70E5939;
        state[4] = 0x67332667FFC00B31;
        state[5] = 0x8EB44A8768581511;
        state[6] = 0xDB0C2E0D64F98FA7;
        state[7] = 0x47B5481DBEFA4FA4;
        count = 0;
        std::memset( buffer, 0, sizeof( buffer ) );
    }
};


class hxcSHA
{
    DECLARE_NO_COPY_CLASS( hxcSHA );

public:
    hxcSHA() = default ;
    virtual ~hxcSHA() = default;
    virtual void Init() = 0;
    virtual void Update( const uint8_t* data, size_t len ) = 0;
    virtual void Final( uint8_t* hash ) = 0;
    virtual size_t HashSize() const = 0;
};


#endif // !__HXC_SHA_HPP__
