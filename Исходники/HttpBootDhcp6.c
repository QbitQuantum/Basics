/**
  Build the options buffer for the DHCPv6 request packet.

  @param[in]  Private             The pointer to HTTP BOOT driver private data.
  @param[out] OptList             The pointer to the option pointer array.
  @param[in]  Buffer              The pointer to the buffer to contain the option list.

  @return     Index               The count of the built-in options.

**/
UINT32
HttpBootBuildDhcp6Options (
  IN  HTTP_BOOT_PRIVATE_DATA       *Private,
  OUT EFI_DHCP6_PACKET_OPTION      **OptList,
  IN  UINT8                        *Buffer
  )
{
  HTTP_BOOT_DHCP6_OPTION_ENTRY     OptEnt;
  UINT16                           Value;
  UINT32                           Index;

  Index      = 0;
  OptList[0] = (EFI_DHCP6_PACKET_OPTION *) Buffer;

  //
  // Append client option request option
  //
  OptList[Index]->OpCode     = HTONS (HTTP_BOOT_DHCP6_OPT_ORO);
  OptList[Index]->OpLen      = HTONS (8);
  OptEnt.Oro                 = (HTTP_BOOT_DHCP6_OPTION_ORO *) OptList[Index]->Data;
  OptEnt.Oro->OpCode[0]      = HTONS(HTTP_BOOT_DHCP6_OPT_BOOT_FILE_URL);
  OptEnt.Oro->OpCode[1]      = HTONS(HTTP_BOOT_DHCP6_OPT_BOOT_FILE_PARAM);
  OptEnt.Oro->OpCode[2]      = HTONS(HTTP_BOOT_DHCP6_OPT_DNS_SERVERS);
  OptEnt.Oro->OpCode[3]      = HTONS(HTTP_BOOT_DHCP6_OPT_VENDOR_CLASS);
  Index++;
  OptList[Index]             = GET_NEXT_DHCP6_OPTION (OptList[Index - 1]);

  //
  // Append client network device interface option
  //
  OptList[Index]->OpCode     = HTONS (HTTP_BOOT_DHCP6_OPT_UNDI);
  OptList[Index]->OpLen      = HTONS ((UINT16)3);
  OptEnt.Undi                = (HTTP_BOOT_DHCP6_OPTION_UNDI *) OptList[Index]->Data;

  if (Private->Nii != NULL) {
    OptEnt.Undi->Type        = Private->Nii->Type;
    OptEnt.Undi->MajorVer    = Private->Nii->MajorVer;
    OptEnt.Undi->MinorVer    = Private->Nii->MinorVer;
  } else {
    OptEnt.Undi->Type        = DEFAULT_UNDI_TYPE;
    OptEnt.Undi->MajorVer    = DEFAULT_UNDI_MAJOR;
    OptEnt.Undi->MinorVer    = DEFAULT_UNDI_MINOR;
  }

  Index++;
  OptList[Index]             = GET_NEXT_DHCP6_OPTION (OptList[Index - 1]);

  //
  // Append client system architecture option
  //
  OptList[Index]->OpCode     = HTONS (HTTP_BOOT_DHCP6_OPT_ARCH);
  OptList[Index]->OpLen      = HTONS ((UINT16) sizeof (HTTP_BOOT_DHCP6_OPTION_ARCH));
  OptEnt.Arch                = (HTTP_BOOT_DHCP6_OPTION_ARCH *) OptList[Index]->Data;
  Value                      = HTONS (EFI_HTTP_BOOT_CLIENT_SYSTEM_ARCHITECTURE);
  CopyMem (&OptEnt.Arch->Type, &Value, sizeof (UINT16));
  Index++;
  OptList[Index]             = GET_NEXT_DHCP6_OPTION (OptList[Index - 1]);

  //
  // Append vendor class identify option.
  //
  OptList[Index]->OpCode       = HTONS (HTTP_BOOT_DHCP6_OPT_VENDOR_CLASS);
  OptList[Index]->OpLen        = HTONS ((UINT16) sizeof (HTTP_BOOT_DHCP6_OPTION_VENDOR_CLASS));
  OptEnt.VendorClass           = (HTTP_BOOT_DHCP6_OPTION_VENDOR_CLASS *) OptList[Index]->Data;
  OptEnt.VendorClass->Vendor   = HTONL (HTTP_BOOT_DHCP6_ENTERPRISE_NUM);
  OptEnt.VendorClass->ClassLen = HTONS ((UINT16) sizeof (HTTP_BOOT_CLASS_ID));
  CopyMem (
    &OptEnt.VendorClass->ClassId,
    DEFAULT_CLASS_ID_DATA,
    sizeof (HTTP_BOOT_CLASS_ID)
    );
  HttpBootUintnToAscDecWithFormat (
    EFI_HTTP_BOOT_CLIENT_SYSTEM_ARCHITECTURE,
    OptEnt.VendorClass->ClassId.ArchitectureType,
    sizeof (OptEnt.VendorClass->ClassId.ArchitectureType)
    );

  if (Private->Nii != NULL) {
    CopyMem (
      OptEnt.VendorClass->ClassId.InterfaceName,
      Private->Nii->StringId,
      sizeof (OptEnt.VendorClass->ClassId.InterfaceName)
      );
    HttpBootUintnToAscDecWithFormat (
      Private->Nii->MajorVer,
      OptEnt.VendorClass->ClassId.UndiMajor,
      sizeof (OptEnt.VendorClass->ClassId.UndiMajor)
      );
    HttpBootUintnToAscDecWithFormat (
      Private->Nii->MinorVer,
      OptEnt.VendorClass->ClassId.UndiMinor,
      sizeof (OptEnt.VendorClass->ClassId.UndiMinor)
      );
  }

  Index++;

  return Index;
}