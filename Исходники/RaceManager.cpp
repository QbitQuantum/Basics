/* static */ bool RaceManager::writeGlobalObjects(const std::string& fileName, const RaceManager::globalObjectList_t& globalObjectList)
{
    FILE* f;
    errno_t error = fopen_s(&f, fileName.c_str(), "w");
    if (error)
    {
        printf("unable to open file for write %s\n", fileName.c_str());
        return false;
    }

    unsigned int id = 1;
    char fillZero[5] = {'0', '0', '0', '0', 0};

    assert(globalObjectList.size() < 100000);

    for (globalObjectList_t::const_iterator it = globalObjectList.begin();
         it != globalObjectList.end();
         it++)
    {
        if (id != 1)
        {
            fprintf_s(f, "\n");
        }
        if (id < 10)
        {
            fillZero[4] = 0;
        }
        else if (id < 100)
        {
            fillZero[3] = 0;
        }
        else if (id < 1000)
        {
            fillZero[2] = 0;
        }
        else if (id < 10000)
        {
            fillZero[1] = 0;
        }
        else
        {
            fillZero[0] = 0;
        }
        fprintf_s(f, "[%s%u]\n", fillZero, id);

        fprintf_s(f, "type=%s\n", (*it)->getObjectPool()->getName().c_str());
        fprintf_s(f, "pos=%f %f %f\n", (*it)->getPos().X, (*it)->getPos().Y, (*it)->getPos().Z);
        fprintf_s(f, "rot=%f %f %f\n", (*it)->getRot().X, (*it)->getRot().Y, (*it)->getRot().Z);
        fprintf_s(f, "scale=%f %f %f\n", (*it)->getScale().X, (*it)->getScale().Y, (*it)->getScale().Z);

        id++;
    }

    fclose(f);
    return true;
}