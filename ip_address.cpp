#include "ip_address.hpp"
#include "auxiliary.hpp"
#include <exception>
#include <sstream>

namespace tsk_ip
{
	ip_address::ip_address()
	{
		for (int i = 0; i < 4; ++i)
		{
			_address[i] = 0;
		}
	}

	ip_address::ip_address(const std::string& str)
	{
		std::vector<std::string> data = aux::split_string(str, '.');
		if (data.size() != 4) throw std::invalid_argument("Incorrect data");

		for (int i = 0; i < 4; ++i)
		{
			int num = std::stoi(data[i]);
			if (num < 0 || num > 255) throw std::invalid_argument("Incorrect ip value");
			_address[i] = num;
		}
	}

	std::string ip_address::get_value() const
	{
		std::string result;
		for (int i = 0; i < 4; ++i)
		{
			if (i != 0) result += '.';
			result += std::to_string(_address[i]);
		}
		return result;
	}

	uint8_t ip_address::get_byte(int index) const
	{
		if (index < 0 || index >3) throw std::invalid_argument("Incorrect index");
		return _address[index];
	}

	bool ip_address::operator==(const ip_address& other)  const
	{
		for (int i = 0; i < 4; ++i)
		{
			if (_address[i] != other._address[i]) return false;
		}
		return true;
	}

	bool ip_address::operator!=(const ip_address& other) const
	{
		return !(*this == other);
	}

	bool ip_address::operator<(const ip_address& other) const
	{
		for (int i = 0; i < 4; ++i)
		{
			if (_address[i] == other._address[i]) continue;
			return _address[i] < other._address[i];
		}
		return false;
	}

	bool ip_address::operator> (const ip_address& other) const
	{
		for (int i = 0; i < 4; ++i)
		{
			if (_address[i] == other._address[i]) continue;
			return _address[i] > other._address[i];
		}
		return false;
	}
}