#include "readwrite.hpp"
#include "ip_address.hpp"
#include "filtration.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <exception>
#include <algorithm>
#include <stdlib.h>

int main()
{
    try
    {
        tsk_ip::source_data container = tsk_ip::read_stream(std::cin);
        std::vector<tsk_ip::ip_address> solution = get_filtered_ips(container);
        tsk_ip::write_stream(std::cout, solution);
    }
    catch(const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}