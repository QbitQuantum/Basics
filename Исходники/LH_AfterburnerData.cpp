bool LH_AfterburnerData::getData(float& value, QString& text, QString& units, QString& format, float& min, float& max, int index)
{
#ifdef Q_WS_WIN
    bool resultVal = false;

    HANDLE filemap = OpenFileMappingA(FILE_MAP_READ, FALSE, "MAHMSharedMemory");
    if(filemap != NULL)
    {
        MAHM_SHARED_MEMORY_HEADER* MAHMHeader = (MAHM_SHARED_MEMORY_HEADER*)MapViewOfFile(filemap, FILE_MAP_READ, 0, 0, 0);

        if (MAHMHeader)
        {
            if (MAHMHeader->dwSignature == 0xDEAD)
            {
                qDebug() << "LH_Afterburner: Shared memory has been terminated; try again later.";
            }
            else
            {
                if (ui_->count(mon_type) == 0) loadTypesList(MAHMHeader);
                getSelectedValue(MAHMHeader, value, text, units, format, min, max, index);
                resultVal = true;
            }
            UnmapViewOfFile(MAHMHeader);
        }
        CloseHandle(filemap);
    }
    ui_->setReadonly(mon_type | mon_item, !resultVal);
    return resultVal;
#else
    Q_UNUSED(value);
    Q_UNUSED(text);
    Q_UNUSED(units);
    Q_UNUSED(format);
    Q_UNUSED(min);
    Q_UNUSED(max);
    Q_UNUSED(index);
    return false;
#endif
}