/**
    Internal helper function.

    Update the BBS Table so that devices of DeviceType have their boot priority
    updated to a high/bootable value.

    See "DeviceType values" in 
    http://www.intel.com/content/dam/doc/reference-guide/efi-compatibility-support-module-specification-v097.pdf

    NOTE: This function should probably be refactored! Currently, all devices of
    type are enabled. This should be updated so that only a specific device is
    enabled. The wrong device could boot if there are multiple targets of the same
    type.

    @param DeviceType   The device type that we wish to enable
**/
VOID UpdateBbsTable (BDS_COMMON_OPTION *Option) {
   UINT16  Idx;
   EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
   EFI_STATUS                Status;
   UINT16                       HddCount = 0;
   HDD_INFO                     *HddInfo = NULL; 
   UINT16                       BbsCount = 0; 
   BBS_TABLE                 *LocalBbsTable = NULL;
   BBS_BBS_DEVICE_PATH       *OptionBBS;
   CHAR16                    Desc[100];

   Status = refit_call3_wrapper(gBS->LocateProtocol, &gEfiLegacyBootProtocolGuid, NULL, (VOID **) &LegacyBios);
   if (EFI_ERROR (Status) || (Option == NULL)) {
      return;
   }

   OptionBBS = (BBS_BBS_DEVICE_PATH *) Option->DevicePath;
   Status = refit_call5_wrapper(LegacyBios->GetBbsInfo, LegacyBios, &HddCount, &HddInfo, &BbsCount, &LocalBbsTable);

//    Print (L"\n");
//    Print (L" NO  Prio bb/dd/ff cl/sc Type Stat segm:offs\n");
//    Print (L"=============================================\n");

   for (Idx = 0; Idx < BbsCount; Idx++) {
      if(LocalBbsTable[Idx].DeviceType == 0) {
         continue;
      }

      BdsBuildLegacyDevNameString (&LocalBbsTable[Idx], Idx, sizeof (Desc), Desc);

      // Set devices of a particular type to BootPriority of 0 or 1. 0 is the highest priority.
      if (LocalBbsTable[Idx].DeviceType == OptionBBS->DeviceType) {
         if (StriCmp(Desc, Option->Description) == 0) {
            // This entry exactly matches what we're looking for; make it highest priority
            LocalBbsTable[Idx].BootPriority = 0;
         } else {
            // This entry doesn't exactly match, but is the right disk type; make it a bit lower
            // in priority. Done mainly as a fallback in case of string-matching weirdness.
            LocalBbsTable[Idx].BootPriority = 1;
         } // if/else
      } else if (LocalBbsTable[Idx].BootPriority <= 1) {
         // Something's got a high enough boot priority to interfere with booting
         // our chosen entry, so bump it down a bit....
         LocalBbsTable[Idx].BootPriority = 2;
      } // if/else if

//          Print (
//            L" %02x: %04x %02x/%02x/%02x %02x/%02x %04x %04x %04x:%04x\n",
//            (UINTN) Idx,
//            (UINTN) LocalBbsTable[Idx].BootPriority,
//            (UINTN) LocalBbsTable[Idx].Bus,
//            (UINTN) LocalBbsTable[Idx].Device,
//            (UINTN) LocalBbsTable[Idx].Function,
//            (UINTN) LocalBbsTable[Idx].Class,
//            (UINTN) LocalBbsTable[Idx].SubClass,
//            (UINTN) LocalBbsTable[Idx].DeviceType,
//            (UINTN) * (UINT16 *) &LocalBbsTable[Idx].StatusFlags,
//            (UINTN) LocalBbsTable[Idx].BootHandlerSegment,
//            (UINTN) LocalBbsTable[Idx].BootHandlerOffset,
//            (UINTN) ((LocalBbsTable[Idx].MfgStringSegment << 4) + LocalBbsTable[Idx].MfgStringOffset),
//            (UINTN) ((LocalBbsTable[Idx].DescStringSegment << 4) + LocalBbsTable[Idx].DescStringOffset)
//            );
//          Print(L"%s\n", Desc);

   } // for
//    PauseForKey();
}