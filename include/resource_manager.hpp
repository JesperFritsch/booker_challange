#pragma once

// third-party libraries
#include "json.hpp"

#include "resource.hpp"

using json = nlohmann::json;

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