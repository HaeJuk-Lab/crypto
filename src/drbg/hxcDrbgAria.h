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
 @file		hxcDrbgAria.h
 @brief
 */
#ifndef __HXC_DRBG_ARIA_H__
#define __HXC_DRBG_ARIA_H__

#include "hxPch.h"
#include "hxcDrbg.h"
#include "../export/hxAriaExport.h"

class hxcARIA;
class hxcNoiseCollector;

class hxcDrbgAria : public hxcDrbg
{
	DECLARE_NO_COPY_CLASS( hxcDrbgAria );
public:
	hxcDrbgAria();
	virtual ~hxcDrbgAria();

	void Initialize( const std::vector<uint8_t>& _vSeed ) override;
	std::vector<uint8_t> Generate( size_t _nSize ) override;
	void ReSeed() override;

private:
	void InCrementV() override;

private:
	hxsAria256			m_stKey;
	int m_nCounter;
	const int m_nReseedInterval = 4096;  // 4096번 생성 후 재시드
	std::unique_ptr<hxcARIA> m_pImpl;		 // 기존 ARIA 구현체
	std::unique_ptr<hxcNoiseCollector> m_pColletor;
};

#endif // !__HXC_DRBG_AES_H__