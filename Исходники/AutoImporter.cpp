bool AutoImporter::abort()
{
    Executable* pExecutable = dynamic_cast<Executable*>(mpPlugIn);
    if (pExecutable != NULL)
    {
        if (pExecutable->hasAbort() == true)
        {
            return pExecutable->abort();
        }
    }

    return false;
}