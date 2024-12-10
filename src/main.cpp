#include <iostream>

#include "parsers.hpp"
#include "resource.hpp"

int main(int argc, char* argv[])
{
    try{
        auto args = parse_args(argc, argv);
        auto json_obj = parse_json(args["resources_file"]);
        auto queries = parse_queries(args["queries_file"]);
        // std::cout << json_obj["resources"].dump(4) << std::endl;
        auto resource_manager = ResourceManager(json_obj["resources"]);
        std::cout << resource_manager.book("Green", "2020-01-01") << std::endl;
        std::cout << resource_manager.book("Yellow", "2020-01-01") << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
