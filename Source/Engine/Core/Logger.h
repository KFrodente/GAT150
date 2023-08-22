#pragma once
#include "Framework/Singleton.h"

#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define INFO_LOG(message)				{ if (yogi::Logger::Instance().Log(yogi::LogLevel::INFO, __FILE__, __LINE__))	   { yogi::Logger::Instance() << message << "\n";} }
#define WARNING_LOG(message)			{ if (yogi::Logger::Instance().Log(yogi::LogLevel::WARNING, __FILE__, __LINE__)) {yogi::Logger::Instance() << message << "\n";} }
#define ERROR_LOG(message)				{ if (yogi::Logger::Instance().Log(yogi::LogLevel::ERROR, __FILE__, __LINE__))   {yogi::Logger::Instance() << message << "\n";} }
#define ASSERT_LOG(condition, message)	{ if (!condition && yogi::Logger::Instance().Log(yogi::LogLevel::ASSERT, __FILE__, __LINE__))  {yogi::Logger::Instance() << message << "\n";} assert(condition); }
#else 
#define INFO_LOG(message)		{}
#define WARNING_LOG(message)	{}
#define ERROR_LOG(message)		{}
#define ASSERT_LOG(condition, message)		{}
#endif //_DEBUG
namespace yogi
{
	enum class LogLevel
	{
		INFO, WARNING, ERROR, ASSERT
	};

	class Logger : public Singleton<Logger>
	{
	public:
		Logger(LogLevel logLevel = LogLevel::INFO, std::ostream* ostream = &std::cout, const std::string& filename = "log.txt") :
			m_ostream{ ostream },
			m_logLevel{ logLevel }
		{
			if (!filename.empty()) m_fstream.open(filename);
		}

		bool Log(LogLevel logLevel, const std::string& filename, int line);

		template <typename T>
		Logger& operator << (T value);

	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	template<typename T>
	inline Logger& Logger::operator<<(T value)
	{
		if (m_ostream) *m_ostream << value;

		if (m_fstream.is_open())
		{
			m_fstream << value;
			m_fstream.flush();
		}

		return *this;
	}
}