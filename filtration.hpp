#pragma once

#include "ip_address.hpp"

namespace tsk_ip
{
    std::vector<tsk_ip::ip_address> get_filtered_ips(const source_data&);
}