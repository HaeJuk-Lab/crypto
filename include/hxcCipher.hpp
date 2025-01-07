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

    // �ʱ�ȭ, �����׽�Ʈ ���, CPU ���� ���� Ȯ�� 
    virtual ErrCode CheckInitOpValues() = 0 ;

    // ��ȣȭ �� ��ȣȭ
    virtual ErrCode Encrypt( const uint8_t* _pInput, OUT uint8_t* _pOutput, size_t _nlength ) = 0;
    virtual ErrCode Decrypt( const uint8_t* _pInput, OUT uint8_t* _pOutput, size_t _nlength ) = 0;

    // ��� ũ�� ��ȯ
    virtual size_t BlockSize() const = 0;

    // ���� Ű ��ȯ
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