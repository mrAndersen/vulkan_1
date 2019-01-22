#ifndef VULKAN_1_MACRO_H
#define VULKAN_1_MACRO_H

#include <cstdlib>
#include <stdio.h>

#define ASSERT_VK(result) \
    if(result != VK_SUCCESS){ \
        printf("VK ERROR %d",result); \
        exit(-1); \
    }

#define C_SIZE(array) sizeof(array) / sizeof(array[0])

#endif //VULKAN_1_MACRO_H
