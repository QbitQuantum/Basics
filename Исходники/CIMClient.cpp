CIMInstance CIMClient::getInstance(
    const CIMNamespaceName& nameSpace,
    const CIMObjectPath& instanceName,
    Boolean localOnly,
    Boolean includeQualifiers,
    Boolean includeClassOrigin,
    const CIMPropertyList& propertyList)
{
    CIMInstance inst = _rep->getInstance(
        nameSpace,
        instanceName,
        localOnly,
        includeQualifiers,
        includeClassOrigin,
        propertyList).getInstance();

    if (!inst.isUninitialized())
    {
        // remove key bindings, name space and host name form object path.
        CIMObjectPath& p =
            const_cast<CIMObjectPath&>(inst.getPath());

        CIMName cls = p.getClassName();
        p.clear();
        p.setClassName(cls);

    }

    return inst;
}