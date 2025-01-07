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
#ifndef __HXC_CIPHER_HPP__
#define __HXC_CIPHER_HPP__

class hxcCipher 
{
public:
    hxcCipher() = default; 
    virtual ~hxcCipher() = default;

    // 초기화, 셀프테스트 통과, CPU 지원 여부 확인 
    virtual ErrCode CheckInitOpValues() = 0 ;

    // 암호화 및 복호화
    virtual ErrCode Encrypt( const uint8_t* _pInput, OUT uint8_t* _pOutput, size_t _nlength ) = 0;
    virtual ErrCode Decrypt( const uint8_t* _pInput, OUT uint8_t* _pOutput, size_t _nlength ) = 0;

    // 블록 크기 반환
    virtual size_t BlockSize() const = 0;

    // 랜덤 키 반환
    bool GeneratorRandomData( OUT uint8_t* _pBuffer, size_t _nlength )
    {
        static std::random_device rd;
        static std::mt19937 gen( rd() );
        static std::uniform_int_distribution<> dis( 0, 255 );

        for( size_t i = 0; i < _nlength; i++ )
        {
            _pBuffer[i] = static_cast<uint8_t>(dis( gen ));
        }
        return true;
    }

};

#endif //!__HXC_CIPHER_HPP__