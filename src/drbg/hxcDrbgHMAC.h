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
 @file		hxcDrbgHMAC.h
 @brief
 */

#ifndef __HXC_DRBG_HMAC_H__
#define __HXC_DRBG_HMAC_H__

#include "hxPch.h"
#include "hxcDrbg.h"

class hxcNoiseCollector;

class hxcDrbgHMAC : public hxcDrbg
{
	DECLARE_NO_COPY_CLASS( hxcDrbgHMAC );

public:
	hxcDrbgHMAC();
	virtual ~hxcDrbgHMAC();

	void Initialize( const std::vector<uint8_t>& _vSeed ) override;
	std::vector<uint8_t> Generate( size_t _nSize ) override;
	void ReSeed() override;

private:
	void InCrementV() override;
	void Hmac( const std::vector<uint8_t>& _vData, const std::vector<uint8_t>& _vKey );

private:
	uint8_t m_nkey[32];    // 키
	uint8_t m_nIV[16];     // 카운터 값
	int m_nCounter;
	const int m_nReseedInterval = 4096;  // 4096번 생성 후 재시드
	std::unique_ptr<hxcNoiseCollector> m_pColletor;
};

#endif // !__HXC_DRBG_HMAC_H__