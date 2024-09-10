bool ZoneData::queryZDNames(int simNum,
                            int zoneNum,
                            vector<string> &names)
{
    int numZDs = 0;
    Tools::ClassManager *cm = Tools::ClassManager::getInstance();
    DataElement *zdInfo = NULL;

    names.clear();

    if (queryNumZDs(simNum, zoneNum, numZDs))
    {
        zdInfo = (DataElement *)cm->getObject("DTF_Lib::DataElement");
        for (int i = 0; i < numZDs; i++)
            if (queryZDbyNum(simNum, zoneNum, i, *zdInfo))
                names.push_back(zdInfo->getName());

        if (zdInfo != NULL)
        {
            cm->deleteObject(zdInfo->getID());
            zdInfo = NULL;
        }

        return true;
    }

    return false;
}