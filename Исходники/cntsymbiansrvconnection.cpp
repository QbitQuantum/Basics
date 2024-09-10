/*!
 * The leaving function that queries the SQL database
 * 
 * \a aSqlQuery An SQL query
 * \return the list of matched contact ids and phonenumber values
 */
QList<QPair<QContactLocalId, QString> > CntSymbianSrvConnection::searchPhoneNumbersL(const TDesC& aSqlQuery, QueryType aQueryType)
{
    readContactsToBufferL(aSqlQuery, aQueryType);

    RBufReadStream readStream;
    QList<QPair<QContactLocalId, QString> > list;
    TInt item;
    TBuf<256> extraValue;
    
    readStream.Open(*m_buffer);
    while ((item = readStream.ReadInt32L()) != 0) {
        readStream >> extraValue;
        QContactLocalId id = item;
        list.append(qMakePair(id,QString::fromUtf16(extraValue.Ptr(), extraValue.Length())));
    }

    return list;
}