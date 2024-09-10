ECode AbstractSet::RemoveAll(
    /* [in] */ ICollection* collection,
    /* [out] */ Boolean* value)
{
    VALIDATE_NOT_NULL(value)

    Boolean result = FALSE;
    Int32 value1 = 0;
    Int32 value2 = 0;
    if ((GetSize(&value1), value1) <= (collection->GetSize(&value2), value2)) {
        AutoPtr<IIterator> it;
        GetIterator((IIterator**)&it);
        Boolean isflag = FALSE;
        while (it->HasNext(&isflag), isflag) {
            AutoPtr<IInterface> next;
            it->GetNext((IInterface**)&next);
            if (collection->Contains(next, &isflag), isflag) {
                it->Remove();
                result = TRUE;
            }
        }
    }
    else {
        AutoPtr<IIterator> it;
        (IIterable::Probe(collection))->GetIterator((IIterator**)&it);
        Boolean isflag = FALSE;
        while (it->HasNext(&isflag), isflag) {
            AutoPtr<IInterface> next;
            it->GetNext((IInterface**)&next);
            Boolean rmflag = FALSE;
            result = (Remove(next, &rmflag), rmflag) || result;
        }
    }
    *value = result;
    return NOERROR;
}