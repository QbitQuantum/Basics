ECode CConcurrentSkipListSet::Remove(
    /* [in] */ IInterface* object,
    /* [out] */ Boolean* modified)
{
    VALIDATE_NOT_NULL(modified);
    AutoPtr<IBoolean> b;
    CBoolean::New(TRUE, (IBoolean**)&b);
    AutoPtr<IConcurrentMap> map = (IConcurrentMap*)mM->Probe(EIID_IConcurrentMap);
    return map->Remove(object, b, modified);
}