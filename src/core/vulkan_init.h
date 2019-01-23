#ifndef VULKAN_1_VULKAN_CORE_H
#define VULKAN_1_VULKAN_CORE_H

#include <vulkan/vulkan.h>
#include "macro.h"
#include <vector>

VkInstance createVkInstance();

VkPhysicalDevice pickPhysicalDevice(VkPhysicalDevice *physicalDevices);

VkPhysicalDevice createVkPhysicalDevice(VkInstance vkInstance);

VkDevice createVkDevice(VkPhysicalDevice vkPhysicalDevice);

VkSurfaceKHR createVkSurface(VkInstance instance);

#endif //VULKAN_1_VULKAN_CORE_H