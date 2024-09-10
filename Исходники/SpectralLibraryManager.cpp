bool SpectralLibraryManager::isKindOf(const std::string& className) const
{
    if (className == getObjectType())
    {
        return true;
    }

    return SubjectAdapter::isKindOf(className);
}