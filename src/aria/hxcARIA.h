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
 @file		hxcARIA.h
 @brief
 */
#ifndef __HXC_ARIA_H__
#define __HXC_ARIA_H__

#include "hxPch.h"
#include "hxcCipher.hpp"
#include "hxcARIAImpl.h"
#include "../export/hxAriaExport.h"

class hxcARIA : public hxcCipher 
{
    DECLARE_NO_COPY_CLASS( hxcARIA );

public:
    hxcARIA();
    virtual ~hxcARIA() = default;
    ErrCode Init( const hxsAria* _pKey );
    ErrCode Generatorkey( INOUT hxsAria* _pKey, size_t _nlength );

    ErrCode CheckInitOpValues() override;
    ErrCode Encrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    ErrCode Decrypt( const uint8_t* input, uint8_t* output, size_t length ) override;
    size_t BlockSize() const override;

private:
    std::unique_ptr<hxsARIA_CTX> m_ctx;    // ARIA 컨텍스트를 unique_ptr로 관리
    std::unique_ptr<hxcARIAImpl> m_pImpl;  // ARIA IMPL

};

#endif //!__HXC_ARIA_H__