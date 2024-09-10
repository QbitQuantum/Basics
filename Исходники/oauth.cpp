QByteArray Oauth::HmacSha1(QString secretKey, QString data, QString tokenSecret)
{
    QString signingKey = QString("%1&%2").arg(Escape(secretKey),Escape(tokenSecret));

    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int resultlen = 0;
    HMAC(
         EVP_sha1(),
         qPrintable(signingKey),
         signingKey.toLocal8Bit().length(),
         (unsigned char*)data.toLocal8Bit().data(),
         data.toLocal8Bit().length(),
         result,
         &resultlen
         );
    char* cbase64 = base64(result,resultlen);
    QByteArray resultArray(cbase64);
    qDebug() << resultArray;
    resultArray = resultArray.toPercentEncoding();
    free(cbase64);
    return resultArray;
}