/*! Return the parameters relevant to the creation of this QOrganizerManager
  \since 1.1
*/
QMap<QString, QString> QOrganizerManager::managerParameters() const
{
    QMap<QString, QString> params = d->m_engine->managerParameters();

    params.remove(QString::fromAscii(QTORGANIZER_VERSION_NAME));
    params.remove(QString::fromAscii(QTORGANIZER_IMPLEMENTATION_VERSION_NAME));
    return params;
}