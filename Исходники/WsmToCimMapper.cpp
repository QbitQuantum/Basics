void testSimpleType(const T& x)
{
    WsmToCimRequestMapper mapper((CIMRepository*) 0);

    // Create a NULL CIMValue of the appropriate type. Normally type
    // info is retrieved from the repository.
    CIMValue tmp(x);
    CIMValue cimValue(tmp.getType(), tmp.isArray());
    String str = tmp.toString();
    if (tmp.getType() == CIMTYPE_BOOLEAN)
    {
        str.toLower();
    }
    WsmValue wsmValue(str);
    mapper.convertWsmToCimValue(wsmValue, CIMNamespaceName(), cimValue);
    PEGASUS_TEST_ASSERT(tmp == cimValue);
}