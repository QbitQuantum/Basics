std::string getEnv(const char* envVar)
{
#ifdef _MSC_VER
    size_t requiredSize;
    getenv_s(&requiredSize, nullptr, 0, envVar);
    if (requiredSize == 0)
        return std::string();

    // std::string doesn't need terminating null
    std::string res(requiredSize - 1, 0);
    getenv_s(&requiredSize, &res[0], requiredSize, envVar);
    return res;
#else
    auto res = getenv(envVar);
    return res ? res : std::string();
#endif
}