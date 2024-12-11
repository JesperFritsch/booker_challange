#pragma once

#include "resource.hpp"

Resource::Resource(std::string id)
{
    _id = id;
}

std::string Resource::get_id()
{
    return _id;
}

void Resource::add_sub_resource(std::shared_ptr<Resource> sub_resource)
{
    _sub_resources.push_back(sub_resource);
}

void Resource::book(std::string date)
// Book this resource and all its sub-resources on a given date.
// book does not check if the resource is available, it is assumed that the resource is checked for availability before booking.
// if book would check if the resource is available, it would traverse the whole (sub)tree multiple times, which is inefficient.
// Also if we are half way down the tree and we find that a sub-resource is not available, we would have to un-book all the resources that were booked so far.
{
    _dates_booked.push_back(date);
    for (auto sub_resource : _sub_resources){
        sub_resource->book(date);
    }
}

bool Resource::is_booked(std::string date)
// check if this resource is booked on a given date
{
    return std::find(_dates_booked.begin(), _dates_booked.end(), date) != _dates_booked.end();
}

bool Resource::is_available(std::string date)
// check if this resource and all if its sub-resources are available on a given date
{
    if (is_booked(date)) {
        return false;
    }
    else{
        for (auto& sub_resource : _sub_resources){
            if (!sub_resource->is_available(date)){
                return false;
            }
        }
    }
    // when no sub-resources are available (leaf node) and this resource is not booked
    return true;
}
