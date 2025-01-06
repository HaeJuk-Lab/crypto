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
 @file		hxcAriaExport.h
 @brief
 */
#ifndef __HXC_ARIA_EXPROT_H__
#define __HXC_ARIA_EXPROT_H__


constexpr auto ARIA_BLOCK_MODE_IV_SIZE = 16;

enum hxeAriaRoundKey
{
    eAria128RoundNum = 12,
    eAria192RoundNum = 24,
    eAria256RoundNum = 16,
};

enum hxeAriaKeySize
{
    eAria128 = 16,
    eAria192 = 24,
    eAria256 = 32,
};

enum hxeAriaMode
{
    eAriaECBMode = 0,
    eAriaCBCMode = 1,
};

struct hxsAria
{
    hxeAriaMode eMode;
    hxeAriaKeySize eKeySize;
    uint8_t nIv[ARIA_BLOCK_MODE_IV_SIZE];
};

struct hxsAria128 : public hxsAria
{
    uint8_t nkey[16];
};

struct hxsAria192 : public hxsAria
{
    uint8_t nkey[24];
};

struct hxsAria256 : public hxsAria
{
    uint8_t nkey[32];
};



#endif //!__HXC_ARIA_EXPROT_H__