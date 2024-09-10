void EventReceiver::saveKeyMapping()
{
    FILE* f;
    errno_t error = fopen_s(&f, keyMappingFilename.c_str(), "w");
    if (error)
    {
        printf("unable to open file for write %s\n", keyMappingFilename.c_str());
        return;
    }

    bool first = true;

    for (keyNameMap_t::const_iterator it = keyNameMap.begin();
         it != keyNameMap.end();
         it++)
    {
        if (keyMap[it->second].primaryKeyConfig || keyMap[it->second].secondaryKeyConfig)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                fprintf_s(f, "\n");
            }
            fprintf_s(f, "[%s]\n", it->first.c_str());
        }
        if (keyMap[it->second].primaryKeyConfig)
        {
            keyMap[it->second].primaryKeyConfig->writeToFile(f, "primary");
        }
        if (keyMap[it->second].secondaryKeyConfig)
        {
            keyMap[it->second].secondaryKeyConfig->writeToFile(f, "secondary");
        }
    }

    fclose(f);
}