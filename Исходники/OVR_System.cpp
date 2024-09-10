// Initializes System core, installing allocator.
void System::Init()
{
    #if defined(_MSC_VER)
        // Make it so that failure of the C malloc family of functions results in the same behavior as C++ operator new failure.
        // This allows us to throw exceptions for malloc usage the same as for operator new bad_alloc.
        _set_new_mode(1);

        // Tells the standard library to direct new (and malloc) failures to us. Normally we wouldn't need to do this, as the 
        // C++ Standard Library already throws std::bad_alloc on operator new failure. The problem is that the Standard Library doesn't
        // throw std::bad_alloc upon malloc failure, and we can only intercept malloc failure via this means. _set_new_handler specifies
        // a global handler for the current running Standard Library. If the Standard Library is being dynamically linked instead
        // of statically linked, then this is a problem because a call to _set_new_handler would override anything the application
        // has already set.
        _set_new_handler(OVRNewFailureHandler);
    #else
        // This allows us to throw OVR::bad_alloc instead of std::bad_alloc, which provides less information.
        // Question: Does this set the handler for all threads or just the current thread? The C++ Standard doesn't 
        // explicitly state this, though it may be implied from other parts of the Standard.
        std::set_new_handler(OVRNewFailureHandler);
    #endif

    if (++System_Init_Count == 1)
    {
        Timer::initializeTimerSystem();
    }
    else
    {
        OVR_DEBUG_LOG(("[System] Init recursively called; depth = %d", System_Init_Count));
    }
}