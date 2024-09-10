UINT32 GetChunk(BYTE *buffer, UINT32 nLen)
{
	UINT8 *p, *pblock;
	UINT32 chunk_pos;
	struct sto_device *sto_dev = NULL;
	UINT8 sVer[16], hVer[16];
	INT32 i = 0;
	char strTmp[30];
#if (defined HDCP_IN_FLASH ||defined DIVX_CERT_ENABLE)
	INT32 temp_slave_blocks_number=0;
	CHUNK_HEADER *temp_pslave_list = NULL;
#endif
	
	switch((unsigned int)buffer[0])
	{
		case 1:
		case 2:
		case 7:
		case 10:
			slave_Flash_type = 0x80000;	//flash size
			break;
		case 3:
		case 4:
		case 8:
		case 9:
		case 11:
		case 13:
			slave_Flash_type = 0x100000;
			break;
		case 5:
		case 6:
		case 12:
		case 14:
		case 15:
		case 16:
		case 25:
		case 28:
		case 30:
			slave_Flash_type = 0x200000;
			break;
		case 17:
		case 18:
		case 19:
		case 33:
			slave_Flash_type = 0x400000;
			break;
		default:
			slave_Flash_type = 0x200000;/*For unkown flash type,default is 2M*/
			//return !SUCCESS;
	}

	slave_status = (unsigned int)buffer[1];
	if(slave_status==0)
		slave_blocks_number = (nLen -2)/CHUNK_HEADER_SIZE;
	else
		slave_blocks_number = 1;

	pslave_list= (CHUNK_HEADER *)MALLOC(sizeof(CHUNK_HEADER)*slave_blocks_number);
	if (pslave_list == NULL)
		return !SUCCESS;
	MEMSET((void *)pslave_list,0,sizeof(CHUNK_HEADER)*slave_blocks_number);

#if (defined HDCP_IN_FLASH ||defined DIVX_CERT_ENABLE)
#ifdef  HDCP_IN_FLASH
	if(m_allcode_include_bootloader==0)
#endif		
		{
			temp_pslave_list= (CHUNK_HEADER *)MALLOC(sizeof(CHUNK_HEADER)*slave_blocks_number);
			if (temp_pslave_list == NULL)
				return !SUCCESS;
			MEMSET((void *)temp_pslave_list,0,sizeof(CHUNK_HEADER)*slave_blocks_number);
		}
#endif

	pblock = &buffer[2];
	for(i=0; i<slave_blocks_number; i++)
	{
		p = pblock + CHUNK_ID;
		pslave_list[i].id = (*p<<24)+(*(p+1)<<16)+(*(p+2)<<8)+(*(p+3)<<0);

		p = pblock + CHUNK_LENGTH;
		pslave_list[i].len = (*p<<24)+(*(p+1)<<16)+(*(p+2)<<8)+(*(p+3)<<0);

		p = pblock + CHUNK_OFFSET;
		pslave_list[i].offset = (*p<<24)+(*(p+1)<<16)+(*(p+2)<<8)+(*(p+3)<<0);

		p = pblock + CHUNK_CRC;
		pslave_list[i].crc = (*p<<24)+(*(p+1)<<16)+(*(p+2)<<8)+(*(p+3)<<0);

		p = pblock + CHUNK_NAME;
		STRCPY((char *)pslave_list[i].name, (char *)p);

		p = pblock + CHUNK_VERSION;
		STRCPY((char *)pslave_list[i].version, (char *)p);

		p = pblock + CHUNK_TIME;
		STRCPY((char *)pslave_list[i].time, (char *)p);

#if (defined HDCP_IN_FLASH ||defined DIVX_CERT_ENABLE)
#ifdef HDCP_IN_FLASH
		if(m_allcode_include_bootloader==0)
#endif		
		{
			UINT32 special_type = 0;

#ifdef HDCP_IN_FLASH		
			if(pslave_list[i].id == HDCPKEY_CHUNK_ID)
			{
				special_type =1;
			}
#endif			
#ifdef DIVX_CERT_ENABLE		
			if(pslave_list[i].id == DIVX_CHUCK_ID)
			{
				special_type =1;
			}
#endif			
			if(special_type!=1)
			{
				MEMCPY((temp_pslave_list+temp_slave_blocks_number),(pslave_list+i),sizeof(CHUNK_HEADER));
				temp_slave_blocks_number++;			
			}
			else
			{ 
				if(i > 0)
				{
					temp_pslave_list[i-1].offset=(temp_pslave_list[i-1].offset+pslave_list[i].offset);
				}
			}
		}
#endif

		pblock += CHUNK_HEADER_SIZE;
	}

#if (defined HDCP_IN_FLASH ||defined DIVX_CERT_ENABLE)
#ifdef  HDCP_IN_FLASH
		if(m_allcode_include_bootloader==0)
#endif		
		{
			FREE(pslave_list);
			slave_blocks_number=temp_slave_blocks_number;
			pslave_list = (CHUNK_HEADER *)MALLOC(sizeof(CHUNK_HEADER)*slave_blocks_number);
			MEMCPY(pslave_list,temp_pslave_list,sizeof(CHUNK_HEADER)*slave_blocks_number);
			FREE(temp_pslave_list);
		}
#endif


	STRCPY(sVer, pslave_list[0].version);
	chunk_pos = sto_chunk_goto(&pblock_list[0].id, 0xFFFFFFFF, 1);
	sto_dev = (struct sto_device*)dev_get_by_id(HLD_DEV_TYPE_STO, 0);
	sto_open(sto_dev);
	sto_lseek(sto_dev, chunk_pos+CHUNK_VERSION, STO_LSEEK_SET);
	sto_read(sto_dev, hVer, 16);
	//sto_close(sto_dev);

#ifdef FORCE_UPGRADE_OLD_PROTOCOL_BOOTLOADER
	if(g_protocol_version < NEW_PROTOCOL_VERSION)
		return SUCCESS;
#endif
	if(CheckVersion(sVer, hVer) != SUCCESS)
	{
		ComUniStrToAsc((UINT8 *)OSD_GetUnicodeString(RS_STB_VERSION_NOT_COMPATIBLE),strTmp);
		callback_fun(2,0,strTmp);
		return !SUCCESS;
	}
}