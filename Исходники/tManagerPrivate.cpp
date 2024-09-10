bool tManagerPrivate::Delete(tBridge bridge)
{
    // Oh FFS, this would be a one liner in C++11
    QVector<tBridge> toSave = AllBridges();

    const int size = toSave.size();
    bool found = false;
    for (int i = 0; i < size; ++i)
    {
        if (IsIdEqual(toSave[i], bridge))
        {
            toSave.remove(i);
            found = true;
            break;
        }
    }

    if (!found)
    {
        return false;
    }    
    
    SaveToSharedStorage(toSave);

    return true;
}