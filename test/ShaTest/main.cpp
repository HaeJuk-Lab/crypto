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
 @file		main.cpp
 @brief		SHA TEST PROJECT
 */

#include "hxPch.h"
#include "hxcSHA1.h"
#include "hxcSHA256.h"
#include "hxcSHA384.h"

void print_hash( const uint8_t* hash, size_t length )
{
	for( size_t i = 0; i < length; i++ ) {
		std::cout << std::hex << std::setw( 2 ) << std::setfill( '0' ) << (int)hash[i];
	}
	std::cout << std::dec << std::endl;
}

int main() 
{
	const char* base_string = "Hello, ARIA SHA Test!";

	for( int i = 1; i <= 10; i++ )
	{
		std::string test_string = std::string( base_string, i * strlen( base_string ) );

		// SHA1 Test
		hxcSHA1 SHA1;
		uint8_t sha1_hash[20] = { 0 };
		SHA1.Init();
		SHA1.Update( reinterpret_cast<const uint8_t*>(test_string.c_str()), test_string.size() );
		SHA1.Final( sha1_hash );
		std::cout << "Input: " << test_string.substr( 0, 60 ) << "... (Length: " << test_string.size() << ")" << std::endl;
		std::cout << "SHA1 Hash: ";
		print_hash( sha1_hash, 20 );

		// SHA256 Test
		hxcSHA256 SHA256;
		uint8_t sha256_hash[32] = { 0 };
		SHA256.Init();
		SHA256.Update( reinterpret_cast<const uint8_t*>(test_string.c_str()), test_string.size() );
		SHA256.Final( sha256_hash );
		std::cout << "SHA256 Hash: ";
		print_hash( sha256_hash, 32 );

		// SHA384 Test
		hxcSHA384 SHA384;
		uint8_t sha384_hash[48] = { 0 };
		SHA384.Init();
		SHA384.Update( reinterpret_cast<const uint8_t*>(test_string.c_str()), test_string.size() );
		SHA384.Final( sha384_hash );
		std::cout << "SHA384 Hash: ";
		print_hash( sha384_hash, 48 );

		std::cout << "--------------------------------------------" << std::endl;
	}

	return 0;
}