#pragma once

#include <vector>
#include <string>
#include <unordered_map>

// third-party libraries
#include "json.hpp"

using json = nlohmann::json;

class Resource{
    public:
        Resource(std::string id);
        void book(std::string date);
        bool is_booked(std::string date);
        bool is_available(std::string date);
        std::string get_id();
        void add_sub_resource(std::shared_ptr<Resource> sub_resource);
    private:
        std::string _id;
        std::vector<std::shared_ptr<Resource>> _sub_resources;
        std::vector<std::string> _dates_booked;
};

class ResourceManager{
    public:
        std::shared_ptr<Resource> get_resource(std::string id);
        std::string book(std::string id, std::string date);
        std::string is_booked(std::string id, std::string date);
        std::string is_available(std::string id, std::string date);
        void add_resource(std::string parent_id, std::string id);
        void populate_resources_from_json(json& json_obj, std::string parent_id);
    private:
        std::unordered_map<std::string, std::shared_ptr<Resource>> _resources;
        void _add_resource(std::shared_ptr<Resource> parent, std::string id);
};

