#pragma once

#include "resource.hpp"

Resource::Resource(std::string id)
{
    this->_id = id;
}

std::string Resource::get_id()
{
    return this->_id;
}

void Resource::add_sub_resource(std::shared_ptr<Resource> sub_resource)
{
    this->_sub_resources.push_back(sub_resource);
}

void Resource::book(std::string date)
// book this resource and all its sub-resources on a given date
{
    this->_dates_booked.push_back(date);
    for (auto sub_resource : this->_sub_resources){
        sub_resource->book(date);
    }
}

bool Resource::is_booked(std::string date)
// check if this resource is booked on a given date
{
    return std::find(this->_dates_booked.begin(), this->_dates_booked.end(), date) != this->_dates_booked.end();
}

bool Resource::is_available(std::string date)
// check if this resource and all if its sub-resources are available on a given date
{
    if (this->is_booked(date)) {
        return false;
    }
    else{
        for (auto& sub_resource : this->_sub_resources){
            if (!sub_resource->is_available(date)){
                return false;
            }
        }
    }
    // when no sub-resources are available (leaf node) and this resource is not booked
    return true;
}
