void TautoPresetProps::getVolume(void)
{
    const char_t *flnm=deci->getSourceName();
    char_t dsk[MAX_PATH];
    _splitpath_s(flnm,dsk,MAX_PATH,NULL,0,NULL,0,NULL,0);
    DWORD serial,maximumComponentLength,volumeFlags;
    ffstring disk(dsk);
    disk += _l("\\");
    wasVolume=GetVolumeInformation(disk.c_str(),volumeName,256,&serial,&maximumComponentLength,&volumeFlags,NULL,0);
    if (wasVolume) {
        tsnprintf_s(volumeSerial, countof(volumeSerial), _TRUNCATE, _l("%X-%X"),(int)HIWORD(serial),(int)LOWORD(serial));
    }
}