/**
 * @brief FilePersistence::modifyAccountObject
 * @param modifications
 * @return
 */
bool FilePersistence::modifyAccountObject(const OptionTable &modifications)
{
    int index = findAccountObj(modifications);
    if (index < 0) {
        m_error.append(QString("Could not modify Account object !\n"));
        m_error.append(QString("There is no such an Account object.\n"));
        return false;
    }
    QVariantMap modifyValues = variantMapFromOptionTable(modifications);
    if (modifications.contains('i')) {
        modifyValues.remove(optionToRealName('i'));
    } else {
        modifyValues.remove(optionToRealName('p'));
        modifyValues.remove(optionToRealName('u'));
    }
    QVariantMap originObject = m_fileContent[index];
    QStringList keyList = modifyValues.keys();
    for (int index=0; index<keyList.size(); ++index) {
        QVariant value = modifyValues.value(keyList[index]);
        originObject.insert(keyList[index], value);
    }
    m_isModified = true;

    return true;
}