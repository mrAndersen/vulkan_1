#include <iostream>
#include "src/core/vulkan_core.h"


int main() {
    VkInstance vkInstance = createVkInstance();
    VkPhysicalDevice vkPhysicalDevice = createVkPhysicalDevice(vkInstance);

    return 0;
}