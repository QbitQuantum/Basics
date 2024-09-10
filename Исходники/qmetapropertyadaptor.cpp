PropertyData QMetaPropertyAdaptor::propertyData(int index) const
{
    PropertyData data;
    if (!object().isValid())
        return data;

    m_notifyGuard = true;
    const auto mo = object().metaObject();
    Q_ASSERT(mo);

    const auto prop = mo->property(index);

    data.setName(prop.name());
    data.setTypeName(prop.typeName());

    auto pmo = mo;
    while (pmo->propertyOffset() > index)
        pmo = pmo->superClass();
    data.setClassName(pmo->className());

    switch (object().type()) {
    case ObjectInstance::QtObject:
        if (object().qtObject())
            data.setValue(prop.read(object().qtObject()));
        break;
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    case ObjectInstance::QtGadget:
        if (object().object())
            data.setValue(prop.readOnGadget(object().object()));
        break;
#endif
    default:
        break;
    }

    data.setDetails(detailString(prop));

    PropertyData::Flags flags = PropertyData::Readable;
    if (prop.isWritable())
        flags |= PropertyData::Writable;
    if (prop.isResettable())
        flags |= PropertyData::Resettable;
    data.setFlags(flags);

    m_notifyGuard = false;
    return data;
}