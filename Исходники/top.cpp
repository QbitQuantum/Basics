IPCCommandResult NetIPTop::HandleGetInterfaceOptRequest(const IOCtlVRequest& request)
{
  const u32 param = Memory::Read_U32(request.in_vectors[0].address);
  const u32 param2 = Memory::Read_U32(request.in_vectors[0].address + 4);
  const u32 param3 = Memory::Read_U32(request.io_vectors[0].address);
  const u32 param4 = Memory::Read_U32(request.io_vectors[1].address);
  u32 param5 = 0;

  if (request.io_vectors[0].size >= 8)
  {
    param5 = Memory::Read_U32(request.io_vectors[0].address + 4);
  }

  INFO_LOG(IOS_NET, "IOCTLV_SO_GETINTERFACEOPT(%08X, %08X, %X, %X, %X) "
                    "BufferIn: (%08x, %i), BufferIn2: (%08x, %i) ",
           param, param2, param3, param4, param5, request.in_vectors[0].address,
           request.in_vectors[0].size,
           request.in_vectors.size() > 1 ? request.in_vectors[1].address : 0,
           request.in_vectors.size() > 1 ? request.in_vectors[1].size : 0);

  switch (param2)
  {
  case 0xb003:  // dns server table
  {
    u32 address = 0;
#ifdef _WIN32
    if (!Core::WantsDeterminism())
    {
      PIP_ADAPTER_ADDRESSES AdapterAddresses = nullptr;
      ULONG OutBufferLength = 0;
      ULONG RetVal = 0, i;
      for (i = 0; i < 5; ++i)
      {
        RetVal = GetAdaptersAddresses(AF_INET, 0, nullptr, AdapterAddresses, &OutBufferLength);

        if (RetVal != ERROR_BUFFER_OVERFLOW)
        {
          break;
        }

        if (AdapterAddresses != nullptr)
        {
          FREE(AdapterAddresses);
        }

        AdapterAddresses = (PIP_ADAPTER_ADDRESSES)MALLOC(OutBufferLength);
        if (AdapterAddresses == nullptr)
        {
          RetVal = GetLastError();
          break;
        }
      }
      if (RetVal == NO_ERROR)
      {
        unsigned long dwBestIfIndex = 0;
        IPAddr dwDestAddr = (IPAddr)0x08080808;
        // If successful, output some information from the data we received
        PIP_ADAPTER_ADDRESSES AdapterList = AdapterAddresses;
        if (GetBestInterface(dwDestAddr, &dwBestIfIndex) == NO_ERROR)
        {
          while (AdapterList)
          {
            if (AdapterList->IfIndex == dwBestIfIndex && AdapterList->FirstDnsServerAddress &&
                AdapterList->OperStatus == IfOperStatusUp)
            {
              INFO_LOG(IOS_NET, "Name of valid interface: %S", AdapterList->FriendlyName);
              INFO_LOG(
                  IOS_NET, "DNS: %u.%u.%u.%u",
                  (unsigned char)AdapterList->FirstDnsServerAddress->Address.lpSockaddr->sa_data[2],
                  (unsigned char)AdapterList->FirstDnsServerAddress->Address.lpSockaddr->sa_data[3],
                  (unsigned char)AdapterList->FirstDnsServerAddress->Address.lpSockaddr->sa_data[4],
                  (unsigned char)
                      AdapterList->FirstDnsServerAddress->Address.lpSockaddr->sa_data[5]);
              address = Common::swap32(
                  *(u32*)(&AdapterList->FirstDnsServerAddress->Address.lpSockaddr->sa_data[2]));
              break;
            }
            AdapterList = AdapterList->Next;
          }
        }
      }
      if (AdapterAddresses != nullptr)
      {
        FREE(AdapterAddresses);
      }
    }
#endif
    if (address == 0)
      address = 0x08080808;

    Memory::Write_U32(address, request.io_vectors[0].address);
    Memory::Write_U32(0x08080404, request.io_vectors[0].address + 4);
    break;
  }
  case 0x1003:  // error
    Memory::Write_U32(0, request.io_vectors[0].address);
    break;

  case 0x1004:  // mac address
    u8 address[Common::MAC_ADDRESS_SIZE];
    IOS::Net::GetMACAddress(address);
    Memory::CopyToEmu(request.io_vectors[0].address, address, sizeof(address));
    break;

  case 0x1005:  // link state
    Memory::Write_U32(1, request.io_vectors[0].address);
    break;

  case 0x3001:  // hardcoded value
    Memory::Write_U32(0x10, request.io_vectors[0].address);
    break;

  case 0x4002:  // ip addr numberHandle
    Memory::Write_U32(1, request.io_vectors[0].address);
    break;

  case 0x4003:  // ip addr table
    Memory::Write_U32(0xC, request.io_vectors[1].address);
    Memory::Write_U32(inet_addr(10, 0, 1, 30), request.io_vectors[0].address);
    Memory::Write_U32(inet_addr(255, 255, 255, 0), request.io_vectors[0].address + 4);
    Memory::Write_U32(inet_addr(10, 0, 255, 255), request.io_vectors[0].address + 8);
    break;

  case 0x4005:  // hardcoded value
    Memory::Write_U32(0x20, request.io_vectors[0].address);
    break;

  case 0x6003:  // hardcoded value
    Memory::Write_U32(0x80, request.io_vectors[0].address);
    break;

  case 0x600a:  // hardcoded value
    Memory::Write_U32(0x80, request.io_vectors[0].address);
    break;

  case 0x600c:  // hardcoded value
    Memory::Write_U32(0x80, request.io_vectors[0].address);
    break;

  case 0xb002:  // hardcoded value
    Memory::Write_U32(2, request.io_vectors[0].address);
    break;

  default:
    ERROR_LOG(IOS_NET, "Unknown param2: %08X", param2);
    break;
  }

  return GetDefaultReply(0);
}