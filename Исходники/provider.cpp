void Provider::RemoveFromPropertyServiceTable(
    /* [in] */ IInterface* key)
{
    if (key == NULL || IString::Probe(key) == NULL) {
        return;
    }
    String k;
    ICharSequence::Probe(key)->ToString(&k);
    if (k.StartWith("Provider.")) { // Provider service type is reserved
        return;
    }
    AutoPtr<IProviderService> s;
    String serviceName;
    String algorithm;
    String attribute;
    Int32 i;
    if (k.StartWith("Alg.Alias.")) { // Alg.Alias.<crypto_service>.<aliasName>=<standardName>
        String aliasName;
        String service_alias = k.Substring(10);
        i = service_alias.IndexOf('.');
        serviceName = service_alias.Substring(0, i);
        aliasName = service_alias.Substring(i + 1);
        if (mPropertyAliasTable != NULL) {
            AutoPtr<ICharSequence> keyObj;
            CString::New(Key(serviceName, aliasName), (ICharSequence**)&keyObj);
            mPropertyAliasTable->Remove(keyObj);
        }
        if (mPropertyServiceTable != NULL) {
            AutoPtr<ICharSequence> keyObj;
            CString::New(aliasName, (ICharSequence**)&keyObj);
            AutoPtr<ICollection> values;
            mPropertyServiceTable->GetValues((ICollection**)&values);
            AutoPtr<IIterator> it;
            values->GetIterator((IIterator**)&it);
            Boolean hasNext;
            while (it->HasNext(&hasNext), hasNext) {
                s = NULL;
                it->GetNext((IInterface**)&s);
                AutoPtr<IList> aliases;
                s->GetAliases((IList**)&aliases);
                Boolean result;
                if (aliases->Contains(keyObj, &result), result) {
                    aliases->Remove(keyObj);
                    return;
                }
            }
        }
        return;
    }
    Int32 j = k.IndexOf('.');
    if (j == -1) { // unknown format
        return;
    }

    i = k.IndexOf(' ');
    if (i == -1) { // <crypto_service>.<algorithm_or_type>=<className>
        serviceName = k.Substring(0, j);
        algorithm = k.Substring(j + 1);
        if (mPropertyServiceTable != NULL) {
            AutoPtr<ICharSequence> keyObj;
            CString::New(Key(serviceName, algorithm), (ICharSequence**)&keyObj);
            AutoPtr<IProviderService> ser;
            mPropertyServiceTable->Remove(keyObj, (IInterface**)&ser);
            AutoPtr<IList> aliases;
            if (ser != NULL && mPropertyAliasTable != NULL
                    && (ser->GetAliases((IList**)&aliases), aliases != NULL)) {
                AutoPtr<IIterator> it;
                aliases->GetIterator((IIterator**)&it);
                Boolean hasNext;
                while (it->HasNext(&hasNext), hasNext) {
                    AutoPtr<IInterface> strObj;
                    it->GetNext((IInterface**)&strObj);
                    String alias;
                    ICharSequence::Probe(strObj)->ToString(&alias);
                    AutoPtr<ICharSequence> keyObj;
                    CString::New(Key(serviceName, alias), (ICharSequence**)&keyObj);
                    mPropertyAliasTable->Remove(keyObj);
                }
            }
        }
    }
    else {
        // <crypto_service>.<algorithm_or_type>
        // <attribute_name>=<attrValue>
        attribute = k.Substring(i + 1);
        serviceName = k.Substring(0, j);
        algorithm = k.Substring(j + 1, i);
        if (mPropertyServiceTable != NULL) {
            AutoPtr<ICharSequence> keyObj;
            CString::New(Key(serviceName, algorithm), (ICharSequence**)&keyObj);
            AutoPtr<IInterface> o;
            mPropertyServiceTable->Get(keyObj, (IInterface**)&o);
            if (o != NULL) {
                s = IProviderService::Probe(o);
                AutoPtr<IMap> attributes;
                s->GetAttributes((IMap**)&attributes);
                AutoPtr<ICharSequence> keyObj;
                CString::New(attribute, (ICharSequence**)&keyObj);
                attributes->Remove(keyObj);
            }
        }
    }
}