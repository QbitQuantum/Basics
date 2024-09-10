signed char ioman_directSectorRead(IOManager *ioman,unsigned long address, unsigned char* buf)
{
	unsigned char* ibuf;
	signed short bp;
	
	if((bp=ioman_findSectorInCache(ioman,address))!=-1){
		ibuf=ioman_getPtr(ioman,bp);
		memCpy(ibuf,buf,512);
		return(0);
	}
	
	if((bp=ioman_findFreeSpot(ioman))!=-1){
		if((ioman_putSectorInCache(ioman,address,bp))){
			return(-1);
		}
		ibuf=ioman_getPtr(ioman,bp);
		memCpy(ibuf,buf,512);
		return(0);
	}

	if(ioman_readSector(ioman,address,buf)){
		return(-1);
	}

	return(0);
}