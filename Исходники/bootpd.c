int ProcessDHCPMessage (struct dhcp_packet *pDhcpPkt, int *pSize)
{
unsigned char *p=NULL;
struct LL_IP  *pCurIP=NULL, *pProposedIP=NULL;	// Thanks Sam Leitch !
int            Ark, nDhcpType = 0;
struct in_addr sRequestedAddr;
DWORD sStaticIP;

    if (IsDHCP (*pDhcpPkt))
    {
       // search DHCP message type
       p = DHCPSearchOptionsField (pDhcpPkt->options, DHO_DHCP_MESSAGE_TYPE, NULL);
       if (p!=NULL)        nDhcpType = *p;
     }
    if (pDhcpPkt->yiaddr.s_addr!=INADDR_ANY  &&  pDhcpPkt->yiaddr.s_addr!=INADDR_NONE )
            return FALSE ; // address already assigned

     // the tab has one undef raw
     for (Ark=0 ; Ark<SizeOfTab(tDHCPType)-1 && nDhcpType!=tDHCPType[Ark].nType ; Ark++) ;
     LOG (5, "Rcvd %s Msg for IP %s, Mac %s",
                      tDHCPType[Ark].sType,
                      inet_ntoa (pDhcpPkt->ciaddr),
                      haddrtoa(pDhcpPkt->chaddr, pDhcpPkt->hlen,':'));


    // if (sParamDHCP.nPoolSize==0) return FALSE;   // no allocation pool --> listen only

     switch (nDhcpType)
     {
        case 0           :    // BootP
            if(sParamDHCP.nIgnoreBootp)
            {
               LOG (5, "Ignoring Bootp request");
               break;
            }
        case DHCPDISCOVER :
            sStaticIP = DHCP_StaticAssignation (pDhcpPkt);
			if (sStaticIP != INADDR_NONE)
			{
               LOG (0, "%s: statically assigned to address %s", 
								haddrtoa(pDhcpPkt->chaddr, pDhcpPkt->hlen,':'), 
								inet_ntoa (* (struct in_addr *) & sStaticIP) );
               pDhcpPkt->yiaddr.s_addr = sStaticIP;
			}
			else
			{
               p  = DHCPSearchOptionsField (pDhcpPkt->options, DHO_DHCP_REQUESTED_ADDRESS, NULL);
               if (p!=NULL)
              {
                   pDhcpPkt->ciaddr = * (struct in_addr *) p;
                   LOG (5, "Client requested address %s", inet_ntoa (pDhcpPkt->ciaddr));
              }
              pProposedIP  = DHCP_IPAllocate (nDhcpType, & pDhcpPkt->ciaddr, pDhcpPkt->chaddr, pDhcpPkt->hlen);
              if (pProposedIP == NULL)
              {
                  LOG (1, "no more address or address previously allocated by another server");
                  return FALSE;
              }
              pDhcpPkt->yiaddr.s_addr = pProposedIP->dwIP.s_addr;
              LOG (2, "%s: proposed address %s", IsDHCP(*pDhcpPkt) ? "DHCP" : "BOOTP", inet_ntoa (pProposedIP->dwIP) );

              //If this is a bootp, there is no other response from the client.  
              //Since we don't want leases expiring (or being mistaken for unAcked DHCP offers),
              //set renewed to a distant time
              if(nDhcpType == 0  &&  sStaticIP == INADDR_NONE)     // patched by Rolf Offermanns
                  ForceRenewTime(pProposedIP, 0x66666666);         // fixed by Sam Leitch
            } // dynamically assigned address

            // populate the packet to be returned
            pDhcpPkt->op = BOOTREPLY;
            // translate $IP$ and $MAC$ from boot file name
            TranslateExp (sParamDHCP.szBootFile, pDhcpPkt->file, pDhcpPkt->yiaddr, pDhcpPkt->chaddr);
           *pSize = DHCPOptionsReply (pDhcpPkt, DHCPOFFER);
            break ;

		//NJW Changed how requests are handled to mimic linux -- requests are responded to even if we didn't originally allocate, but only if the requested address is in our pool range

        case DHCPREQUEST :
         {BOOL bSERVER = FALSE;  // TRUE if Tftpd32 has assigned this address
           // Static Allocation ?
             // search field REQUEST ADDR in options
            sStaticIP = DHCP_StaticAssignation (pDhcpPkt);
			if (sStaticIP != INADDR_NONE)
			{
			    // populate the packet to be returned
                   pDhcpPkt->op = BOOTREPLY;
                   pDhcpPkt->yiaddr.s_addr = sStaticIP;
                 // translate $IP$ and $MAC$ from boot file name
                 TranslateExp (sParamDHCP.szBootFile, pDhcpPkt->file, pDhcpPkt->yiaddr, pDhcpPkt->chaddr);
                   *pSize = DHCPOptionsReply (pDhcpPkt, DHCPACK);
				   break;
			}

           // has tftpd32 dinamically assigned this address
           pCurIP = DHCPSearchByMacAddress (pDhcpPkt->chaddr, pDhcpPkt->hlen);
           if (pCurIP==NULL)  return FALSE; // not attributed by Tftpd32 --> do not answer
           // search field REQUEST ADDR in options
            // if specified should fit database
			p  = DHCPSearchOptionsField (pDhcpPkt->options, DHO_DHCP_REQUESTED_ADDRESS, NULL);
            if (p!=NULL)
			{
				pDhcpPkt->ciaddr = * (struct in_addr *) p;
			}

			if(AddrFitsPool(&pDhcpPkt->ciaddr))
			{
				//Look up the address, if it's not found, or the owner is this macaddr,
				//or the lease was expired, allow the serving.
				BOOL wasexpired = FALSE;
				pProposedIP = DHCPSearchByIP(&pDhcpPkt->ciaddr, &wasexpired);
				bSERVER = !pProposedIP || wasexpired || (0 == memcmp(pProposedIP->sMacAddr, pDhcpPkt->chaddr, 6));
			}

			if (bSERVER)
			{

				pProposedIP  = DHCP_IPAllocate (nDhcpType, & pDhcpPkt->ciaddr, pDhcpPkt->chaddr, pDhcpPkt->hlen);
				if (pProposedIP == NULL)
				{
					  LOG (1, "no more addresses or address previously allocated by another server");
					  return FALSE;
				}
				if (pProposedIP->tAllocated==0) SetAllocTime(pProposedIP);
				SetRenewTime(pProposedIP);
				LOG (5, "Previously allocated address %s acked", inet_ntoa (pProposedIP->dwIP));
				// populate the packet to be returned
				pDhcpPkt->op = BOOTREPLY;
				pDhcpPkt->yiaddr.s_addr = pProposedIP->dwIP.s_addr;
                TranslateExp (sParamDHCP.szBootFile, pDhcpPkt->file, pDhcpPkt->yiaddr, pDhcpPkt->chaddr);
				*pSize = DHCPOptionsReply (pDhcpPkt, DHCPACK);
			}
			else
			{
				LOG (5, "Client requested address %s which was not allocated by tftpd32 and is either outside our pool or is used by someone else",
							  inet_ntoa (pDhcpPkt->ciaddr) );
				return FALSE ; // do not answer
 			}
           } // Block for bSERVER declaration
           break;


        case DHCPDECLINE :
             // search current item and its precedent
          pCurIP = DHCPSearchByMacAddress (pDhcpPkt->chaddr, pDhcpPkt->hlen);
           if (pCurIP!=NULL)
           {
             p  = DHCPSearchOptionsField (pDhcpPkt->options, DHO_DHCP_REQUESTED_ADDRESS, NULL);
             if (p!=NULL) 
              {
                 sRequestedAddr.s_addr = * (DWORD *) p;
                 if ( pCurIP->dwIP.s_addr==sRequestedAddr.s_addr) 
                 {
                     DHCPDestroyItem (pCurIP);
                     LOG (5, "item destroyed");
                 }
             }
           }
		   //The decline is sent when an address is already in use.  Do an ARP and 
		   //add a lease for the in-use address
		   {
			 ULONG mac[2];
			 ULONG maclen = 6;
			// search field REQUEST ADDR in options
			// if specified should fit database
			p  = DHCPSearchOptionsField (pDhcpPkt->options, DHO_DHCP_REQUESTED_ADDRESS, NULL);
			if (p!=NULL)
			{
				pDhcpPkt->ciaddr = * (struct in_addr *) p;
			}

			 if(NO_ERROR == SendARP(pDhcpPkt->ciaddr.s_addr, 0, mac, &maclen))
			 {
				pProposedIP  = DHCP_IPAllocate (nDhcpType, & pDhcpPkt->ciaddr, (unsigned char*)mac, maclen);
				if (pProposedIP)
				{
					if (pProposedIP->tAllocated==0) SetAllocTime(pProposedIP);
					ForceRenewTime(pProposedIP, 0x66666666);   //Give a bootp lease, since the device may not do dhcp      
					LOG (5, "Added lease for existing address %s", inet_ntoa (pProposedIP->dwIP));
				}
			 }
		   }
           break;

        case DHCPRELEASE :
            // do not destroy the item but mark it free
           pCurIP = DHCPSearchByMacAddress (pDhcpPkt->chaddr, pDhcpPkt->hlen);
           if (pCurIP!=NULL) // then mac address found in table
           {
                ZeroAllocTime(pCurIP);
                ZeroRenewTime(pCurIP);
                LOG (5, "item %s released", haddrtoa(pDhcpPkt->chaddr, pDhcpPkt->hlen,':') );
           }
           break;
       } // switch type


DHCPScan();

// answer only to BootP, Request or discover msg
return  (nDhcpType==0 || nDhcpType==DHCPDISCOVER || nDhcpType==DHCPREQUEST);
} // ProcessDHCPMessage