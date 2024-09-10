/**
  Extract the discover information and boot server entry from the
  cached packets if unspecified.

  @param[in]      Private      Pointer to PxeBc private data.
  @param[in]      Type         The type of bootstrap to perform.
  @param[in, out] DiscoverInfo Pointer to EFI_PXE_BASE_CODE_DISCOVER_INFO.
  @param[out]     BootEntry    Pointer to PXEBC_BOOT_SVR_ENTRY.
  @param[out]     SrvList      Pointer to EFI_PXE_BASE_CODE_SRVLIST.

  @retval EFI_SUCCESS       Successfully extracted the information.
  @retval EFI_DEVICE_ERROR  Failed to extract the information.

**/
EFI_STATUS
PxeBcExtractDiscoverInfo (
  IN     PXEBC_PRIVATE_DATA               *Private,
  IN     UINT16                           Type,
  IN OUT EFI_PXE_BASE_CODE_DISCOVER_INFO  **DiscoverInfo,
     OUT PXEBC_BOOT_SVR_ENTRY             **BootEntry,
     OUT EFI_PXE_BASE_CODE_SRVLIST        **SrvList
  )
{
  EFI_PXE_BASE_CODE_MODE          *Mode;
  PXEBC_DHCP4_PACKET_CACHE        *Cache4;
  PXEBC_VENDOR_OPTION             *VendorOpt;
  PXEBC_BOOT_SVR_ENTRY            *Entry;
  BOOLEAN                         IsFound;
  EFI_PXE_BASE_CODE_DISCOVER_INFO *Info;
  UINT16                          Index;

  Mode = Private->PxeBc.Mode;
  Info = *DiscoverInfo;

  if (Mode->UsingIpv6) {
    Info->IpCnt    = 1;
    Info->UseUCast = TRUE;

    Info->SrvList[0].Type              = Type;
    Info->SrvList[0].AcceptAnyResponse = FALSE;

    //
    // There is no vendor options specified in DHCPv6, so take BootFileUrl in the last cached packet.
    //
    CopyMem (&Info->SrvList[0].IpAddr, &Private->ServerIp, sizeof (EFI_IP_ADDRESS));

    *SrvList  = Info->SrvList;
  } else {
    Entry     = NULL;
    IsFound   = FALSE;
    Cache4    = (Mode->ProxyOfferReceived) ? &Private->ProxyOffer.Dhcp4 : &Private->DhcpAck.Dhcp4;
    VendorOpt = &Cache4->VendorOpt;

    if (!Mode->DhcpAckReceived || !IS_VALID_DISCOVER_VENDOR_OPTION (VendorOpt->BitMap)) {
      //
      // Address is not acquired or no discovery options.
      //
      return EFI_INVALID_PARAMETER;
    }

    //
    // Parse the boot server entry from the vendor option in the last cached packet.
    //
    Info->UseMCast    = (BOOLEAN) !IS_DISABLE_MCAST_DISCOVER (VendorOpt->DiscoverCtrl);
    Info->UseBCast    = (BOOLEAN) !IS_DISABLE_BCAST_DISCOVER (VendorOpt->DiscoverCtrl);
    Info->MustUseList = (BOOLEAN) IS_ENABLE_USE_SERVER_LIST (VendorOpt->DiscoverCtrl);
    Info->UseUCast    = (BOOLEAN) IS_VALID_BOOT_SERVERS (VendorOpt->BitMap);

    if (Info->UseMCast) {
      //
      // Get the multicast discover ip address from vendor option if has.
      //
      CopyMem (&Info->ServerMCastIp.v4, &VendorOpt->DiscoverMcastIp, sizeof (EFI_IPv4_ADDRESS));
    }

    Info->IpCnt = 0;

    if (Info->UseUCast) {
      Entry = VendorOpt->BootSvr;

      while (((UINT8) (Entry - VendorOpt->BootSvr)) < VendorOpt->BootSvrLen) {
        if (Entry->Type == HTONS (Type)) {
          IsFound = TRUE;
          break;
        }
        Entry = GET_NEXT_BOOT_SVR_ENTRY (Entry);
      }

      if (!IsFound) {
        return EFI_DEVICE_ERROR;
      }

      Info->IpCnt = Entry->IpCnt;
      if (Info->IpCnt >= 1) {
        *DiscoverInfo = AllocatePool (sizeof (*Info) + (Info->IpCnt - 1) * sizeof (**SrvList));
        if (*DiscoverInfo == NULL) {
          return EFI_OUT_OF_RESOURCES;       
        }     
        CopyMem (*DiscoverInfo, Info, sizeof (*Info));
        Info = *DiscoverInfo;
      }

      for (Index = 0; Index < Info->IpCnt; Index++) {
        CopyMem (&Info->SrvList[Index].IpAddr, &Entry->IpAddr[Index], sizeof (EFI_IPv4_ADDRESS));
        Info->SrvList[Index].AcceptAnyResponse = !Info->MustUseList;
        Info->SrvList[Index].Type = NTOHS (Entry->Type);
      }
    }

    *BootEntry = Entry;
    *SrvList   = Info->SrvList;
  }

  return EFI_SUCCESS;
}