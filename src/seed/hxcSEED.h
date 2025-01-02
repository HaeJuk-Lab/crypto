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
 @file		hxcSEED.h
 @brief
 */
#ifndef __HXC_SEED_H__
#define __HXC_SEED_H__

#include "hxPch.h"
#include "hxcCipher.hpp"
#include "hxcSEEDImpl.h"

class hxcSEED : public hxcCipher 
{
    DECLARE_NO_COPY_CLASS( hxcSEED );

public:
    hxcSEED();
    virtual ~hxcSEED() = default; 

    void Init( const uint8_t* key, size_t key_len, const uint8_t* iv = nullptr, bool use_cbc = false ) override;
    void Encrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    void Decrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    size_t BlockSize() const override;

private:
    std::unique_ptr<hxsSEED_CTX> m_ctx;  // SEED 컨텍스트를 unique_ptr로 관리
    std::unique_ptr<hxcSEEDImpl> m_pImpl;
};

#endif // !__HXC_SEED_H__
