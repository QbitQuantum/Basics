int _glfwCreateContext(_GLFWwindow* window,
                       const _GLFWwndconfig* wndconfig,
                       const _GLFWfbconfig* fbconfig)
{
    _GLFWfbconfig closest;

    // Choose the best available fbconfig
    {
        unsigned int fbcount;
        _GLFWfbconfig* fbconfigs;
        const _GLFWfbconfig* result;

        fbconfigs = getFBConfigs(window, wndconfig, &fbcount);
        if (!fbconfigs)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "EGL: No usable EGLFBConfigs found");
            return GL_FALSE;
        }

        result = _glfwChooseFBConfig(fbconfig, fbconfigs, fbcount);
        if (!result)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "EGL: No EGLFBConfig matched the criteria");

            free(fbconfigs);
            return GL_FALSE;
        }

        closest = *result;
        free(fbconfigs);
    }

    return createContext(window, wndconfig, closest.platformID);
}