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
 @file		hxdefine.h
 @brief
 */


#ifndef __HX_DEFINE_H__
#define __HX_DEFINE_H__


#define DECLARE_NO_ASSIGN_CLASS(classname)	\
private:										\
	classname& operator=(const classname&)

#define DECLARE_NO_COPY_CLASS(classname)		\
private:										\
	classname(const classname&);				\
	classname& operator=(const classname&)

#define DECLARE_NO_SELF_CLASS(classname)		\
protected:										\
	classname(){}								\
	~classname(){}


#define OUT 
#define IN
#define INOUT 

#ifndef NULL
#define NULL 0
#endif 

template<typename T>
class hxcSingleton
{
protected:
    hxcSingleton() {}

public:
    hxcSingleton( const hxcSingleton& ) = delete;
    hxcSingleton& operator=( const hxcSingleton& ) = delete;

    static T& GetInstance()
    {
        static T instance;
        return instance;
    }
};



//---------------------------------------------------------------------------------
// SUPPORT OS DEFINE 
#ifdef _WIN32

#endif 

#ifdef _LINUX

#endif

#ifdef _MACOS

#endif 


#endif // !__HX_DEFINE_H__

