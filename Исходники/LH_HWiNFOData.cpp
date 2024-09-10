bool LH_HWiNFOData::getData(float& value, QString& text, QString& units)
{
#ifdef Q_WS_WIN
    const char* mapname  = HWiNFO_SENSORS_MAP_FILE_NAME;
    float resultVal = true;

    // Create file mapping
    HANDLE filemap = OpenFileMappingA(FILE_MAP_READ, FALSE, mapname);
    // Get pointer
    if(filemap != NULL)
    {
        _HWiNFO_SENSORS_SHARED_MEM* hwinfoMemory = (_HWiNFO_SENSORS_SHARED_MEM*)MapViewOfFile(filemap, FILE_MAP_READ, 0, 0, sizeof(_HWiNFO_SENSORS_SHARED_MEM));
        if (hwinfoMemory)
        {
            if(hwinfoMemory->header.dwVersion!=3)
            {
                qWarning() << "LH_Monitoring: HWiNFO version is incompatible.";
                return false;
            }

            if (ui_->count(mon_type) == 0)
                loadTypesList(hwinfoMemory);

            if(ui_->value(mon_type)!=-1)
            {
                if (ui_->value(mon_type) != listedType_)
                {
                    listedType_ = ui_->value(mon_type);
                    listedGroup_ = -1;
                    loadGroupsList(hwinfoMemory);
                }
                if(ui_->value(mon_group)!=-1)
                {
                    int max = -1;
                    HWiNFO_SENSORS_READING_LIST *list = getList(hwinfoMemory->Sensors[sensor_indexes_.value(ui_->value(mon_group))], max);

                    if (ui_->value(mon_group) != listedGroup_)
                    {
                        listedGroup_ = ui_->value(mon_group);
                        loadItemsList(list, max);
                    }

                    getSelectedValue(list, value, text, units);
                } else
                    resultVal = false;
            } else
                resultVal = false;
            UnmapViewOfFile(hwinfoMemory);
        } else
            resultVal = false;
        CloseHandle(filemap);
    } else
        resultVal = false;
    return resultVal;
#else
    Q_UNUSED(value);
    Q_UNUSED(text);
    Q_UNUSED(units);
    return false;
#endif
}