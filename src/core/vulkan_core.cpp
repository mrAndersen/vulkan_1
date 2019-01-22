#include "vulkan_core.h"
#include "macro.h"

const int maxGPUProcessors = 16;

VkInstance createVkInstance() {
    VkInstance vkInstance = nullptr;

    VkInstanceCreateInfo vkInstanceCreateInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    ASSERT_VK(vkCreateInstance(&vkInstanceCreateInfo, nullptr, &vkInstance));

    return vkInstance;
}

VkPhysicalDevice createVkPhysicalDevice(VkInstance vkInstance) {
    VkPhysicalDevice physicalDevices[maxGPUProcessors];
    uint32_t physicalDeviceCount = C_SIZE(physicalDevices);

    ASSERT_VK(vkEnumeratePhysicalDevices(vkInstance, &physicalDeviceCount, physicalDevices));
    VkPhysicalDevice physicalDevice = pickPhysicalDevice(physicalDevices);

    VkPhysicalDeviceProperties vkPhysicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &vkPhysicalDeviceProperties);

    return physicalDevice;
}

VkPhysicalDevice pickPhysicalDevice(VkPhysicalDevice *physicalDevices) {
    VkPhysicalDevice vkPhysicalDevice = nullptr;

    for (int i = 0; i < C_SIZE(physicalDevices); ++i) {
        VkPhysicalDeviceProperties vkPhysicalDeviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevices[i], &vkPhysicalDeviceProperties);

        printf(
                "GPU_%d: Name -> %s, ID -> %d, ApiVersion -> %d, Vendor -> %d\n",
                i,
                vkPhysicalDeviceProperties.deviceName,
                vkPhysicalDeviceProperties.deviceID,
                vkPhysicalDeviceProperties.apiVersion,
                vkPhysicalDeviceProperties.vendorID
        );
    }

    vkPhysicalDevice = physicalDevices[0];
    return vkPhysicalDevice;
}