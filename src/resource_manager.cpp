#include "resource_manager.hpp"

using json = nlohmann::json;

std::shared_ptr<Resource> ResourceManager::get_resource(std::string id)
// get a resource by its id
{
    if (_resources.find(id) == _resources.end()) {
        return nullptr;
    }
    return _resources[id];
}

std::string ResourceManager::is_booked(std::string id, std::string date)
// check if a resource is booked on a given date
{
    auto resource = this->get_resource(id);
    if (resource == nullptr) {
        throw std::runtime_error("Resource not found: " + id);
    }
    return (resource->is_booked(date)) ? "yes" : "no";
}

std::string ResourceManager::is_available(std::string id, std::string date)
// check if a resource and all of its sub-resources are available on a given date
{
    auto resource = this->get_resource(id);
    if (resource == nullptr) {
        throw std::runtime_error("Resource not found: " + id);
    }
    return (resource->is_available(date)) ? "yes" : "no";
}

std::string ResourceManager::book(std::string id, std::string date)
// book a resource on a given date
{
    auto resource = this->get_resource(id);
    if (resource == nullptr) {
        throw std::runtime_error("Resource not found: " + id);
    }
    if (!resource->is_available(date)) {
        // before booking a resource, we should check if it is available
        return "failed";
    }
    resource->book(date);
    return "ok";
}

void ResourceManager::add_resource(std::string parent_id, std::string id)
// add a resource to the resource manager
// if parent_id is not an empty string, add the resource as a sub-resource of the parent
{
    auto parent = this->get_resource(parent_id);
    if (parent_id != "" && parent == nullptr) {
        throw std::runtime_error("Parent resource not found: '" + parent_id + "'");
    }
    this->_add_resource(parent, id);
    return;
}

void ResourceManager::_add_resource(std::shared_ptr<Resource> parent, std::string id)
// add a resource to the resource manager
{
    if (_resources.find(id) == _resources.end()) {
        _resources[id] = std::make_shared<Resource>(id);
    }
    if (parent != nullptr && parent->get_id() != id) {
        parent->add_sub_resource(_resources[id]);
    }
    return;
}

void ResourceManager::populate_resources_from_json(json& json_obj, std::string parent_id){
    // here we assume that any string values (not keys) are resource ids
    // and populate the resource manager with them recursively.
    // No error checking is done here, we assume the json is well-formed.
    std::string next_parent_id = parent_id;
    if(json_obj.contains("id")) {
        next_parent_id = json_obj["id"].get<std::string>();
    }
    for (auto& [key, value] : json_obj.items()){
        if (value.is_string()) {
            add_resource(parent_id, value.get<std::string>());
        }
        else if (value.is_object() || value.is_array()) {
            populate_resources_from_json(value, next_parent_id);
        }
    }
}