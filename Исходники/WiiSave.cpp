bool WiiSave::saveToFile(const std::string& filepath, Uint8* macAddress, Uint32 ngId, Uint8* ngPriv, Uint8* ngSig, Uint32 ngKeyId)
{
    m_writer = new BinaryWriter(filepath);
    m_writer->setAutoResizing(true);
    m_writer->setEndianess(Stream::BigEndian);

    writeBanner();

    m_writer->writeUInt32(0x70);
    m_writer->writeUInt32(0x426B0001);
    m_writer->writeUInt32(ngId); // NG-ID
    m_writer->writeUInt32(m_files.size());
    m_writer->writeUInt32(0); // Size of files;
    m_writer->seek(8);
    m_writer->writeUInt32(0); // totalSize
    m_writer->seek(64);
    m_writer->writeUInt64(m_banner->gameID());
    m_writer->writeBytes((Int8*)macAddress, 6);
    m_writer->seek(2); // unknown;
    m_writer->seek(0x10); // padding;
    Uint32 totalSize = 0;
    for (std::map<std::string, WiiFile*>::const_iterator iter = m_files.begin(); iter != m_files.end(); ++iter)
    {
        totalSize += writeFile(iter->second);
    }
    int pos = m_writer->position();
    // Write size data
    m_writer->seek(0xF0C0 + 0x10, Stream::Beginning);
    m_writer->writeUInt32(totalSize);
    m_writer->seek(0xF0C0 + 0x1C, Stream::Beginning);
    m_writer->writeUInt32(totalSize + 0x3c0);
    m_writer->seek(pos, Stream::Beginning);

    writeCerts(totalSize, ngId, ngPriv, ngSig, ngKeyId);

    m_writer->save();

    return true;
}