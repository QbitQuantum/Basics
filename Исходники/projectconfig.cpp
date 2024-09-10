void ProjectConfig::setWritablePath(const string &writablePath)
{
    _writablePath = writablePath;
    normalize();
}