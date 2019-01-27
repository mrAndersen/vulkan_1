#ifndef VULKAN_1_VULKAN_CORE_H
#define VULKAN_1_VULKAN_CORE_H

#include <vulkan/vulkan.h>
#include <stdexcept>
#include "macro.h"
#include <vector>

VkInstance createVkInstance();

VkPhysicalDevice pickPhysicalDevice(VkPhysicalDevice *physicalDevices);

VkPhysicalDevice createVkPhysicalDevice(VkInstance vkInstance);

VkDevice createVkDevice(VkPhysicalDevice vkPhysicalDevice, uint32_t queueFamilyIndex);

VkQueue getGraphicsQueue(VkDevice vkDevice, uint32_t familyIndex);

uint32_t getGraphicsBitQueueFamily(VkPhysicalDevice vkPhysicalDevice);

VkSurfaceKHR createVkSurface(VkInstance instance, GLFWwindow *window);

#endif //VULKAN_1_VULKAN_CORE_H
