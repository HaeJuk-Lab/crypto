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
 @file		hxcBigInteger.h
 @brief
 */

#ifndef __HXC_BIG_INTEGER_H__
#define __HXC_BIG_INTEGER_H__

#include "include/hxPch.h"

class hxcBigInteger
{
	DECLARE_NO_COPY_CLASS( hxcBigInteger );

private:
	// Helper function to remove leading zeros
	void Trim();
public:
	// Default constructor
	hxcBigInteger( int64_t value = 0 );

	// Constructor from string
	hxcBigInteger( const std::string& str );

	// Convert string to hxcBigInteger
	static hxcBigInteger FromString( const std::string& str );

	// Addition operator
	hxcBigInteger operator+( const hxcBigInteger& other ) const;

	// Negation operator
	hxcBigInteger operator-() const;

	// Subtraction operator
	hxcBigInteger operator-( const hxcBigInteger& other ) const;


	// Multiplication operator
	hxcBigInteger operator*( const hxcBigInteger& other ) const;


	// Division operator
	hxcBigInteger operator/( const hxcBigInteger& other ) const;

	// Modulus operator
	hxcBigInteger operator%( const hxcBigInteger& other ) const;


	// Modular exponentiation
	hxcBigInteger ModExp( const hxcBigInteger& exponent, const hxcBigInteger& modulus ) const;


	// ToString method for output
	std::string ToString() const;

private:
	std::vector<uint32_t> digits;  // 32-bit words in little-endian order
	bool negative;                 // Sign indicator
};


#endif //!__HX_BIG_INTEGER_H__
