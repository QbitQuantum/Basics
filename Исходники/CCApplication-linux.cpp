bool Application::openURL(const std::string &url)
{
    std::string op = std::string("open ").append(url);
    return system(op.c_str())!=-1;
}