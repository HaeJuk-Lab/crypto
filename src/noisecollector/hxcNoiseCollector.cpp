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
 @file		hxcNoiseCollector.cpp
 @brief
 */
#include "hxcNoiseCollector.h"

#ifdef __HX_WINDOWS__
#include "Windows/hxcNoiseCollectorImpl.h"
#elif __HX_LINUX__
#include "Linux/hxcNoiseCollectorImpl.h"
#elif __HX_MACOS__
#include "Mac/hxcNoiseCollectorImpl.h"
#elif __HX_ANDROID__
#include "Android/hxcNoiseCollectorImpl.h"
#elif __HX_IOS__
#include "Ios/hxcNoiseCollectorImpl.h"
#endif 


hxcNoiseCollector::hxcNoiseCollector()
{
	m_pImpl = std::make_unique<hxcNoiseCollectorImpl>();
}

hxcNoiseCollector::~hxcNoiseCollector()
{

}

std::vector<uint8_t> hxcNoiseCollector::CollectNoise( int _nRepeatCount )
{
	ErrCode nRet = Err_Success;

    std::vector<uint8_t> noise;
    
    //----------------------------------------------------------------------
    // IMPL 내부 변수 초기화, OS 마다 구현 다름
    nRet = m_pImpl->Reset();
    if( Err_Success != nRet )
    {
        //TODO: LOG
    }


    for( int i = 0; i <= _nRepeatCount; i++ )
    {
        nRet = m_pImpl->CollectPID( noise );
        if( Err_Success != nRet )
        {
            //TODO: LOG
        }

        nRet = m_pImpl->CollectHeapAddress( noise );
        if( Err_Success != nRet )
        {
            //TODO: LOG
        }

        nRet = m_pImpl->CollectHeapData( noise );
        if( Err_Success != nRet )
        {
            //TODO: LOG
        }

        nRet = m_pImpl->CollectRandomDevice( noise );
        if( Err_Success != nRet )
        {
            //TODO: LOG
        }

        nRet = m_pImpl->CollectProcessName( noise );
        if( Err_Success != nRet )
        {
            //TODO: LOG
        }
    }
    return noise;
}