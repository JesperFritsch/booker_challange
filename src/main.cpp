#include <iostream>
#include <fstream>
#include <unordered_map>

#include "parsers.hpp"
#include "resource.hpp"

int main(int argc, char* argv[])
{
    try{
        auto args = parse_args(argc, argv);
        auto json_obj = parse_json(args["resources_file"]);
        auto queries = parse_queries(args["queries_file"]);
        auto output_file = args["output_file"];
        auto resource_manager = ResourceManager();
        resource_manager.populate_resources_from_json(json_obj, "");
        std::ofstream outfile(output_file);
        if (!outfile.is_open()) {
            throw std::runtime_error("Failed to open file: " + output_file);
        }
        for (auto query : queries) {
            if (query.query == "book") {
                outfile << resource_manager.book(query.id, query.date) << std::endl;
            }
            else if (query.query == "is_booked") {
                outfile << resource_manager.is_booked(query.id, query.date) << std::endl;
            }
            else if (query.query == "is_available") {
                outfile << resource_manager.is_available(query.id, query.date) << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
