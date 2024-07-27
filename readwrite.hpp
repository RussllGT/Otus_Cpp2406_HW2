#pragma once

#include "ip_address.hpp"
#include <string>
#include <vector>

namespace tsk_ip
{
	const std::string test_source_file = R"(ip_filter.tsv)";
	const std::string test_result_file = R"(ip_filter_result.tsv)";
	const std::string test_hash_file = R"(test_hash.txt)";

	source_data read_stream(std::istream& stream);
	source_data read_file(const std::string& filename);

	void write_stream(std::ostream& stream, const std::vector<ip_address>& ips);
	void write_file(const std::string& filename, const std::vector<ip_address>& ips);
}