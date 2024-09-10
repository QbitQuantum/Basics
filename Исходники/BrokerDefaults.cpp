std::string
Broker::Options::getHome() {
    std::string home;
    char home_c[MAX_PATH+1];
    size_t unused;
    if (0 == getenv_s (&unused, home_c, sizeof(home_c), "HOME"))
        home += home_c;
    return home;
}