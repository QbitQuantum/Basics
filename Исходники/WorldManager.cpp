int32 WorldManager::getPlanetIdByNameLike(BString name)
{
    uint8	id = 0;
    name.toLower();

    BStringVector::iterator it = mvPlanetNames.begin();

    while(it != mvPlanetNames.end())
    {
        // gLogger->log(LogManager::DEBUG,"Comparing: %s",  name.getAnsi());
        // gLogger->log(LogManager::DEBUG,"with     : %s",  (*it).getAnsi());
        if(Anh_Utils::cmpnistr((*it).getAnsi(),name.getAnsi(), 3) == 0)
        {
            // gLogger->log(LogManager::DEBUG,"Matched with planet id = %d",  id);
            return (id);
        }
        ++it;
        id++;
    }
    return(-1);
}