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
 @file		hxcDrbgAes.h
 @brief
 */

#ifndef __HXC_DRBG_AES_H__
#define __HXC_DRBG_AES_H__

#include "hxPch.h"
#include "hxcDrbg.h"

class hxcAES;
class hxcNoiseCollector;

class hxcDrbgAes : public hxcDrbg
{
	DECLARE_NO_COPY_CLASS( hxcDrbgAes );

public:
	hxcDrbgAes();
	virtual ~hxcDrbgAes();

	void Initialize( const std::vector<uint8_t>& _vSeed ) override;
	std::vector<uint8_t> Generate( size_t _nSize ) override;
	void ReSeed() override;

private:
	void InCrementV() override;

private:
	uint8_t m_nkey[32];  // AES-256 키
	uint8_t m_nIV[16];    // 카운터 값
	int m_nCounter;
	const int m_nReseedInterval = 4096;  // 4096번 생성 후 재시드
	std::unique_ptr<hxcAES> m_pImpl;		 // 기존 AES 구현체
	std::unique_ptr<hxcNoiseCollector> m_pColletor;

};

#endif // !__HXC_DRBG_AES_H__
