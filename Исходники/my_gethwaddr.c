/*
  my_gethwaddr - Windows version

  @brief Retrieve MAC address from network hardware

  @param[out]  to MAC address exactly six bytes

  @return Operation status
    @retval 0       OK
    @retval <>0     FAILED
*/
my_bool my_gethwaddr(uchar *to)
{
  PIP_ADAPTER_ADDRESSES pAdapterAddresses;
  PIP_ADAPTER_ADDRESSES pCurrAddresses;
  IP_ADAPTER_ADDRESSES  adapterAddresses;
  ULONG                 address_len;
  my_bool               return_val= 1;
  static pfnGetAdaptersAddresses fnGetAdaptersAddresses=
                                (pfnGetAdaptersAddresses)-1;

  if (fnGetAdaptersAddresses == (pfnGetAdaptersAddresses)-1)
  {
    /* Get the function from the DLL */
    fnGetAdaptersAddresses= (pfnGetAdaptersAddresses)
                            GetProcAddress(LoadLibrary("iphlpapi.dll"),
                                          "GetAdaptersAddresses");
  }
  if (!fnGetAdaptersAddresses)
    return 1;                                   /* failed to get function */
  address_len= sizeof (IP_ADAPTER_ADDRESSES);

  /* Get the required size for the address data. */
  if (fnGetAdaptersAddresses(AF_UNSPEC, 0, 0, &adapterAddresses, &address_len)
      == ERROR_BUFFER_OVERFLOW)
  {
    pAdapterAddresses= my_malloc(address_len, 0);
    if (!pAdapterAddresses)
      return 1;                                   /* error, alloc failed */
  }
  else
    pAdapterAddresses= &adapterAddresses;         /* one is enough don't alloc */

  /* Get the hardware info. */
  if (fnGetAdaptersAddresses(AF_UNSPEC, 0, 0, pAdapterAddresses, &address_len)
      == NO_ERROR)
  {
    pCurrAddresses= pAdapterAddresses;

    while (pCurrAddresses)
    {
      /* Look for ethernet cards. */
      if (pCurrAddresses->IfType == IF_TYPE_ETHERNET_CSMACD)
      {
        /* check for a good address */
        if (pCurrAddresses->PhysicalAddressLength < 6)
            continue;                           /* bad address */

        /* save 6 bytes of the address in the 'to' parameter */
        memcpy(to, pCurrAddresses->PhysicalAddress, 6);

        /* Network card found, we're done. */
        return_val= 0;
        break;
      }
      pCurrAddresses= pCurrAddresses->Next;
    }
  }

  /* Clean up memory allocation. */
  if (pAdapterAddresses != &adapterAddresses)
    my_free(pAdapterAddresses);

  return return_val;
}