DWORD C_ArpTable::arpspoof_check_by_ip(IPAddr ip,PMIB_IPNETROW old_row)
{
	
	char *str1;
	in_addr ip_in_addr;
	ip_in_addr.S_un.S_addr=ip;
	str1=inet_ntoa(ip_in_addr);
	printf("Checking %s for arp spoofing...\n",str1);

	ULONG MacAddr[3],MacAddr2[3],MacAddr3[3];
	ULONG PhysAddrLen = 12,PhysAddrLen2=12,PhysAddrLen3=12;
	PMIB_IPNETROW x=C_ArpTable::find_by_ip(ip);
	if(!x || x->dwType!=3) 
		return 0; //if no entry or static entry.
	C_ArpTable::del_by_ip(ip);
	if(SendARP(ip,0, MacAddr, &PhysAddrLen)!=0)
		PhysAddrLen=0;
	C_ArpTable::del_by_ip(ip);
	if(SendARP(ip,0, MacAddr2, &PhysAddrLen2)!=0)
	{
		if(PhysAddrLen==0)
			return 0; //cant sendarp two times, exit;
		PhysAddrLen2=0;
	}
	C_ArpTable::del_by_ip(ip);
	if(SendARP(ip,0, MacAddr3, &PhysAddrLen3)!=0)
		PhysAddrLen3=0;
	if(
		(PhysAddrLen>0 &&  (PhysAddrLen!=x->dwPhysAddrLen  || memcmp(MacAddr,x->bPhysAddr,PhysAddrLen)!=0))
		||
		(PhysAddrLen2>0 && (PhysAddrLen2!=x->dwPhysAddrLen || memcmp(MacAddr2,x->bPhysAddr,PhysAddrLen2)!=0))
		||
		(PhysAddrLen3>0 && (PhysAddrLen3!=x->dwPhysAddrLen || memcmp(MacAddr3,x->bPhysAddr,PhysAddrLen3)!=0))
		)
	{

		if(
			((PhysAddrLen==0 || PhysAddrLen2==0) || (PhysAddrLen==PhysAddrLen2 && memcmp(MacAddr,MacAddr2,PhysAddrLen2)==0))
			&&
			((PhysAddrLen==0 || PhysAddrLen3==0) || (PhysAddrLen==PhysAddrLen3 && memcmp(MacAddr,MacAddr3,PhysAddrLen3)==0))
			&&
			((PhysAddrLen2==0 || PhysAddrLen3==0) || (PhysAddrLen2==PhysAddrLen3 && memcmp(MacAddr2,MacAddr3,PhysAddrLen3)==0))

			)
		{
			if(PhysAddrLen!=0)
				memcpy(x->bPhysAddr,MacAddr,PhysAddrLen);
			else
				memcpy(x->bPhysAddr,MacAddr2,PhysAddrLen2);
		}
		if(old_row)
		{
			if(
				(PhysAddrLen!=0 && old_row->dwPhysAddrLen==PhysAddrLen && memcmp(MacAddr,old_row->bPhysAddr,PhysAddrLen)==0)
				||
				(PhysAddrLen2!=0 && old_row->dwPhysAddrLen==PhysAddrLen2 && memcmp(MacAddr2,old_row->bPhysAddr,PhysAddrLen2)==0)
				||
				(PhysAddrLen3!=0 && old_row->dwPhysAddrLen==PhysAddrLen3 && memcmp(MacAddr3,old_row->bPhysAddr,PhysAddrLen3)==0)
				)
			{
				memcpy(x->bPhysAddr,old_row->bPhysAddr,old_row->dwPhysAddrLen);
				printf("use old address.\n");
			}
		}
		else
			printf("Spoofed new address.\n");
		x->dwType=4;
		C_ArpTable::del_by_ip(ip);
		if(CreateIpNetEntry(x)!=0)
		{
			C_ArpTable::del_by_ip(ip);
			CreateIpNetEntry(x);
		}

		printf("Arp spoof of %s detected. setting arp entry to static.\nfor delete static entry run \"arp -d %s\"\n\n",str1,str1);
		return 1;
		//spoofing detected!
	}
	printf("Spoofing not detected.\n\n");
	CreateIpNetEntry(x);
///	C_ArpTable::reload();
	return 0;
}