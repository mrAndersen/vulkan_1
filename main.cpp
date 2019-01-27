#include <iostream>
#include "src/core/vulkan_init.h"
#include "src/core/macro.h"

void glfwErrorCallback(int error, const char *description) {
    printf("\t -- GLFW \"%s\"", description);
}

int main() {
    glfwSetErrorCallback(glfwErrorCallback);
    glfwInit();

    VkInstance vkInstance = createVkInstance();

    VkPhysicalDevice vkPhysicalDevice = createVkPhysicalDevice(vkInstance);
    uint32_t queueFamilyIndex = getGraphicsBitQueueFamily(vkPhysicalDevice);

    VkDevice vkDevice = createVkDevice(vkPhysicalDevice, queueFamilyIndex);

//    VkSurfaceKHR vkSurfaceKHR = createVkSurface(vkInstance);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(1366, 768, "vulkan_1 test", nullptr, nullptr);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
    }

    vkDestroyDevice(vkDevice, nullptr);
    vkDestroyInstance(vkInstance, nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}