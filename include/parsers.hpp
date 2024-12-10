#pragma once

#include <map>
#include <string>
#include <vector>

// third-party libraries
#include "json.hpp"


struct Query {
    std::string query;
    std::string id;
    std::string date;
};

std::map <std::string, std::string> parse_args(int argc, char* argv[]);
nlohmann::json parse_json(const std::string& filename);
std::vector <Query> parse_queries(const std::string& filename);

