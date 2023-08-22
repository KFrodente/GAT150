#include "Logger.h"
#include <iostream>
#include "FileIO.h"

namespace yogi 
{
	bool Logger::Log(LogLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case LogLevel::INFO:
			*this << "Info: ";
			break;
		case LogLevel::WARNING:
			*this << "Warning: ";
			break;
		case LogLevel::ERROR:
			*this << "Error: ";
			break;
		case LogLevel::ASSERT:
			*this << "Assert: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << "): ";

		return true;
	}
}