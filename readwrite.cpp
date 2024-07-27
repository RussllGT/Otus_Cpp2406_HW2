#include "readwrite.hpp"
#include "auxiliary.hpp"
#include <fstream>
#include <exception>
#include <iostream>
#include <filesystem>

namespace tsk_ip
{
	source_data read_stream(std::istream& stream)
	{
		source_data result;

		std::string line;
		std::vector<std::string> data;
		while (std::getline(stream, line))
		{
			data = aux::split_string(line, '\t');
			if (data.size() != 3) throw std::invalid_argument("Incorrect input");

			result.push_back(std::make_tuple(ip_address(data[0]), data[1], data[2]));
		}

		return result;
	}

	source_data read_file(const std::string& filename)
	{
		std::ifstream filestream(filename);

		if (filestream.is_open())
		{
			source_data result = read_stream(filestream);
			filestream.close();
			return result;
		}
		else
		{
			throw std::invalid_argument("Incorrect file");
		}
	}

	void write_stream(std::ostream& stream, const std::vector<ip_address>& ips)
	{
		for (const auto& ip : ips) stream << ip.get_value() << std::endl;
	}

	void write_file(const std::string& filename, const std::vector<ip_address>& ips)
	{
		std::ofstream filestream;
		filestream.open(filename);

		if (filestream.is_open())
		{
			write_stream(filestream, ips);
			filestream.close();
		}
		else
		{
			throw std::invalid_argument("Incorrect file");
		}
	}
}