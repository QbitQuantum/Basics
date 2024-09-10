CIMInstance ObjectNormalizer::processInstance(
    const CIMInstance& cimInstance) const
{
    // pre-checks
    if (!_enableNormalization || _cimClass.isUninitialized())
    {
        // do nothing
        return cimInstance;
    }

    /*
    // ATTN: moving similar logic to the response handlers because this
    // type of error should be checked regardless with or without
    // normalization enabled.
    if (cimInstance.isUninitialized())
    {
        throw CIMException(CIM_ERR_FAILED, "unintialized instance object.");
    }
    */

    CIMInstance normalizedInstance(_cimClass.getClassName());

    // proces object path
    normalizedInstance.setPath(
        processInstanceObjectPath(cimInstance.getPath()));

    // process instance qualifiers
    if (_includeQualifiers)
    {
        // propagate class qualifiers
        for (Uint32 i = 0, n = _cimClass.getQualifierCount(); i < n; i++)
        {
            CIMConstQualifier referenceQualifier = _cimClass.getQualifier(i);

            Uint32 pos =
                cimInstance.findQualifier(referenceQualifier.getName());

            // update value if qualifier is present in the specified property
            if (pos != PEG_NOT_FOUND)
            {
                CIMConstQualifier cimQualifier = cimInstance.getQualifier(pos);

                CIMQualifier normalizedQualifier =
                    _processQualifier(
                        referenceQualifier,
                        cimQualifier);

                normalizedInstance.addQualifier(normalizedQualifier);
            }
            else
            {
                normalizedInstance.addQualifier(referenceQualifier.clone());
            }
        }
    }

    // check property names and types. any properties in the class but not
    // in the instance are implicitly dropped.
    for (Uint32 i = 0, n = cimInstance.getPropertyCount(); i < n; i++)
    {
        CIMConstProperty instProperty = cimInstance.getProperty(i);

        Uint32 pos = _cimClass.findProperty(instProperty.getName());

        if (pos != PEG_NOT_FOUND)
        {
            CIMConstProperty cimProperty = _cimClass.getProperty(pos);

            CIMProperty normalizedProperty =
                processProperty(
                    cimProperty,
                    instProperty,
                    _includeQualifiers,
                    _includeClassOrigin,
                    _context.get(),
                    _nameSpace);

            normalizedInstance.addProperty(normalizedProperty);
        }
    }

    return normalizedInstance;
}