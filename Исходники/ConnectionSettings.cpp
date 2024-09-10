QString UnprotectPassword(const QString & s)
{
    if (s.isEmpty()) {
        return QString();
    }
    QByteArray ba64 = QByteArray::fromStdString(s.toStdString());
    QByteArray ba = QByteArray::fromBase64(ba64);    
    DATA_BLOB db;
    db.cbData = static_cast<DWORD>(ba.size());
    db.pbData = (BYTE*)(ba.data());
    DATA_BLOB rdb;
    if (!CryptUnprotectData(&db, nullptr, nullptr, nullptr, nullptr, 0, &rdb)) {
        throw adbook::HrError(HRESULT_FROM_WIN32(GetLastError()),
            L"CryptUnprotectData() failed.", __FUNCTIONW__
        );
    }    
    QString ret = QString::fromWCharArray((const wchar_t*)rdb.pbData, rdb.cbData/sizeof(wchar_t));
    LocalFree(rdb.pbData);
    return ret;
}