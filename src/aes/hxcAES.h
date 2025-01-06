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
 @file		hxcAES.h
 @brief
 */
#ifndef __HXC_AES_H__
#define __HXC_AES_H__

#include "hxPch.h"
#include "hxcCipher.hpp"
#include "hxcAESImpl.h"

class hxcAES : public hxcCipher 
{
    DECLARE_NO_COPY_CLASS( hxcAES );

public:
    hxcAES();
    virtual ~hxcAES() = default; 

    ErrCode Init( const uint8_t* key, size_t key_len, const uint8_t* iv = nullptr, bool use_cbc = false );

    ErrCode Generatorkey( INOUT uint8_t* _pBuffer, size_t _nkeylen );
    ErrCode CheckInitOpValues() override;

    ErrCode Encrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    ErrCode Decrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    size_t BlockSize() const override;;

private:
    std::unique_ptr<hxsAES_CTX> m_ctx;  // AES 컨텍스트를 unique_ptr로 관리
    std::unique_ptr<hxcAESImpl> m_pImpl;
};


#endif // !__HXC_AES_H__

