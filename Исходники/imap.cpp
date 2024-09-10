QByteArray ImapPrivate::hmacMd5 (const QString& username,
                                 const QString& password,
                                 const QString& serverResponse)
{
    QByteArray passwordBytes = password.toLatin1();
    QByteArray ipad(64, 0);
    QByteArray opad(64, 0);
    
    for (int i = 0; i < 64; ++i) {
        if (i < passwordBytes.size()) {
            ipad[i] = (quint8)(0x36 ^ passwordBytes[i]);
            opad[i] = (quint8)(0x5c ^ passwordBytes[i]);
        } else {
            ipad[i] = 0x36;
            opad[i] = 0x5c;
        }
    }

    QByteArray serverResponseBytes = serverResponse.toLatin1();
    while (serverResponseBytes[0] == '+' || serverResponseBytes[0] == ' ')
        serverResponseBytes.remove(0, 1);
        
    QCryptographicHash md5hash(QCryptographicHash::Md5);
    md5hash.addData(ipad);
    md5hash.addData(serverResponseBytes);
    QByteArray resultIpad = md5hash.result();
    
    md5hash.reset();
    md5hash.addData(opad);
    md5hash.addData(resultIpad);
    QByteArray resultOpad = md5hash.result();
    
    QByteArray response = username.toLatin1() + ' ' + resultOpad.toHex();
    return(response.toBase64());
}