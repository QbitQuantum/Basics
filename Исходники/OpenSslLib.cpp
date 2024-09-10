unsigned long OpenSslLib::threadIdCallback(void)
{
#if 0
    unsigned long ret = 0;
    std::thread::id thread_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << thread_id;
    ss >> ret;
    return ret;
#else
    return getCurrentThreadId();
#endif
}