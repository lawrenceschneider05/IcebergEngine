#pragma once
#include <sstream>
#include <utility>
#include <iostream>

#include "time/time.h"

using std::ostringstream;
using std::forward;
using std::cout;

namespace Engine
{
	enum LogLevel
	{
		LOG_DEBUG,
		LOG_INFO,
		LOG_WARN,
		LOG_ERROR,
		LOG_SUCCESS
	};
}

namespace
{
	const char* logLevelToString(Engine::LogLevel level)
	{
		switch (level) {
		case Engine::LOG_DEBUG: return "DEBUG";
		case Engine::LOG_INFO:  return "INFO";
		case Engine::LOG_WARN:  return "WARN";
		case Engine::LOG_ERROR: return "ERROR";
		case Engine::LOG_SUCCESS: return "SUCCESS";
		default: return "UNKNOWN";
		}
	}

	constexpr const char* COLOR_RESET = "\033[0m";
	constexpr const char* COLOR_DEBUG = "\033[36m"; // Cyan
	constexpr const char* COLOR_INFO = "\033[37m"; // White/Default
	constexpr const char* COLOR_WARN = "\033[33m"; // Yellow
	constexpr const char* COLOR_ERROR = "\033[31m"; // Red
	constexpr const char* COLOR_SUCCESS = "\033[32m"; // Green

	inline const char* logLevelToColor(Engine::LogLevel level)
	{
		switch (level) {
		case Engine::LOG_DEBUG:   return COLOR_DEBUG;
		case Engine::LOG_INFO:    return COLOR_INFO;
		case Engine::LOG_WARN:    return COLOR_WARN;
		case Engine::LOG_ERROR:   return COLOR_ERROR;
		case Engine::LOG_SUCCESS: return COLOR_SUCCESS;
		default:          return COLOR_RESET;
		}
	}
}

namespace Engine
{
	template<typename... Args>
	inline void log(LogLevel level, Args&&... args)
	{
		ostringstream ss;
		((ss << std::forward<Args>(args)), ...);

		cout << logLevelToColor(level)
			<< "[" << getCurrentDateTime() << "] "
			<< "[" << logLevelToString(level) << "] "
			<< ss.str()
			<< COLOR_RESET << "\n";
	}
}

