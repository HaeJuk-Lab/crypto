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
 @file		hxcSHA384.h
 @brief
 */
#ifndef __HXC_SHA384_H__
#define __HXC_SHA384_H__

#include "hxPch.h"
#include "hxcSHA.hpp"

class hxcSHA384 : public hxcSHA
{
    DECLARE_NO_COPY_CLASS( hxcSHA384 );

public:
    hxcSHA384();
    virtual ~hxcSHA384() = default;
    void Init() override;
    void Update( const uint8_t* data, size_t len ) override;
    void Final( uint8_t* hash ) override;
    size_t HashSize() const override;

private:
    void Transform( uint64_t state[8], const uint8_t buffer[128] );

private:
    std::unique_ptr<hxsSHA384_CTX> ctx;
};

#endif //! __HXC_SHA256_H__