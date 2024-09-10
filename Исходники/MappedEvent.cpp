void DataBlockFile::addDataByte(MidiByte byte)
{
    prepareToWrite();
    m_file.putChar(byte);
}