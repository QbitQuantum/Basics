VOID tapReadPermanentAddress(__in PTAP_ADAPTER_CONTEXT Adapter,
                             __in NDIS_HANDLE ConfigurationHandle, __out MACADDR PermanentAddress) {
  NDIS_STATUS status;
  NDIS_CONFIGURATION_PARAMETER *configParameter;
  NDIS_STRING macKey = NDIS_STRING_CONST("MAC");
  ANSI_STRING macString;
  BOOLEAN macFromRegistry = FALSE;

  // Read MAC parameter from registry.
  NdisReadConfiguration(&status, &configParameter, ConfigurationHandle, &macKey,
                        NdisParameterString);

  if (status == NDIS_STATUS_SUCCESS) {
    if ((configParameter->ParameterType == NdisParameterString) &&
        (configParameter->ParameterData.StringData.Length >= 12)) {
      if (RtlUnicodeStringToAnsiString(&macString, &configParameter->ParameterData.StringData,
                                       TRUE) == STATUS_SUCCESS) {
        macFromRegistry = ParseMAC(PermanentAddress, macString.Buffer);
        RtlFreeAnsiString(&macString);
      }
    }
  }

  if (!macFromRegistry) {
    //
    // There is no (valid) address stashed in the registry parameter.
    //
    // Make up a dummy mac address based on the ANSI representation of the
    // NetCfgInstanceId GUID.
    //
    GenerateRandomMac(PermanentAddress, MINIPORT_INSTANCE_ID(Adapter));
  }
}