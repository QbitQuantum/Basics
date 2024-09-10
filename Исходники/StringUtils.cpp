bool StringUtils::istarts_with(const std::string &string, const std::string &prefix)
{
    return starts_with_internal(string.c_str(), string.size(),
                                prefix.c_str(), prefix.length(),
                                true);
}