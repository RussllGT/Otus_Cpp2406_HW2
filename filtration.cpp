#include "filtration.hpp"
#include <vector>
#include <algorithm>

namespace tsk_ip
{
    std::vector<tsk_ip::ip_address> get_filtered_ips(const source_data& source)
    {
        std::vector<tsk_ip::ip_address> ips;
        for (const auto& data : source) ips.push_back(std::get<0>(data));

        std::sort(std::rbegin(ips), std::rend(ips));

        std::vector<tsk_ip::ip_address> temp[] = { std::vector<tsk_ip::ip_address>(), std::vector<tsk_ip::ip_address>(), std::vector<tsk_ip::ip_address>() };
        for (const auto& ip : ips)
        {
            if (ip.get_byte(0) == 1) temp[0].push_back(ip);

            if (ip.get_byte(0) == 46 && ip.get_byte(1) == 70)
            {
                temp[1].push_back(ip);
                temp[2].push_back(ip);
            }

            for (int index = 1; index < 4; ++index)
            {
                if (ip.get_byte(index) == 46) temp[2].push_back(ip);
            }
        }

        std::vector<tsk_ip::ip_address> result (ips);
        for (const auto& vec : temp)
        {
            for (const auto& ip : vec)
            {
                result.push_back(ip);
            }
        }
        return result;
    }
}