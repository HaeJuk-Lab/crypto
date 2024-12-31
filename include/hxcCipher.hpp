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

    // �ʱ�ȭ
    virtual void Init( const uint8_t* key, size_t key_len, const uint8_t* iv = nullptr, bool use_cbc = false ) = 0;

    // ��ȣȭ �� ��ȣȭ
    virtual void Encrypt( const uint8_t* input, uint8_t* output, size_t length ) = 0;
    virtual void Decrypt( const uint8_t* input, uint8_t* output, size_t length ) = 0;

    // ��� ũ�� ��ȯ
    virtual size_t BlockSize() const = 0;
};