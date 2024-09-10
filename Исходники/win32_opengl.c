void _glfwPlatformCopyContext(_GLFWwindow* src, _GLFWwindow* dst, unsigned long mask)
{
    if (!wglCopyContext(src->WGL.context, dst->WGL.context, mask))
    {
        _glfwSetError(GLFW_PLATFORM_ERROR,
                      "Win32/WGL: Failed to copy OpenGL context attributes");
    }
}