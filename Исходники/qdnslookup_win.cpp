QT_BEGIN_NAMESPACE

void QDnsLookupRunnable::query(const int requestType, const QByteArray &requestName, QDnsLookupReply *reply)
{
    // Perform DNS query.
    PDNS_RECORD dns_records = 0;
    const QString requestNameUtf16 = QString::fromUtf8(requestName.data(), requestName.size());
    const DNS_STATUS status = DnsQuery_W(reinterpret_cast<const wchar_t*>(requestNameUtf16.utf16()), requestType, DNS_QUERY_STANDARD, NULL, &dns_records, NULL);
    switch (status) {
    case ERROR_SUCCESS:
        break;
    case DNS_ERROR_RCODE_FORMAT_ERROR:
        reply->error = QDnsLookup::InvalidRequestError;
        reply->errorString = tr("Server could not process query");
        return;
    case DNS_ERROR_RCODE_SERVER_FAILURE:
        reply->error = QDnsLookup::ServerFailureError;
        reply->errorString = tr("Server failure");
        return;
    case DNS_ERROR_RCODE_NAME_ERROR:
        reply->error = QDnsLookup::NotFoundError;
        reply->errorString = tr("Non existent domain");
        return;
    case DNS_ERROR_RCODE_REFUSED:
        reply->error = QDnsLookup::ServerRefusedError;
        reply->errorString = tr("Server refused to answer");
        return;
    default:
        reply->error = QDnsLookup::InvalidReplyError;
        reply->errorString = QSystemError(status, QSystemError::NativeError).toString();
        return;
    }

    // Extract results.
    for (PDNS_RECORD ptr = dns_records; ptr != NULL; ptr = ptr->pNext) {
        const QString name = QUrl::fromAce( QString::fromWCharArray( ptr->pName ).toLatin1() );
        if (ptr->wType == QDnsLookup::A) {
            QDnsHostAddressRecord record;
            record.d->name = name;
            record.d->timeToLive = ptr->dwTtl;
            record.d->value = QHostAddress(ntohl(ptr->Data.A.IpAddress));
            reply->hostAddressRecords.append(record);
        } else if (ptr->wType == QDnsLookup::AAAA) {
            Q_IPV6ADDR addr;
            memcpy(&addr, &ptr->Data.AAAA.Ip6Address, sizeof(Q_IPV6ADDR));

            QDnsHostAddressRecord record;
            record.d->name = name;
            record.d->timeToLive = ptr->dwTtl;
            record.d->value = QHostAddress(addr);
            reply->hostAddressRecords.append(record);
        } else if (ptr->wType == QDnsLookup::CNAME) {
            QDnsDomainNameRecord record;
            record.d->name = name;
            record.d->timeToLive = ptr->dwTtl;
            record.d->value = QUrl::fromAce(QString::fromWCharArray(ptr->Data.Cname.pNameHost).toLatin1());
            reply->canonicalNameRecords.append(record);
        } else if (ptr->wType == QDnsLookup::MX) {
            QDnsMailExchangeRecord record;
            record.d->name = name;
            record.d->exchange = QUrl::fromAce(QString::fromWCharArray(ptr->Data.Mx.pNameExchange).toLatin1());
            record.d->preference = ptr->Data.Mx.wPreference;
            record.d->timeToLive = ptr->dwTtl;
            reply->mailExchangeRecords.append(record);
        } else if (ptr->wType == QDnsLookup::NS) {
            QDnsDomainNameRecord record;
            record.d->name = name;
            record.d->timeToLive = ptr->dwTtl;
            record.d->value = QUrl::fromAce(QString::fromWCharArray(ptr->Data.Ns.pNameHost).toLatin1());
            reply->nameServerRecords.append(record);
        } else if (ptr->wType == QDnsLookup::PTR) {
            QDnsDomainNameRecord record;
            record.d->name = name;
            record.d->timeToLive = ptr->dwTtl;
            record.d->value = QUrl::fromAce(QString::fromWCharArray(ptr->Data.Ptr.pNameHost).toLatin1());
            reply->pointerRecords.append(record);
        } else if (ptr->wType == QDnsLookup::SRV) {
            QDnsServiceRecord record;
            record.d->name = name;
            record.d->target = QUrl::fromAce(QString::fromWCharArray(ptr->Data.Srv.pNameTarget).toLatin1());
            record.d->port = ptr->Data.Srv.wPort;
            record.d->priority = ptr->Data.Srv.wPriority;
            record.d->timeToLive = ptr->dwTtl;
            record.d->weight = ptr->Data.Srv.wWeight;
            reply->serviceRecords.append(record);
        } else if (ptr->wType == QDnsLookup::TXT) {
            QDnsTextRecord record;
            record.d->name = name;
            record.d->timeToLive = ptr->dwTtl;
            for (unsigned int i = 0; i < ptr->Data.Txt.dwStringCount; ++i) {
                record.d->values << QString::fromWCharArray((ptr->Data.Txt.pStringArray[i])).toLatin1();;
            }
            reply->textRecords.append(record);
        }
    }

    DnsRecordListFree(dns_records, DnsFreeRecordList);
}