#include "test_stream.hpp"
#include "ip_address.hpp"
#include "readwrite.hpp"
#include "filtration.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cstddef>

namespace tsk_ip
{
	size_t get_hash()
    {
        tsk_ip::source_data container = tsk_ip::read_file(tsk_ip::test_source_file);
        std::vector<tsk_ip::ip_address> solution = get_filtered_ips(container);
        tsk_ip::write_file(tsk_ip::test_result_file, solution);

        std::ifstream result_stream(test_result_file);
        std::stringstream ss;
        ss << result_stream.rdbuf();

        std::hash<std::string> hasher;
        size_t hash_value = hasher(ss.str());

        std::ofstream hash_stream;
		hash_stream.open(tsk_ip::test_hash_file);

		if (hash_stream.is_open())
		{
			hash_stream << hash_value << std::endl;
			hash_stream.close();
		}
		else
		{
			throw std::invalid_argument("Incorrect file");
		}

        return hash_value;
    }
}