QString QNPutExtraPrivate::remove(const QString &key)
{
    QString value;
    if(m_params.contains(key))
    {
        value = m_params.value(key);
        m_params.remove(key);
    }
    return value;
}