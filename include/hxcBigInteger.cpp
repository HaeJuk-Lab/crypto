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
 @file		hxBigInteger.cpp
 @brief
 */
#include "hxBigInteger.h"

 // Helper function to remove leading zeros
void hxBigInteger::Trim()
{
	while( !digits.empty() && digits.back() == 0 )
	{
		digits.pop_back();
	}
	if( digits.empty() )
	{
		digits.push_back( 0 );
		negative = false;
	}
}
// Default constructor
hxBigInteger::hxcBigInteger( int64_t value ) : negative( value < 0 )
{
	uint64_t absValue = (value < 0) ? -value : value;
	while( absValue > 0 )
	{
		digits.push_back( static_cast<uint32_t>(absValue & 0xFFFFFFFF) );
		absValue >>= 32;
	}
	if( digits.empty() )
	{
		digits.push_back( 0 );
	}
}

// Constructor from string
hxBigInteger::hxcBigInteger( const std::string& str )
{
	*this = FromString( str );
}

// Convert string to hxcBigInteger
hxcBigInteger hxBigInteger::FromString( const std::string& str )
{
	hxcBigInteger result;
	result.negative = (str[0] == '-');
	size_t start = (result.negative || str[0] == '+') ? 1 : 0;

	for( size_t i = start; i < str.length(); ++i )
	{
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

// Addition operator
hxcBigInteger hxBigInteger::operator+( const hxcBigInteger& other ) const
{
	if( negative == other.negative )
	{
		hxcBigInteger result;
		result.negative = negative;
		uint64_t carry = 0;
		size_t maxSize = std::max( digits.size(), other.digits.size() );

		for( size_t i = 0; i < maxSize || carry; ++i )
		{
			uint64_t sum = carry;
			if( i < digits.size() ) sum += digits[i];
			if( i < other.digits.size() ) sum += other.digits[i];

			if( i >= result.digits.size() )
			{
				result.digits.push_back( 0 );
			}
			result.digits[i] = sum & 0xFFFFFFFF;
			carry = sum >> 32;
		}
		result.Trim();
		return result;
	}
	return *this - (-other);
}

// Negation operator
hxcBigInteger hxBigInteger::operator-() const
{
	hxcBigInteger result = *this;
	if( *this != 0 )
	{
		result.negative = !negative;
	}
	return result;
}

// Subtraction operator
hxcBigInteger hxBigInteger::operator-( const hxcBigInteger& other ) const
{
	if( negative != other.negative )
	{
		return *this + (-other);
	}

	if( *this == other )
		return hxcBigInteger( 0 );

	bool swapNeeded = (*this < other);
	const hxcBigInteger& larger = swapNeeded ? other : *this;
	const hxcBigInteger& smaller = swapNeeded ? *this : other;

	hxcBigInteger result;
	result.negative = swapNeeded ? !negative : negative;

	int64_t carry = 0;
	for( size_t i = 0; i < larger.digits.size() || carry; ++i )
	{
		int64_t diff = larger.digits[i] - carry - (i < smaller.digits.size() ? smaller.digits[i] : 0);
		carry = (diff < 0);
		if( carry )
			diff += 0x100000000LL;
		result.digits.push_back( static_cast<uint32_t>(diff) );
	}
	result.Trim();
	return result;
}

// Multiplication operator
hxcBigInteger hxBigInteger::operator*( const hxcBigInteger& other ) const
{
	hxcBigInteger result;
	result.digits.resize( digits.size() + other.digits.size() );
	result.negative = (negative != other.negative);

	for( size_t i = 0; i < digits.size(); ++i )
	{
		uint64_t carry = 0;
		for( size_t j = 0; j < other.digits.size() || carry; ++j )
		{
			uint64_t current = result.digits[i + j] +
				carry +
				static_cast<uint64_t>(digits[i]) * (j < other.digits.size() ? other.digits[j] : 0);
			result.digits[i + j] = current & 0xFFFFFFFF;
			carry = current >> 32;
		}
	}
	result.Trim();
	return result;
}

// Division operator
hxcBigInteger hxBigInteger::operator/( const hxcBigInteger& other ) const
{
	// To be implemented: Long division algorithm
	return hxcBigInteger( 0 );
}

// Modulus operator
hxcBigInteger hxBigInteger::operator%( const hxcBigInteger& other ) const
{
	// To be implemented: Modulus calculation
	return hxcBigInteger( 0 );
}

// Modular exponentiation
hxcBigInteger hxBigInteger::ModExp( const hxcBigInteger& exponent, const hxcBigInteger& modulus ) const
{
	hxcBigInteger base = *this % modulus;
	hxcBigInteger result( 1 );
	hxcBigInteger exp = exponent;

	while( exp != 0 )
	{
		if( exp.digits[0] & 1 )
		{
			result = (result * base) % modulus;
		}
		base = (base * base) % modulus;
		exp >>= 1;
	}
	return result;
}

// ToString method for output
std::string hxBigInteger::ToString() const
{
	if( *this == 0 ) return "0";
	hxcBigInteger temp = *this;
	std::string result;
	while( temp != 0 )
	{
		result += '0' + (temp % 10).digits[0];
		temp /= 10;
	}
	if( negative ) result += '-';
	std::reverse( result.begin(), result.end() );
	return result;
}