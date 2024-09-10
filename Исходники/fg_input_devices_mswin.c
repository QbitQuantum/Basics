void fgPlatformRegisterDialDevice ( const char *dial_device )
{
        if (!dial_device){
            static char devname[256];
            DWORD size=sizeof(devname);
            DWORD type = REG_SZ;
            HKEY key;
            if (RegOpenKeyA(HKEY_LOCAL_MACHINE,"SOFTWARE\\FreeGLUT",&key)==ERROR_SUCCESS) {
                if (RegQueryValueExA(key,"DialboxSerialPort",NULL,&type,(LPBYTE)devname,&size)==ERROR_SUCCESS){
                    dial_device=devname;
                }
                RegCloseKey(key);
            }
        }
}