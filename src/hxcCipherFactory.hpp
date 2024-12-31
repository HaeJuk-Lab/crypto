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
 @file		hxcCipherFactory.cpp
 @brief
 */


class hxcCipherFactory 
{
public:
    static std::unique_ptr<hxcCipher> CreateCipher( const std::string& type ) 
    {
        if( type == "ARIA" ) {
            return std::make_unique<hxcARIA>();
        }
        else if( type == "AES" ) {
            return std::make_unique<hxcAES>();
        }
        else if( type == "SEED" ) {
            return std::make_unique<hxcSEED>();
        }
        throw std::invalid_argument( "Unsupported cipher type" );
    }
};