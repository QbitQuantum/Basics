int8 Wechat_data_produce(void *args, uint8 **r_data, uint32 *r_len)
{
	static uint16 bleDemoHeadLen = sizeof(WechatBlueDemoHead);
	wechat_info *info = (wechat_info *)args;
	BaseRequest basReq = {NULL};
	static uint8 fix_head_len = sizeof(BpFixHead);
	BpFixHead fix_head = {0xFE, 1, 0, htons(ECI_req_auth), 0};
	wechatSta.seq++;
	int ret;

	switch (info->cmd)
	{
		case WECHAT_CMD_AUTH:
		{
			#if defined EAM_md5AndAesEnrypt
			uint8 deviceid[] = DEVICE_ID;
			static uint32 seq = 0x00000001;//
			uint32 ran = 0x11223344;//ÎªÁË·½±ãÆð¼ûÕâÀï·ÅÁËÒ»¸ö¹Ì¶¨Öµ×öÎªËæ»úÊý£¬ÔÚÊ¹ÓÃÊ±Çë×ÔÐÐÉú³ÉËæ»úÊý¡£
			ran = t_htonl(ran);
			seq = t_htonl(seq);
			uint8 id_len = osal_strlen(DEVICE_ID);
			uint8* data = osal_mem_alloc(id_len+8);
			if(!data)
			{
				NPI_Printf("Not enough memory!\r\n");
				return ( bleMemAllocError );
			}

			memcpy(data,deviceid,id_len);
			memcpy(data+id_len,(uint8*)&ran,4);
			memcpy(data+id_len+4,(uint8*)&seq,4);
			uint32 crc = crc32(0, data, id_len+8);
			crc = t_htonl(crc);
			NPI_Printf("Wechat_data_produce 0x%x!\r\n", crc);
			osal_memset(data,0x00,id_len+8);
			memcpy(data,(uint8*)&ran,4);
			memcpy(data+4,(uint8*)&seq,4);
			memcpy(data+8,(uint8*)&crc,4);	
			//uint8 CipherText[16];
			//AES_Init(key);
			//AES_Encrypt_PKCS7 (data, CipherText, 12, key);
			uint8 CipherText[128];
			encrypt_data(data, CipherText, key);
			if(data)
			{
				osal_mem_free(data);
				data = NULL;
			}
			AuthRequest authReq = {
				&basReq, 
				true,
				{md5_type_and_id, MD5_TYPE_AND_ID_LENGTH}, 
				PROTO_VERSION, 
				AUTH_PROTO, 
				(EmAuthMethod)AUTH_METHOD, 
				true ,
				{CipherText, CIPHER_TEXT_LENGTH}, 
				false, 
				{NULL, 0}, 
				false, 
				{NULL, 0}, 
				false, 
				{NULL, 0},
				true,
				{DEVICE_ID,sizeof(DEVICE_ID)}
			};
			seq++;
			#endif
				
			#if defined EAM_macNoEncrypt
			static uint8 mac_address[MAC_ADDRESS_LENGTH];
			wechat_get_mac_addr(mac_address);
			AuthRequest authReq = {
				&basReq, 
				false,
				{NULL, 0}, 
				PROTO_VERSION, 
				AUTH_PROTO, 
				(EmAuthMethod)AUTH_METHOD, 
				false,
				{NULL, 0}, 
				true, 
				{mac_address, MAC_ADDRESS_LENGTH}, 
				false, 
				{NULL, 0}, 
				false, 
				{NULL, 0},
				true,
				{DEVICE_ID,sizeof(DEVICE_ID)}
			};
			#endif
				
			#if defined EAM_md5AndNoEnrypt
				AuthRequest authReq = {
					&basReq, 
					true,
					{md5_type_and_id, MD5_TYPE_AND_ID_LENGTH}, 
					PROTO_VERSION, 
					(EmAuthMethod)AUTH_PROTO, 
					(EmAuthMethod)AUTH_METHOD, 
					false ,
					{NULL, 0}, 
					false, 
					{NULL, 0}, 
					false, 
					{NULL, 0}, 
					false, 
					{NULL, 0},
					true,
					{DEVICE_ID,sizeof(DEVICE_ID)}
				};
			#endif

			*r_len = (uint32)epb_auth_request_pack_size(&authReq) + fix_head_len;
			*r_data = (uint8 *)osal_mem_alloc(*r_len);
			if(!(*r_data))
			{
				NPI_Printf("Not enough memory!\r\n");
				return ( bleMemAllocError );
			}
			ret = epb_pack_auth_request(&authReq, *r_data+fix_head_len, *r_len-fix_head_len);
			if( ret <0)
			{
				osal_mem_free(*r_data);
				*r_data = NULL;
				NPI_Printf("epb pack auth request failed!\r\n");
				return ret;
			}

			fix_head.nCmdId = htons(ECI_req_auth);
			fix_head.nLength = htons((uint16)*r_len);
			fix_head.nSeq = htons(wechatSta.seq);
			memcpy(*r_data, &fix_head, fix_head_len);
			break;
		}

		case WECHAT_CMD_INIT:
		{
			//has challeange
			InitRequest initReq = {&basReq,false, {NULL, 0},true, {challeange, CHALLENAGE_LENGTH}};
			*r_len = epb_init_request_pack_size(&initReq) + fix_head_len;
			#if defined EAM_md5AndAesEnrypt
			uint8 length = *r_len;				
			uint8 *p = osal_mem_alloc(AES_get_length( *r_len-fix_head_len));
			if(!p)
			{
				NPI_Printf("Not enough memory!\r\n");
				return ( bleMemAllocError );
			}
			*r_len = AES_get_length( *r_len-fix_head_len)+fix_head_len;
			#endif
			
			//pack data
			*r_data = (uint8 *)osal_mem_alloc(*r_len);
			if(!(*r_data))
			{
				NPI_Printf("Not enough memory!\r\n");
				return ( bleMemAllocError );
			}

			ret = epb_pack_init_request(&initReq, *r_data+fix_head_len, *r_len-fix_head_len);
			if( ret < 0 )
			{
				osal_mem_free(*r_data);
				*r_data = NULL;
				return ret;
			}

			//encrypt body
			#if defined EAM_md5AndAesEnrypt
			//AES_Init(session_key);
			//AES_Encrypt_PKCS7(*r_data+fix_head_len,p,length-fix_head_len,session_key);//Ô­Ê¼Êý¾Ý³¤¶È
			//uint8 CipherText[128];
			encrypt_data(*r_data+fix_head_len,p, session_key);

			memcpy(*r_data + fix_head_len, p, *r_len-fix_head_len);
			if(p)
				osal_mem_free(p);
			#endif
			
			fix_head.nCmdId = htons(ECI_req_init);
			fix_head.nLength = htons(*r_len);
			fix_head.nSeq = htons(wechatSta.seq);
			memcpy(*r_data, &fix_head, fix_head_len);
			break;
		}
		case WECHAT_CMD_TEST_SENDDAT:
		{
			//NPI_Printf("test msg to send : %s \r\n",(uint8*)info->send_msg.str);
			
			WechatBlueDemoHead  *bleDemoHead = (WechatBlueDemoHead*)osal_mem_alloc(bleDemoHeadLen+info->send_msg.len);
			if(!bleDemoHead)
			{
				NPI_Printf("Not enough memory!\r\n");
				return ( bleMemAllocError );
			}

			bleDemoHead->m_magicCode[0] = WECHAT_MAGICCODE_H;
			bleDemoHead->m_magicCode[1] = WECHAT_MAGICCODE_L;
			bleDemoHead->m_version = htons( WECHAT_VERSION);
			bleDemoHead->m_totalLength = htons(bleDemoHeadLen + info->send_msg.len);
			bleDemoHead->m_cmdid = htons(sendTextReq);
			bleDemoHead->m_seq = htons(wechatSta.seq);
			bleDemoHead->m_errorCode = 0;	

			/*connect body and head.*/
			/*turn to uint8* befort offset.*/
			memcpy((uint8*)bleDemoHead+bleDemoHeadLen, info->send_msg.str, info->send_msg.len);			
			SendDataRequest sendDatReq = {&basReq, {(uint8*) bleDemoHead, (bleDemoHeadLen + info->send_msg.len)}, false, (EmDeviceDataType)NULL};
			*r_len = epb_send_data_request_pack_size(&sendDatReq) + fix_head_len;

			#if defined EAM_md5AndAesEnrypt
			uint16 length = *r_len;
			uint8 *p = osal_mem_alloc(AES_get_length( *r_len-fix_head_len));
			if(!p)
			{
				NPI_Printf("Not enough memory!\r\n");
				return ( bleMemAllocError );
			}
			*r_len = AES_get_length( *r_len-fix_head_len)+fix_head_len;
			#endif
			
			*r_data = (uint8 *)osal_mem_alloc(*r_len);
			if(!(*r_data))
			{
				NPI_Printf("Not enough memory!\r\n");
				return ( bleMemAllocError );
			}

			ret = epb_pack_send_data_request(&sendDatReq, *r_data+fix_head_len, *r_len-fix_head_len);
			if( ret < 0 )
			{
				*r_data = NULL;

				#if defined EAM_md5AndAesEnrypt
				if(p)
				{
					osal_mem_free(p);
					p = NULL;
				}
				#endif

				NPI_Printf("\r\nepb_pack_send_data_request error!");
				return ret;
			}

			#if defined EAM_md5AndAesEnrypt
			//encrypt body
			//AES_Init(session_key);
			//AES_Encrypt_PKCS7(*r_data+fix_head_len,p,length-fix_head_len,session_key);//Ô­Ê¼Êý¾Ý³¤¶È
			encrypt_data(*r_data+fix_head_len,p, session_key);
			memcpy(*r_data + fix_head_len, p, *r_len-fix_head_len);
			if(p)
			{
				osal_mem_free(p); 
				p = NULL;
			}
			#endif
			fix_head.nCmdId = htons(ECI_req_sendData);
			fix_head.nLength = htons(*r_len);
			fix_head.nSeq = htons(wechatSta.seq);
			memcpy(*r_data, &fix_head, fix_head_len);
			if(bleDemoHead)
			{
				osal_mem_free(bleDemoHead);
				bleDemoHead = NULL;
			}

#if 0
			NPI_Printf("##send data: ");
			uint8 *d = *r_data;
			for(uint8 i=0;i<*r_len;++i)
			{
				NPI_Printf(" %x",d[i]);
			}
			BpFixHead *fix_head = (BpFixHead *)*r_data;
			NPI_Printf("\r\n CMDID: %d\r\n",ntohs(fix_head->nCmdId));
			NPI_Printf("len: %d\r\n", ntohs(fix_head->nLength ));
			NPI_Printf("Seq: %d\r\n", ntohs(fix_head->nSeq));
#endif
			wechatSta.send_data_seq++;
			break;
		}
	}	
	return	SUCCESS;
}