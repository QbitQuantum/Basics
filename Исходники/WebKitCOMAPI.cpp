static COMPtr<IClassFactory> classFactory(const CLSID& clsid)
{
    typedef HashMap<CLSID, COMPtr<IClassFactory>, CLSIDHash, CLSIDHashTraits> FactoryMap;
    static FactoryMap& factories = *new FactoryMap;

    pair<FactoryMap::iterator, bool> result = factories.add(clsid, 0);
    COMPtr<IClassFactory>& factory = result.first->second;
    bool added = result.second;
    if (added && FAILED(DllGetClassObject(clsid, __uuidof(factory), reinterpret_cast<void**>(&factory))))
        factory = 0;

    return factory;
}