#ifndef VULKAN_1_VULKAN_CORE_H
#define VULKAN_1_VULKAN_CORE_H

#include <vulkan/vulkan.h>
#include "macro.h"

VkInstance createVkInstance();

VkPhysicalDevice pickPhysicalDevice(VkPhysicalDevice *physicalDevices);

VkPhysicalDevice createVkPhysicalDevice(VkInstance vkInstance);

#endif //VULKAN_1_VULKAN_CORE_H
