#include "FileIO.h"
#include <fstream>
#include <iostream>
#include "Logger.h"

namespace yogi
{
	std::string yogi::getFilePath()
	{
		return std::filesystem::current_path().string();
	}

	bool setFilePath(const std::filesystem::path& path)
	{
		std::error_code ec;//error code
		std::filesystem::current_path(path, ec);

		return ec.value() == 0;
	}

	std::string getFileName(const std::filesystem::path& path)
	{
		return path.filename().string();
	}

	bool fileExists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
	}

	bool getFileSize(const std::filesystem::path& path, size_t& size)
	{
		std::error_code ec;//error code
		size = std::filesystem::file_size(path, ec);
		return ec.value() == 0;
	}
	
	bool readFile(const std::filesystem::path& path, std::string& buffer)
	{
		if (!fileExists(path))
		{
			//std::cout << "file not found: " << path << std::endl;
			WARNING_LOG("file not loaded: " << path.string());
			return false;
		}

		size_t size;
		if (!getFileSize(path, size)) return false;

		buffer.resize(size);

		std::ifstream stream(path);
		stream.read(buffer.data(), size);
		stream.close();

		return true;
	}
}
