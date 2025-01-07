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
 @file		hxcARIA_AVX.h
 @brief
 */
#ifndef __HXC_ARIA_AVX_H__
#define __HXC_ARIA_AVX_H__

#include "hxPch.h"
#include "hxcCipher.hpp"
#include "../export/hxAriaExport.h"

class hxcARIA_AVX : public hxcCipher
{
	DECLARE_NO_COPY_CLASS( hxcARIA_AVX );

public:
	hxcARIA_AVX();
	virtual ~hxcARIA_AVX();
  
    ErrCode Init( const hxsAria* _pKey );
    ErrCode Generatorkey( INOUT hxsAria* _pKey);
    ErrCode CheckInitOpValues() override;

    ErrCode Encrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    ErrCode Decrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    
    size_t BlockSize() const override;


private:
    ErrCode EncryptBlock( uint8_t* block );
    ErrCode DecryptBlock( uint8_t* block );

    void SubBytes_AVX( uint8_t* block );
    void MixColumns_AVX( uint8_t* block );
    void ShiftRows_AVX( uint8_t* block );
    void AddRoundKey_AVX( uint8_t* block, const uint8_t* roundKey );

    bool IsSupportAVX();
    bool GetSupportAVX();

private:
    int     m_nNumRounds;
    uint8_t m_nRoundKeys[16 * 15];  // 최대 16라운드 * 4워드
    uint8_t m_nIV[16];
    hxeAriaMode m_eMode;
    bool    m_IsSupport;
};


#endif //!__HXC_ARIA_AVX_H__ 