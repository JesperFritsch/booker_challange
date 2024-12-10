#pragma once

#include <vector>
#include <string>

// third-party libraries
#include "json.hpp"

using json = nlohmann::json;

class Resource{
    public:
        Resource(std::string id);
        std::string get_id();
        void add_sub_resource(std::shared_ptr<Resource> sub_resource);
        bool book(std::string date);
        bool is_booked(std::string date);
        ~Resource();
    private:
        std::string _id;
        std::vector<std::shared_ptr<Resource>> _sub_resources;
        std::vector<std::string> _dates_booked;
};

class ResourceManager{
    public:
        ResourceManager(json& json_obj);
        ~ResourceManager();
        std::shared_ptr<Resource> get_resource(std::string id);
        bool book(std::string id, std::string date);
        bool is_booked(std::string id, std::string date);
    private:
        std::map<std::string, std::shared_ptr<Resource>> _resources;
        std::shared_ptr<Resource> _add_resource(std::shared_ptr<Resource> parent, std::string id);
        void _parse_json_object(json& json_obj);
        void _recurse_json(json& json_obj, std::shared_ptr<Resource> parent);
};