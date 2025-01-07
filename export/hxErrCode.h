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
 @file		hxErrCode.h
 @brief
 */
#ifndef __HX_ERROR_CODE_H__
#define __HX_ERROR_CODE_H__


#ifndef ErrCode 
typedef unsigned __int32 ErrCode;
#endif 

constexpr ErrCode Err_Success		  = 0x0000;

constexpr ErrCode Err_OpCode		  = 0x1000;

constexpr ErrCode Err_KGCode		  = 0x2000;

constexpr ErrCode Err_ECCode		  = 0x3000;

constexpr ErrCode Err_DCCode		  = 0x4000;



#endif //!__HX_ERROR_CODE_H__