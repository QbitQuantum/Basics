BOOL acl_filter(PACL_LIST acl,const unsigned char HwType,const unsigned char* HwAddr,unsigned char HwAddrLen){
	AcquireSRWLockShared(&acl->lock);
	DEBUG("acl_filter: AcquireSRWLockShared()\n");
	__try{
		char buf[16*2+1];
		DEBUG("acl_filter(HwType=%d, HwAddr=%s)\n",(int)HwType,dhcp_hw_addr(buf,HwAddr,(int)HwAddrLen));
		unsigned int len = acl->length,i,j;
		PACL_ENTRY entries = acl->entry;
		for(i = 0;i<len;i++){
			DEBUG("acl_filter: entry[%d].HwType=%d arg.HwType=%d\n",i,(int)entries[i].HwType,(int)HwType);
			if(entries[i].HwType!=HwType)
				continue;
			
			for(j=0;j<HwAddrLen;j++){
				DEBUG("acl_filter: entry[%d].HwAddr[%d]=0x%02x arg.HwAddr[%d]=0x%02x\n",i,j,(int)entries[i].HwAddr[j],j,(int)HwAddr[j]);
				if((HwAddr[j]&entries[i].HwMask[j])!=entries[i].HwAddr[j]){
					goto next;
				}
			}
			return entries[i].access;
	next:	
			DEBUG("Goto Next\n");
			(void)0;
		}
		return TRUE;
	}__finally{
		ReleaseSRWLockShared(&acl->lock);
		DEBUG("acl_filter: ReleaseSRWLockShared()\n");
	}
}