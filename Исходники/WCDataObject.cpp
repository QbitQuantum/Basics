WCDataObject::~WCDataObject()
{
    for(size_t i = 0; i < m_medium.size(); ++i) {
        ReleaseStgMedium(m_medium[i]);
        delete m_medium[i];
    }
    WTF::deleteAllValues(m_formats);
}