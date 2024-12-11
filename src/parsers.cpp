#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "parsers.hpp"

using json = nlohmann::json;

std::vector <Query> parse_queries(const std::string& filename)
// Parses a file with queries like: "book <id> <date>" or "is_booked <id> <date>" or "is_available <id> <date>"
//and returns a vector of Query objects
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    std::vector<Query> queries;
    while (std::getline(file, line)){
        if (line.empty() || line[0] == '#') {
            continue;
        }
        std::string query;
        std::string id;
        std::string date;
        std::istringstream iss(line);
        iss >> query >> id >> date;
        if (iss.fail()){
            throw std::runtime_error("Invalid query line: " + line);
        }
        queries.push_back({query, id, date});
    }
    return queries;
}

std::pair<std::string, std::string> split_file_extension(const std::string& filename)
// Splits a filename into a pair of strings: the name and the extension
{
    size_t pos = filename.rfind('.'); // Find the last occurrence of '.'
    if (pos == std::string::npos) {
        return {filename, ""}; // No extension found
    }
    std::string name = filename.substr(0, pos);
    std::string extension = filename.substr(pos + 1);
    return {name, extension};
}

std::unordered_map <std::string, std::string> parse_args(int argc, char* argv[])
// minimalistic argument parser
// expects 3 arguments: resources_file.json, queries_file.txt, output_file.txt
// the names of the files doesn't matter, but the extensions must be correct, the names in the arg_spec are used as keys in the returned map
{
    std::unordered_map <std::string, std::string> args;
    std::array <std::string, 3> arg_spec = {"resources_file.json", "queries_file.txt", "output_file.txt"};
    if (argc != 4) {
        throw std::runtime_error("Invalid number of arguments. Expected 3, got " + std::to_string(argc - 1));
    }
    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];
        auto [name, type] = split_file_extension(arg);
        auto [expected_name, expected_type] = split_file_extension(arg_spec[i - 1]);
        if (type != expected_type)
        {
            throw std::runtime_error("Invalid file type '" + type + "' for " + arg_spec[i - 1] + " (" + name + ") " + " Expected '" + expected_type + "'");
        }
        args[expected_name] = argv[i];
    }
    return args;
}

nlohmann::json parse_json(const std::string& filename)
// Parses a json file and returns a nlohmann::json object
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    json jsonObject;
    file >> jsonObject;
    return jsonObject;
}

