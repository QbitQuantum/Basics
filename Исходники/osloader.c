VOID
FwBuildLoaderBlock(
    VOID
    )
/*++

Routine Description:

    Build the ARM loader block by creating the memory map
    and setting the proper function descriptors for FreeLoader.

Arguments:

    None.
    
Return Value:

    None.

--*/

{

    memset(&ArmBlock, 0, sizeof(ARM_BOARD_CONFIGURATION_BLOCK));

    FwPrintf("Initializing freeldr loader block.\n");
    
    DebugTrace("ArmBlock is located at 0x%08x\n", &ArmBlock);

    //
    // Version number
    //

    ArmBlock.MajorVersion = ARM_BOARD_CONFIGURATION_MAJOR_VERSION;
    ArmBlock.MinorVersion = ARM_BOARD_CONFIGURATION_MINOR_VERSION;

    //
    // The board doesn't really exist.
    //
    
    ArmBlock.BoardType = 387;
    ArmBlock.ClockRate = 0;
    ArmBlock.UartRegisterBase = 0;
    ArmBlock.TimerRegisterBase = 0;

    //
    // Firmware functions
    //

    ArmBlock.ConsPutChar = FwFramebufferPutChar;
    ArmBlock.ConsKbHit = FwKbHit;
    ArmBlock.ConsGetCh = FwGetCh;
    ArmBlock.VideoClearScreen = FwClearScreen;
    ArmBlock.VideoPutChar = FwVideoPutChar;
    ArmBlock.VideoSetDisplayMode = FwVideoSetDisplayMode;
    ArmBlock.VideoGetDisplaySize = FwVideoGetDisplaySize;
    ArmBlock.VideoPutChar = FwVideoPutChar;
    ArmBlock.GetTime = FwGetTime;
    
    //
    // Build the memory map.
    //
    
    FwPrintf("Building loader memory map.\n");
    
    FwBuildMemoryMap();
    
    //
    // Load it.
    //
    
    ArmBlock.MemoryMap = MemoryMap;    
    
}