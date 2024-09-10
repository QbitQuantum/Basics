void SenderIdentitiesModel::saveToSettings(QSettings &s) const
{
    s.beginWriteArray(Common::SettingsNames::identitiesKey);
    for (int i = 0; i < m_identities.size(); ++i) {
        s.setArrayIndex(i);
        s.setValue(Common::SettingsNames::realNameKey, m_identities[i].realName);
        s.setValue(Common::SettingsNames::addressKey, m_identities[i].emailAddress);
        s.setValue(Common::SettingsNames::organisationKey, m_identities[i].organisation);
        s.setValue(Common::SettingsNames::signatureKey, m_identities[i].signature);
    }
    s.endArray();
    s.remove(Common::SettingsNames::obsRealNameKey);
    s.remove(Common::SettingsNames::obsAddressKey);
}