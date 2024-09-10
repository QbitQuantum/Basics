Boolean AwHashSet::Remove(
    /* [in] */ IInterface* obj,
    /* [in] */ IInterface* p0)
{
    AutoPtr<ISet> mObj = ISet::Probe(obj);
    if (NULL == mObj)
    {
        Logger::E("AwHashSet", "AwHashSet::Remove, mObj is NULL");
        return FALSE;
    }
    return mObj->Remove(p0);
}