static void swapIntervalWGL(int interval)
{
    _GLFWwindow* window = _glfwPlatformGetTls(&_glfw.contextSlot);

    window->context.wgl.interval = interval;

    if (!window->monitor)
    {
        if (IsWindowsVistaOrGreater())
        {
            BOOL enabled;

            // HACK: Disable WGL swap interval when desktop composition is enabled to
            //       avoid interfering with DWM vsync
            if (SUCCEEDED(DwmIsCompositionEnabled(&enabled)) && enabled)
                interval = 0;
        }
    }

    if (_glfw.wgl.EXT_swap_control)
        _glfw.wgl.SwapIntervalEXT(interval);
}