#pragma once

#include <vector>
#include <string>
#include <memory>


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

