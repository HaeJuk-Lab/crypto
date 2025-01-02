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
 @file		pch.h
 @brief
 */

#ifndef __HX_PCH_H__
#define __HX_PCH_H__

#include "hxDefine.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cctype>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <exception>
#include <filesystem>
#include <functional>
#include <fstream>

#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <shared_mutex>
#include <signal.h>
#include <span>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <sstream>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>
#include <cstddef>


#ifdef __HX_WINDOWS__
#include <windows.h>
#include <tchar.h>

#elif defined(__HX_LINUX__)
// LINUX 에 특화된 코드 

#elif defined(__HX_MACOS__)
// macOS에 특화된 코드
#endif

#include "hxType.h"

#endif // !__HX_PCH_H__
