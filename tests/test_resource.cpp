#include <iostream>
#include <memory>
#include "resource.hpp"


// Helper macro to simplify test result logging
#define ASSERT_TRUE(condition, message)                                  \
    if (!(condition)) {                                                  \
        std::cerr << "Test failed: " << message << " (" << __FILE__      \
                  << ":" << __LINE__ << ")" << std::endl;                \
        return 1;                                                        \
    }

int main() {
    // Test 1: Resource creation and ID retrieval
    {
        auto resource = std::make_shared<Resource>("TestResource");
        ASSERT_TRUE(resource->get_id() == "TestResource", "Resource ID mismatch");
        std::cout << "Test 1 passed: Resource creation and ID retrieval" << std::endl;
    }

    // Test 2: Booking a resource
    {
        auto resource = std::make_shared<Resource>("TestResource");
        resource->book("2023-12-01");
        ASSERT_TRUE(resource->is_booked("2023-12-01"), "Resource should be booked on 2023-12-01");
        ASSERT_TRUE(!resource->is_booked("2023-12-02"), "Resource should not be booked on 2023-12-02");
        std::cout << "Test 2 passed: Booking a resource" << std::endl;
    }

    // Test 3: Adding and booking sub-resources
    {
        auto parent = std::make_shared<Resource>("ParentResource");
        auto child = std::make_shared<Resource>("ChildResource");

        parent->add_sub_resource(child);
        parent->book("2023-12-01");

        ASSERT_TRUE(parent->is_booked("2023-12-01"), "Parent resource should be booked");
        ASSERT_TRUE(child->is_booked("2023-12-01"), "Child resource should be booked through parent");
        std::cout << "Test 3 passed: Adding and booking sub-resources" << std::endl;
    }

    // Test 4: Checking availability
    {
        auto resource = std::make_shared<Resource>("TestResource");
        ASSERT_TRUE(resource->is_available("2023-12-01"), "Resource should be available initially");
        resource->book("2023-12-01");
        ASSERT_TRUE(!resource->is_available("2023-12-01"), "Resource should not be available after booking");
        std::cout << "Test 4 passed: Checking availability" << std::endl;
    }

    // Test 5: Checking that common child are not available
    {
        auto parent1 = std::make_shared<Resource>("ParentResource1");
        auto parent2 = std::make_shared<Resource>("ParentResource2");
        auto child = std::make_shared<Resource>("ChildResource");

        parent1->add_sub_resource(child);
        parent2->add_sub_resource(child);

        parent1->book("2023-12-01");
        ASSERT_TRUE(!parent2->is_available("2023-12-01"), "Parent resource should not be available");
        std::cout << "Test 5 passed: Checking that common child are not available" << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
