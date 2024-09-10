void
DDProxyLoadConfig(
   IN  PUNICODE_STRING registryPath
   )
{
   NTSTATUS status;

   OBJECT_ATTRIBUTES objectAttributes;
   HANDLE registryKey;
   UNICODE_STRING valueName;
   UCHAR regValueStorage[sizeof(KEY_VALUE_PARTIAL_INFORMATION) + 
                         INET6_ADDRSTRLEN * sizeof(WCHAR)]; 
   KEY_VALUE_PARTIAL_INFORMATION* regValue = 
      (KEY_VALUE_PARTIAL_INFORMATION*)regValueStorage;
   ULONG resultLength;

   InitializeObjectAttributes(
      &objectAttributes,
      registryPath,
      OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
      NULL,
      NULL
      );

   status = ZwOpenKey(
               &registryKey,
               KEY_READ,
               &objectAttributes
               );
   if (NT_SUCCESS(status))
   {
      RtlInitUnicodeString(
         &valueName,
         L"InspectUdp"
         );

      status = ZwQueryValueKey(
                  registryKey,
                  &valueName,
                  KeyValuePartialInformation,
                  regValue,
                  sizeof(regValueStorage),
                  &resultLength
                  );

      if (NT_SUCCESS(status))
      {
         if ((*(PULONG)regValue->Data) != 0)
         {
            configInspectUdp = TRUE;
         }
         else
         {
            configInspectUdp = FALSE;
         }
      }

      RtlInitUnicodeString(
         &valueName,
         L"DestinationAddressToIntercept"
         );

      status = ZwQueryValueKey(
                  registryKey,
                  &valueName,
                  KeyValuePartialInformation,
                  regValue,
                  sizeof(regValueStorage),
                  &resultLength                                                                          
                  );

      if (NT_SUCCESS(status))
      {
         PWSTR terminator;

         status = RtlIpv4StringToAddressW(
                     (PCWSTR)(regValue->Data),
                     TRUE,
                     &terminator,
                     &destAddrStorageV4
                     );

         if (NT_SUCCESS(status))
         {
            destAddrStorageV4.S_un.S_addr = 
               RtlUlongByteSwap(destAddrStorageV4.S_un.S_addr);
            configInspectDestAddrV4 = &destAddrStorageV4.S_un.S_un_b.s_b1;
         }
         else
         {
            status = RtlIpv6StringToAddressW(
                        (PCWSTR)(regValue->Data),
                        &terminator,
                        &destAddrStorageV6
                        );

            if (NT_SUCCESS(status))
            {
               configInspectDestAddrV6 = (UINT8*)(&destAddrStorageV6.u.Byte[0]);
            }
         }
      }

      RtlInitUnicodeString(
         &valueName,
         L"DestinationPortToIntercept"
         );

      status = ZwQueryValueKey(
                  registryKey,
                  &valueName,
                  KeyValuePartialInformation,
                  regValue,
                  sizeof(regValueStorage),
                  &resultLength                                                                          
                  );

      if (NT_SUCCESS(status))
      {
         configInspectDestPort = (USHORT)(*(PULONG)regValue->Data);
      }

      RtlInitUnicodeString(
         &valueName,
         L"NewDestinationAddress"
         );

      status = ZwQueryValueKey(
                  registryKey,
                  &valueName,
                  KeyValuePartialInformation,
                  regValue,
                  sizeof(regValueStorage),
                  &resultLength                                                                          
                  );

      if (NT_SUCCESS(status))
      {
         PWSTR terminator;

         status = RtlIpv4StringToAddressW(
                     (PCWSTR)(regValue->Data),
                     TRUE,
                     &terminator,
                     &newDestAddrStorageV4
                     );

         if (NT_SUCCESS(status))
         {
            newDestAddrStorageV4.S_un.S_addr = 
               RtlUlongByteSwap(newDestAddrStorageV4.S_un.S_addr);
            configNewDestAddrV4 = &newDestAddrStorageV4.S_un.S_un_b.s_b1;
         }
         else
         {
            status = RtlIpv6StringToAddressW(
                        (PCWSTR)(regValue->Data),
                        &terminator,
                        &newDestAddrStorageV6
                        );

            if (NT_SUCCESS(status))
            {
               configNewDestAddrV6 = (UINT8*)(&newDestAddrStorageV6.u.Byte[0]);
            }
         }
      }

      RtlInitUnicodeString(
         &valueName,
         L"NewDestinationPort"
         );

      status = ZwQueryValueKey(
                  registryKey,
                  &valueName,
                  KeyValuePartialInformation,
                  regValue,
                  sizeof(regValueStorage),
                  &resultLength                                                                          
                  );

      if (NT_SUCCESS(status))
      {
         configNewDestPort = (USHORT)(*(PULONG)regValue->Data);
      }

      ZwClose(registryKey);
   }
}