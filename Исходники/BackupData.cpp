status_t
BackupDataWriter::WriteEntityHeader(const String8& key, size_t dataSize)
{
    if (m_status != NO_ERROR) {
        return m_status;
    }

    ssize_t amt;

    amt = write_padding_for(m_pos);
    if (amt != 0) {
        return amt;
    }

    String8 k;
    if (m_keyPrefix.length() > 0) {
        k = m_keyPrefix;
        k += ":";
        k += key;
    } else {
        k = key;
    }
    if (DEBUG) {
        ALOGD("Writing header: prefix='%s' key='%s' dataSize=%d", m_keyPrefix.string(),
                key.string(), dataSize);
    }

    entity_header_v1 header;
    ssize_t keyLen;

    keyLen = k.length();

    header.type = tolel(BACKUP_HEADER_ENTITY_V1);
    header.keyLen = tolel(keyLen);
    header.dataSize = tolel(dataSize);

    if (DEBUG) ALOGI("writing entity header, %d bytes", sizeof(entity_header_v1));
    amt = write(m_fd, &header, sizeof(entity_header_v1));
    if (amt != sizeof(entity_header_v1)) {
        m_status = errno;
        return m_status;
    }
    m_pos += amt;

    if (DEBUG) ALOGI("writing entity header key, %ld bytes", keyLen+1);
    amt = write(m_fd, k.string(), keyLen+1);
    if (amt != keyLen+1) {
        m_status = errno;
        return m_status;
    }
    m_pos += amt;

    amt = write_padding_for(keyLen+1);

    m_entityCount++;

    return amt;
}