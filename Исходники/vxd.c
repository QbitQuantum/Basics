LONG
    VcdPmGetPortArray(
        VOID
    )
/*++

Routine Description:

    Use the registry enteries in HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM
    to simulate the Virtual Comm Device API: VCD_PM_Get_Port_Array. See VCD.ASM
    in the Win 3.1 DDK.


Arguments:

    None

Return Value:

    Port Array in LOWORD. Bit array of valid ports:

    Bit Set   -> Port valid
    Bit clear -> Port invalid

    Bit 0 -> COM1, Bit 1 -> COM2, Bit 2 -> COM3...

--*/
{
    HKEY        hSerialCommKey;
    DWORD       dwPortArray;
    DWORD       dwPortNum;
    DWORD       cbPortName;
    DWORD       cbPortValue;
    CHAR        szPortName[16];
    CHAR        szPortValue[16];
    LONG        iPort;
    LONG        iStatus;

    dwPortArray = 0;
    if (RegOpenKeyEx (HKEY_LOCAL_MACHINE,
                      "HARDWARE\\DEVICEMAP\\SERIALCOMM",
                      0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS,
                      &hSerialCommKey) == ERROR_SUCCESS){

        cbPortName  = sizeof(szPortName);
        cbPortValue = sizeof(szPortValue);
        for (iPort = 0;
             (iStatus = RegEnumValue(hSerialCommKey,
                                     iPort, szPortName, &cbPortName,
                                     NULL, NULL, szPortValue,
                                     &cbPortValue)) != ERROR_NO_MORE_ITEMS;
             iPort++)
        {
            if ((iStatus == ERROR_SUCCESS) && (cbPortValue > 3)) {

                if (NT_SUCCESS(RtlCharToInteger(szPortValue+3,10,&dwPortNum))) {
                    dwPortArray |= (1 << (dwPortNum - 1));
                }

            }
            cbPortName  = sizeof(szPortName);
            cbPortValue = sizeof(szPortValue);
        }
    // WOW only supports 9 ports. See WU32OPENCOM in WUCOMM.C.
    dwPortArray &= 0x1FF;
    RegCloseKey(hSerialCommKey);
    }
    return(dwPortArray);
}