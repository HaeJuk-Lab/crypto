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
 @file		hxcCipher.hpp
 @brief
 */

class hxcCipher 
{
public:
    virtual ~hxcCipher() = default;

    // 초기화
    virtual void Init( const uint8_t* key, size_t key_len, const uint8_t* iv = nullptr, bool use_cbc = false ) = 0;

    // 암호화 및 복호화
    virtual void Encrypt( const uint8_t* input, uint8_t* output, size_t length ) = 0;
    virtual void Decrypt( const uint8_t* input, uint8_t* output, size_t length ) = 0;

    // 블록 크기 반환
    virtual size_t BlockSize() const = 0;
};