void CSendLogSerializer::LoadMap(MemoryBuffer& rawdata,StringBuffer& GUID, StringBuffer& line)
{
    line.append(rawdata.length() -1, rawdata.toByteArray());
    const char* strLine = line.str();
    while(*strLine && *strLine != '\t' && *strLine != '\0')
    {
        GUID.append(*strLine);
        strLine++;
    }
}