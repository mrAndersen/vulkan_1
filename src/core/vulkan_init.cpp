
#include "vulkan_init.h"


const int maxGPUProcessors = 16;

VkInstance createVkInstance() {
    VkInstance vkInstance = nullptr;

    uint32_t count = 10;
    auto extensionNames = glfwGetRequiredInstanceExtensions(&count);

    VkInstanceCreateInfo vkInstanceCreateInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vkInstanceCreateInfo.ppEnabledExtensionNames = extensionNames;
    vkInstanceCreateInfo.enabledExtensionCount = C_SIZE(extensionNames);

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

        VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevices[i], &vkPhysicalDeviceFeatures);

        if (
                vkPhysicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
                vkPhysicalDeviceFeatures.geometryShader
                ) {

            getGraphicsBitQueueFamily(physicalDevices[i]);

            printf(
                    "Selected GPU_%d: Name -> %s, ID -> %d, ApiVersion -> %d, Vendor -> %d\n",
                    i,
                    vkPhysicalDeviceProperties.deviceName,
                    vkPhysicalDeviceProperties.deviceID,
                    vkPhysicalDeviceProperties.apiVersion,
                    vkPhysicalDeviceProperties.vendorID
            );

            return physicalDevices[i];
        }
    }

    throw std::runtime_error("No suitable GPUs find in the system!");
}

VkDevice createVkDevice(VkPhysicalDevice vkPhysicalDevice, uint32_t queueFamilyIndex) {
    VkDevice vkDevice = nullptr;

//    const std::vector<const char *> deviceExtenstions = {
//            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
//    };

    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo vkDeviceCreateInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
    vkDeviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    vkDeviceCreateInfo.queueCreateInfoCount = 1;
//    vkDeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtenstions.size());
//    vkDeviceCreateInfo.ppEnabledExtensionNames = deviceExtenstions.data();


    ASSERT_VK(vkCreateDevice(vkPhysicalDevice, &vkDeviceCreateInfo, nullptr, &vkDevice));
    return vkDevice;
}


VkSurfaceKHR createVkSurface(VkInstance instance, GLFWwindow *window) {
    VkSurfaceKHR vkSurfaceKHR = nullptr;
    VkWin32SurfaceCreateInfoKHR vkWin32SurfaceCreateInfoKHR = {VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR};
    vkWin32SurfaceCreateInfoKHR.hinstance = glfwGetWin32Window(window);
    vkWin32SurfaceCreateInfoKHR.hwnd = GetModuleHandle(nullptr);

    ASSERT_VK(vkCreateWin32SurfaceKHR(instance, &vkWin32SurfaceCreateInfoKHR, nullptr, &vkSurfaceKHR));
}

uint32_t getGraphicsBitQueueFamily(VkPhysicalDevice vkPhysicalDevice) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, queueFamilies.data());

    uint32_t i = 0;
    for (const auto &queueFamily:queueFamilies) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            return i;
        }

        i++;
    }

    throw std::runtime_error("No VK_QUEUE_GRAPHICS_BIT queue family found");
}

VkQueue getGraphicsQueue(VkDevice vkDevice, uint32_t familyIndex) {
    VkQueue graphicsQueue = nullptr;
    vkGetDeviceQueue(vkDevice, familyIndex, 0, &graphicsQueue);

    return graphicsQueue;
}
