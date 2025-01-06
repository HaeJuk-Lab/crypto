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
 @file		hxcARIA_AVX.cpp
 @brief
 */

#include "hxcARIA_AVX.h"
#include "hxcARIA.h"

#ifdef __HX_WINDOWS__
#include <immintrin.h>
#include <intrin.h>
#else 
#include <cpuid.h>
#endif 

hxcARIA_AVX::hxcARIA_AVX()
	: m_nNumRounds(0)
	, m_eMode( hxeAriaMode::eAriaCBCMode )
{
	m_IsSupport = IsSupportAVX();

	std::fill( std::begin( m_nRoundKeys ), std::end( m_nRoundKeys ), 0 );
	std::fill( std::begin( m_nIV ), std::end( m_nIV ), 0 );

	std::cout << "[INFO] AVX-optimized ARIA initialized." << std::endl;
}

hxcARIA_AVX::~hxcARIA_AVX()
{

}

// 초기화 구현
ErrCode hxcARIA_AVX::Init( const hxsAria* _pKey )
{
	ErrCode nRet = Err_Success;

	//-------------------------------------------------------------------------------------
	// Check Initialzie Value


	m_eMode = _pKey->eMode;

	if( hxeAriaKeySize::eAria128 == _pKey->eKeySize )
	{
		const hxsAria128* pKey = reinterpret_cast<const  hxsAria128*>(_pKey);
		std::memcpy( m_nRoundKeys, pKey->nkey, pKey->eKeySize );
	}
	else if( hxeAriaKeySize::eAria192 == _pKey->eKeySize )
	{
		const hxsAria192* pKey = reinterpret_cast<const  hxsAria192*>(_pKey);
		std::memcpy( m_nRoundKeys, pKey->nkey, pKey->eKeySize );
	}
	else if( hxeAriaKeySize::eAria256 == _pKey->eKeySize )
	{
		const hxsAria256* pKey = reinterpret_cast<const  hxsAria256*>(_pKey);
		std::memcpy( m_nRoundKeys, pKey->nkey, pKey->eKeySize );
	}

	std::memcpy( m_nIV, _pKey->nIv, ARIA_BLOCK_MODE_IV_SIZE );

	std::cout << "[INFO] ARIA initialized with " << m_nNumRounds << " rounds." << std::endl;

	return nRet;
}

// 키 생성기 구현
ErrCode hxcARIA_AVX::Generatorkey( INOUT hxsAria* _pKey)
{
	ErrCode nRet = Err_Success;

	_pKey->eMode = hxeAriaMode::eAriaCBCMode;
	
	if(  hxeAriaKeySize::eAria128 == _pKey->eKeySize )
	{
		hxsAria128* pKey = reinterpret_cast<hxsAria128*>(_pKey);
		if( nullptr != pKey )
		{
			//---------------------------------------------------------------------------
			// 초기화 
			std::fill( std::begin( pKey->nkey ), std::end( pKey->nkey ), 0 );
			std::fill( std::begin( pKey->nIv ), std::end( pKey->nIv ), 0 );

			//---------------------------------------------------------------------------
			// Gen 16Byte Random Key    
			this->GeneratorRandomData( pKey->nkey, pKey->eKeySize );

			//---------------------------------------------------------------------------
			// Gen 16Byte Random Iv
			this->GeneratorRandomData( pKey->nIv, ARIA_BLOCK_MODE_IV_SIZE );

			return nRet;
		}
	}
	else if( hxeAriaKeySize::eAria192 == _pKey->eKeySize )
	{
		hxsAria192* pKey = reinterpret_cast<hxsAria192*>(_pKey);
		if( nullptr != pKey )
		{
			//---------------------------------------------------------------------------
			// 초기화 
			std::fill( std::begin( pKey->nkey ), std::end( pKey->nkey ), 0 );
			std::fill( std::begin( pKey->nIv ), std::end( pKey->nIv ), 0 );

			//---------------------------------------------------------------------------
			// Gen 16Byte Random Key    
			this->GeneratorRandomData( pKey->nkey, pKey->eKeySize );

			//---------------------------------------------------------------------------
			// Gen 16Byte Random Iv
			this->GeneratorRandomData( pKey->nIv, ARIA_BLOCK_MODE_IV_SIZE );

			return nRet;
		}
	}
	else if( hxeAriaKeySize::eAria256 == _pKey->eKeySize )
	{
		hxsAria256* pKey = reinterpret_cast<hxsAria256*>(_pKey);
		if( nullptr != pKey )
		{
			//---------------------------------------------------------------------------
			// 초기화 
			std::fill( std::begin( pKey->nkey ), std::end( pKey->nkey ), 0 );
			std::fill( std::begin( pKey->nIv ), std::end( pKey->nIv ), 0 );

			//---------------------------------------------------------------------------
			// Gen 16Byte Random Key    
			this->GeneratorRandomData( pKey->nkey, pKey->eKeySize );

			//---------------------------------------------------------------------------
			// Gen 16Byte Random Iv
			this->GeneratorRandomData( pKey->nIv, ARIA_BLOCK_MODE_IV_SIZE );

			return nRet;
		}
	}
	return nRet;
}

ErrCode hxcARIA_AVX::CheckInitOpValues()
{
	ErrCode nRet = Err_Success;

	return nRet;
}

// 암호화 구현
ErrCode hxcARIA_AVX::Encrypt( const uint8_t* input, uint8_t* output, size_t length )
{
	ErrCode nRet = Err_Success;
	//-----------------------------------------------------------------------------------------------
	// 초기화 체크 
	nRet = CheckInitOpValues();
	if( Err_Success != nRet )
	{
		return nRet;
	}

	uint8_t block[16];
	size_t numBlocks = length / 16;

	for( size_t i = 0; i < numBlocks; ++i ) 
	{
		std::memcpy( block, input + (i * 16), 16 );

		if( hxeAriaMode::eAriaCBCMode == m_eMode )
		{
			for( size_t j = 0; j < 16; ++j )
				block[j] ^= m_nIV[j];
		}

		EncryptBlock( block );
		std::memcpy( output + (i * 16), block, 16 );

		if( hxeAriaMode::eAriaCBCMode == m_eMode )
		{
			std::memcpy( m_nIV, block, 16 );  // CBC: 다음 블록을 위해 IV 업데이트
		}
	}
	return nRet;
}

// 복호화 구현
ErrCode hxcARIA_AVX::Decrypt( const uint8_t* input, uint8_t* output, size_t length )
{
	ErrCode nRet = Err_Success;

	//-----------------------------------------------------------------------------------------------
	// 초기화 체크 
	nRet = CheckInitOpValues();
	if( Err_Success != nRet )
	{
		return nRet;
	}


	uint8_t block[16];
	uint8_t previousBlock[16];
	size_t numBlocks = length / 16;

	for( size_t i = 0; i < numBlocks; ++i ) {
		std::memcpy( block, input + (i * 16), 16 );
		std::memcpy( previousBlock, block, 16 );  // CBC 모드에서 XOR 전을 위해 복사

		DecryptBlock( block );

		if( hxeAriaMode::eAriaCBCMode == m_eMode )
		{
			for( size_t j = 0; j < 16; ++j )
				block[j] ^= m_nIV[j];

			std::memcpy( m_nIV, previousBlock, 16 );  // CBC: 다음 블록을 위해 IV 업데이트
		}

		std::memcpy( output + (i * 16), block, 16 );
	}
	return nRet;
}

// 블록 크기 반환
size_t hxcARIA_AVX::BlockSize() const
{
	return 16;
}

// 암호화 라운드 적용
ErrCode hxcARIA_AVX::EncryptBlock( uint8_t* block )
{
	ErrCode nRet = Err_Success;
	
	//-----------------------------------------------------------------------------------------------
	// 초기화 체크 
	nRet = CheckInitOpValues();
	if( Err_Success != nRet )
	{
		return nRet;
	}


	for( int round = 0; round < m_nNumRounds; ++round )
	{
		SubBytes_AVX( block );
		ShiftRows_AVX( block );
		MixColumns_AVX( block );
		AddRoundKey_AVX( block, reinterpret_cast<const uint8_t*>(&round) );
	}

	return nRet;
}

// 복호화 라운드 적용
ErrCode hxcARIA_AVX::DecryptBlock( uint8_t* block )
{
	ErrCode nRet = Err_Success;
	
	//-----------------------------------------------------------------------------------------------
	// 초기화 체크 
	nRet = CheckInitOpValues();
	if( Err_Success != nRet )
	{
		return nRet;
	}

	for( int round = m_nNumRounds - 1; round >= 0; --round )
	{
		AddRoundKey_AVX( block, reinterpret_cast<const uint8_t*>(&round) );
		MixColumns_AVX( block );
		ShiftRows_AVX( block );
		SubBytes_AVX( block );
	}

	return nRet;
}


void hxcARIA_AVX::SubBytes_AVX( uint8_t* block )
{
	__m128i v = _mm_loadu_si128( reinterpret_cast<const __m128i*>(block) );
	alignas(32) uint8_t temp[16];

	for( int i = 0; i < 16; i++ )
	{
		temp[i] = sbox[block[i]];
	}

	_mm_storeu_si128( reinterpret_cast<__m128i*>(block), _mm_load_si128( reinterpret_cast<__m128i*>(temp) ) );
}

void hxcARIA_AVX::ShiftRows_AVX( uint8_t* block )
{
	__m128i v = _mm_loadu_si128( reinterpret_cast<const __m128i*>(block) );
	v = _mm_shuffle_epi8( v, _mm_set_epi8( 15, 12, 13, 14, 11, 8, 9, 10, 7, 4, 5, 6, 3, 0, 1, 2 ) );
	_mm_storeu_si128( reinterpret_cast<__m128i*>(block), v );
}

void hxcARIA_AVX::MixColumns_AVX( uint8_t* block )
{
	__m128i v = _mm_loadu_si128( reinterpret_cast<const __m128i*>(block) );
	__m128i mask = _mm_set1_epi8( 0x1b );

	__m128i t = _mm_xor_si128( v, _mm_srli_epi32( v, 8 ) );
	t = _mm_xor_si128( t, _mm_srli_epi32( t, 16 ) );
	t = _mm_xor_si128( t, _mm_and_si128( v, mask ) );

	_mm_storeu_si128( reinterpret_cast<__m128i*>(block), t );
}

void hxcARIA_AVX::AddRoundKey_AVX( uint8_t* block, const uint8_t* roundKey )
{
	__m128i v = _mm_loadu_si128( reinterpret_cast<const __m128i*>(block) );
	__m128i rk = _mm_loadu_si128( reinterpret_cast<const __m128i*>(roundKey) );
	v = _mm_xor_si128( v, rk );
	_mm_storeu_si128( reinterpret_cast<__m128i*>(block), v );
}

bool hxcARIA_AVX::IsSupportAVX()
{
	return m_IsSupport;
}

bool hxcARIA_AVX::GetSupportAVX()
{
#ifdef __HX_WINDOWS__
	int cpuInfo[4] = { 0 };
	__cpuid( cpuInfo, 1 );  // 기능 ID 1번으로 호출

	if( cpuInfo[2] & (1 << 28) ) 
	{  // AVX는 ecx(=cpuInfo[2])의 28번째 비트
		return true;
	}
	return false;
#else 
	unsigned int eax, ebx, ecx, edx;
	__cpuid( 1, eax, ebx, ecx, edx );

	if( ecx & (1 << 28) ) {
		return true;
	}
	return false;
#endif 
}
