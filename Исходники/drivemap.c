VOID DriveMapInstallInt13Handler(PDRIVE_MAP_LIST DriveMap)
{
    ULONG*  RealModeIVT = (ULONG*)UlongToPtr(0x00000000);
    USHORT* BiosLowMemorySize = (USHORT*)ULongToPtr(0x00000413);

    if (!DriveMapInstalled)
    {
        // Get the old INT 13h handler address from the vector table
        OldInt13HandlerAddress = RealModeIVT[0x13];

        // Decrease the size of low memory
        (*BiosLowMemorySize)--;

        // Get linear address for drive map handler
        DriveMapHandlerAddress = (ULONG)(*BiosLowMemorySize) << 10;

        // Convert to segment:offset style address
        DriveMapHandlerSegOff = (DriveMapHandlerAddress << 12) & 0xffff0000;
    }

    // Copy the drive map structure to the proper place
    RtlCopyMemory(&DriveMapInt13HandlerMapList, DriveMap, sizeof(DRIVE_MAP_LIST));

    // Set the address of the BIOS INT 13h handler
    DriveMapOldInt13HandlerAddress = OldInt13HandlerAddress;

    // Copy the code to our reserved area
    RtlCopyMemory(UlongToPtr(DriveMapHandlerAddress),
                  &DriveMapInt13HandlerStart,
                  ((PUCHAR)&DriveMapInt13HandlerEnd - (PUCHAR)&DriveMapInt13HandlerStart));

    // Update the IVT
    RealModeIVT[0x13] = DriveMapHandlerSegOff;

    CacheInvalidateCacheData();
    DriveMapInstalled = TRUE;
}