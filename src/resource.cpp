#include <stdexcept>

#include "resource.hpp"

using json = nlohmann::json;

Resource::Resource(std::string id)
{
    this->_id = id;
}

Resource::~Resource()
{
    this->_sub_resources.clear();
    this->_dates_booked.clear();
}

std::string Resource::get_id()
{
    return this->_id;
}

void Resource::add_sub_resource(std::shared_ptr<Resource> sub_resource)
{
    this->_sub_resources.push_back(sub_resource);
}

bool Resource::book(std::string date)
{
    if (this->is_booked(date)){
        return false;
    }
    this->_dates_booked.push_back(date);
    for (auto sub_resource : this->_sub_resources){
        sub_resource->book(date);
    }
    return true;
}

bool Resource::is_booked(std::string date)
{
    bool self_booked = std::find(this->_dates_booked.begin(), this->_dates_booked.end(), date) != this->_dates_booked.end();
    if (self_booked){
        return true;
    }
    else{
        for (auto& sub_resource : this->_sub_resources){
            if (sub_resource->is_booked(date)){
                return true;
            }
        }
    }
    return false;

}

ResourceManager::ResourceManager(json& json_obj)
{
    this->_parse_json_object(json_obj);
}

ResourceManager::~ResourceManager()
{
    this->_resources.clear();
}

std::shared_ptr<Resource> ResourceManager::get_resource(std::string id)
{
    if (_resources.find(id) == _resources.end())
    {
        return nullptr;
    }
    return _resources[id];
}

bool ResourceManager::book(std::string id, std::string date)
{
    auto resource = this->get_resource(id);
    if (resource == nullptr){
        throw std::runtime_error("Resource not found: " + id);
    }
    return resource->book(date);
}

bool ResourceManager::is_booked(std::string id, std::string date)
{
    auto resource = this->get_resource(id);
    if (resource == nullptr){
        throw std::runtime_error("Resource not found: " + id);
    }
    return resource->is_booked(date);
}

std::shared_ptr<Resource> ResourceManager::_add_resource(std::shared_ptr<Resource> parent, std::string id)
{
    if (_resources.find(id) == _resources.end())
    {
        _resources[id] = std::make_unique<Resource>(id);
    }
    if (parent != nullptr && parent->get_id() != id)
    {
        parent->add_sub_resource(_resources[id]);
    }
    return _resources[id];
}

void ResourceManager::_parse_json_object(json& json_obj)
{
    std::shared_ptr<Resource> parent = nullptr;
    this->_recurse_json(json_obj, parent);
}

void ResourceManager::_recurse_json(json& json_obj, std::shared_ptr<Resource> parent)
{
    if(json_obj.contains("buildings")){
        for (auto& building : json_obj["buildings"]){
            auto parent_resource = this->_add_resource(parent, building["id"]);
            this->_recurse_json(building, parent_resource);
        }
    }
    if(json_obj.contains("sections")){
        for (auto& section : json_obj["sections"]){
            auto parent_resource = this->_add_resource(parent, section["id"]);
            this->_recurse_json(section, parent_resource);
        }
    }
    if(json_obj.contains("vehicles")){
        for (auto& vehicle_id : json_obj["vehicles"]){
            this->_add_resource(parent, vehicle_id);
        }
    }
}