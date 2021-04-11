
#include "Precompiled.h"
#include "VulkanPlayer.h"


void VulkanPlayer::run() 
{
    initWindow();

    auto extensions = getRequiredExtensions();
    helper.createInstance(extensions);
    helper.setupDebugMessenger();
    createSurface();
    helper.initVulkan();
    mainLoop();
    helper.cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();
}