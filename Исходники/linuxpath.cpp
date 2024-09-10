boost::filesystem::path LinuxPath::getUserConfigPath() const
{
    return getEnv("XDG_CONFIG_HOME", getUserHome() / ".config") / mName;
}