#include <iostream>
#include "src/core/vulkan_init.h"
#include "src/core/macro.h"

void glfwErrorCallback(int error, const char *description) {
    printf("\t -- GLFW \"%s\"\n", description);
}

int main() {
    glfwSetErrorCallback(glfwErrorCallback);
    glfwInit();

    VkInstance vkInstance = createVkInstance();

    VkPhysicalDevice vkPhysicalDevice = createVkPhysicalDevice(vkInstance);
    uint32_t queueFamilyIndex = getGraphicsBitQueueFamily(vkPhysicalDevice);

    VkDevice vkDevice = createVkDevice(vkPhysicalDevice, queueFamilyIndex);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(1366, 768, "vulkan_1 test", nullptr, nullptr);

    VkSurfaceKHR vkSurfaceKHR = createVkSurface(vkInstance, window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
    }

    vkDestroySurfaceKHR(vkInstance, vkSurfaceKHR, nullptr);
    vkDestroyDevice(vkDevice, nullptr);
    vkDestroyInstance(vkInstance, nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}