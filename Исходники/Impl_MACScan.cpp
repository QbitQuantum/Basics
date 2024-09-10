/* jShadow: black magic!  here we merge IP Helper with WinPCAP - we go through all 
 * IP addresses via IP Helper and check if some of them matches one of the addresses
 * of WinPCAP adapter address list. if a match is found we get MAC via IP Helper
 */
bool TWinPCAP::GetAdapterMAC(int adapter, unsigned char * mac)
{
   bool ok = false;

   /* Preparation: PCAP */
   pcap_if_t * d = GetAdapter(adapter);
   if (!d) return false;

   /* Preparation: IPHlpAPI */
   PMIB_IPADDRTABLE mib_ip_table = NULL;
   ULONG mib_ip_table_size = 0;
   
   /* walk through adapters via IPHelper API*/
   GetIpAddrTable(mib_ip_table, &mib_ip_table_size, FALSE);
   if (mib_ip_table_size != 0)
   {
      mib_ip_table = (PMIB_IPADDRTABLE) new unsigned char[mib_ip_table_size];
      if (mib_ip_table)
      {
         if (GetIpAddrTable(mib_ip_table, &mib_ip_table_size, FALSE) == NO_ERROR)
         {
            for (unsigned int i = 0; i < mib_ip_table->dwNumEntries && !ok; i++)
            {

               /* walk through adapter addresses */
               for (pcap_addr_t * addr = d->addresses; addr && !ok; addr = addr->next)
               {
                  /* we are interested only in AF_INET (IPv4) 'cause ARP is defined in IPv4 stack */
                  if (addr->addr->sa_family == AF_INET && ((struct sockaddr_in *)addr->addr)->sin_addr.S_un.S_addr == mib_ip_table->table[i].dwAddr)
                  {
                     /* gotcha - fetch HW address! */

                     MIB_IFROW mib_if_entry;

                     mib_if_entry.dwIndex = mib_ip_table->table[i].dwIndex;
                     if (GetIfEntry(&mib_if_entry) == NO_ERROR)
                     {
                        ok = true;
                        memcpy(mac, mib_if_entry.bPhysAddr, 6);
                     } /* if */
                  } /* if */
               } /* for on winpcap adapter list */

            } /* for each of IP address matches */
         } /* if GetIpAddrTable */

         /* cleanup */
         delete [] mib_ip_table;
      }
   }

   /* hack: we fill mac address with FF-s if we failed to find it. this
    * workaround is needed to avoid 3 more lines of code in send_packet -
    * if we failed to figure out mac address, we'll send from broadcast 
    * address (we'll most likely get a responce in that case). To speed 
    * up send_packet code we move invariant MAC workaroud here.
    */

   if (!ok)
   {
      memset(mac, 0xff, 6);
   }

   return ok;
}