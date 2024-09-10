 bool Wagnis::isSignatureValid(const QString &content, const QString &signature)
 {
     qDebug() << "Wagnis::isSignatureValid";
     RSA* publicRSA = createPublicRSA(PUBLIC_KEY);
     QByteArray signatureigBase64 = signature.toLatin1();
     QByteArray rawData = QByteArray::fromBase64(signatureigBase64);
     bool authentic;
     bool result = verifySignature(publicRSA, reinterpret_cast<unsigned char*>(rawData.data()), rawData.length(), content.toStdString().c_str(), content.toStdString().length(), &authentic);
     return authentic & result;
 }