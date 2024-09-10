PropertyData DynamicPropertyAdaptor::propertyData(int index) const
{
    PropertyData data;
    if (!object().isValid())
        return data;

    Q_ASSERT(m_propNames.size() == object().qtObject()->dynamicPropertyNames().size());

    data.setName(m_propNames.at(index));
    data.setValue(object().qtObject()->property(m_propNames.at(index)));
    data.setClassName(tr("<dynamic>"));
    data.setFlags(PropertyData::Writable | PropertyData::Deletable);
    return data;
}