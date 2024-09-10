QDbfRecord QDbfTablePrivate::record() const
{
    if (m_bufered) {
        return m_currentRecord;
    }

    m_currentRecord = m_record;
    m_bufered = true;

    if (m_currentIndex < QDbfTablePrivate::FirstRow) {
        return m_currentRecord;
    }

    if (!isOpen()) {
        qWarning("QDbfTablePrivate::record(): IODevice is not open");
        return m_currentRecord;
    }

    if (!m_file.isReadable()) {
        m_error = QDbfTable::ReadError;
        return m_currentRecord;
    }

    const qint64 position = m_headerLength + m_recordLength * m_currentIndex;

    if (!m_file.seek(position)) {
        m_error = QDbfTable::ReadError;
        return m_currentRecord;
    }

    m_currentRecord.setRecordIndex(m_currentIndex);

    const QByteArray recordData = m_file.read(m_recordLength);

    if (recordData.count() == 0) {
        m_error = QDbfTable::UnspecifiedError;
        return m_currentRecord;
    }

    m_currentRecord.setDeleted(recordData.at(0) == '*' ? true : false);

    for (int i = 0; i < m_currentRecord.count(); ++i) {
        const QByteArray byteArray = recordData.mid(m_currentRecord.field(i).offset(),
                                                    m_currentRecord.field(i).length());
        QVariant value;
        switch (m_currentRecord.field(i).type()) {
        case QVariant::String:
            value = m_textCodec->toUnicode(byteArray);
            break;
        case QVariant::Date:
            value = QVariant(QDate(byteArray.mid(0, 4).toInt(),
                                   byteArray.mid(4, 2).toInt(),
                                   byteArray.mid(6, 2).toInt()));
            break;
        case QVariant::Double:
            value = byteArray.toDouble();
            break;
        case QVariant::Bool: {
            QString val = QString::fromLatin1(byteArray.toUpper());
            if (val == QLatin1String("T") ||
                val == QLatin1String("Y")) {
                value = true;
            } else {
                value = false;
            }
            break; }
        default:
            value = QVariant::Invalid;
        }

        m_currentRecord.setValue(i, value);
    }

    m_error = QDbfTable::NoError;

    return m_currentRecord;
}