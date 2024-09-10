int imageFileValid(unsigned long startAddr, int len)
{
	int i=0;
	unsigned long head_offset=0;
	unsigned short sum=0;
	unsigned char sum1=0;
	IMG_HEADER_T Header ; //avoid unalign problem
       int	skip_check_signature=0;
	   
	
	int found=0;
	   
	while((head_offset + sizeof(IMG_HEADER_T)) <  len){
		/*as soon as we found a correct header. we thinks the file is valid*/
		memcpy(&Header, ((char *)startAddr + head_offset), sizeof(IMG_HEADER_T));
		if(!skip_check_signature)
		{
			for(i=0 ;i < MAX_SIG_TBL ; i++) {
			

				if(!memcmp(Header.signature, (char *)sign_tbl[i].signature, sign_tbl[i].sig_len)){
					found++;
					break;			
				}
			
				
			}
			if(i == MAX_SIG_TBL){
				head_offset += Header.len + sizeof(IMG_HEADER_T);
				continue ;
			}	
		}
		else
		{
			if(!memcmp(Header.signature, BOOT_SIGNATURE, SIG_LEN))
			{
				found++;
			}
			else 
			{
				unsigned char *pRoot =((unsigned char *)startAddr) + head_offset + sizeof(IMG_HEADER_T);
				if (!memcmp(pRoot, SQSH_SIGNATURE, SIG_LEN))
				{
					found++;
				}
			}				
		}

		if(skip_check_signature || 
			memcmp(Header.signature, WEB_SIGNATURE, 3)){
			//calculate checksum
			if(!memcmp(Header.signature, ALL1_SIGNATURE, SIG_LEN) ||
					!memcmp(Header.signature, ALL2_SIGNATURE, SIG_LEN)) {
				for (i=0; i< Header.len+sizeof(IMG_HEADER_T); i+=2) {
					sum += *((unsigned short *)(startAddr+ head_offset + i));
				}				
			}	
			else {			
			unsigned char x=0,y=0;
			unsigned short temp=0;	
			for (i=0; i< Header.len; i+=2) 
			{
#if defined(RTL8196B) || defined(RTL8198)				
#if 1				
				//sum +=*((unsigned short *)(startAddr+ head_offset + sizeof(IMG_HEADER_T) + i));
				memcpy(&temp, (startAddr+ head_offset + sizeof(IMG_HEADER_T) + i), 2); // for alignment issue
				sum+=temp;
#else
				x=*((unsigned char *)(startAddr+ head_offset + sizeof(IMG_HEADER_T) + i));						
				y=*((unsigned char *)(startAddr+ head_offset + sizeof(IMG_HEADER_T) + i+1));
				sum+=(y|x<<8)&0xFFFF;
#endif
#else
				sum += *((unsigned short *)(startAddr+ head_offset + sizeof(IMG_HEADER_T) + i));
#endif				
				}
			}
			if ( sum ) {
				for(i=0 ;i < MAX_SIG_TBL ; i++) {
					
					if(!memcmp(Header.signature, (char *)sign_tbl[i].signature, sign_tbl[i].sig_len)){
						break;
					}			
				}
				SprintF(message,"%s imgage checksum error at %X!\n",sign_tbl[i].comment, startAddr+head_offset);
				return -1;
			}

		if(!memcmp(Header.signature, ALL1_SIGNATURE, SIG_LEN)){
					found++;
				head_offset += sizeof(IMG_HEADER_T);
				continue;		
		}	
		if(!memcmp(Header.signature, ALL2_SIGNATURE, SIG_LEN)){
				found ++;
			skip_check_signature = 1;
			head_offset += sizeof(IMG_HEADER_T);			
			continue;		
		}						
	     }else
	     {  
	     		//web page use different checksum algorimth
			for (i=0; i< Header.len; i++)
			       sum1 += *((unsigned char *)(startAddr+ head_offset + sizeof(IMG_HEADER_T) + i));
			if ( sum1 ) {
				for(i=0 ;i < MAX_SIG_TBL ; i++) {
					if(!memcmp(Header.signature, (char *)sign_tbl[i].signature, sign_tbl[i].sig_len))
					{
						break;
					}	
				}
				SprintF(message,"%s imgage checksum error at %X!\n",sign_tbl[i].comment, startAddr+head_offset);
				return -1;
			}
		}
		head_offset += Header.len + sizeof(IMG_HEADER_T);
	} //while	
	return found;
}