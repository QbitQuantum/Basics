bool LH_SpeedFanData::getData(float& value, QString& text, QString& units, int& count, int index)
{
#ifdef Q_WS_WIN
    bool resultVal = false;

    HANDLE filemap = OpenFileMappingA(FILE_MAP_READ, FALSE, "SFSharedMemory_ALM");
    if(filemap != NULL)
    {
        SFMemory* sfmemory = (SFMemory*)MapViewOfFile(filemap, FILE_MAP_READ, 0, 0, sizeof(SFMemory));
        if (sfmemory)
        {
            if(sfmemory->MemSize!=0)
            {
                if (ui_->count(mon_item) == 0)
                    loadSensorList(sfmemory);
                getSelectedValue(sfmemory, value, text, units, count, index);
                resultVal = true;
            }
            UnmapViewOfFile(sfmemory);
        }
        CloseHandle(filemap);
    }
    ui_->setReadonly(mon_type | mon_item, !resultVal);
    return resultVal;
#else
    Q_UNUSED(value);
    Q_UNUSED(text);
    Q_UNUSED(units);
    Q_UNUSED(count);
    Q_UNUSED(index);
    return false;
#endif
}