// 真正读写操作在这里，这套系统类似于HMI，也是回调函数
//=====================================================================================
static int met_load_para(U16 sno)
{
	if(met_mem.bFlag==0x5A)
		if(met_mem.pbuf!=NULL && met_mem.size <= MET_BUF_SIZE)
			if(met_mem.crc==CHECK_CRC(met_mem.pbuf,met_mem.size))
			{
				if(!sno || (met_mem.met<=sno&&sno<(met_mem.met+MET_MAX_ITEM)))
					return 1;
				met_save_para(1);
			}
// 	msg_out("\nLoad met.bin");
	if(met_mem.pbuf==NULL)met_mem.pbuf=(U8*)mem_met;//malloc(MET_BUF_SIZE);
	if(met_mem.pbuf!=NULL)
	{
		FHANDLE fp;
		memset(met_mem.pbuf,0xFF,MET_BUF_SIZE);
		fp=FOPEN("met.bin","r");		//原来如此
		if(fp)
		{
			met_mem.met=(sno/MET_MAX_ITEM)*MET_MAX_ITEM;
			//FSEEK(fp,met_mem.met*MET_ITEM_SIZE,SEEK_SET);
			FREAD(met_mem.pbuf,MET_BUF_SIZE,1,fp);
			FCLOSE(fp);
		}
		else
		{
			//msg_out("\nCreate met.bin");
			fp=FOPEN("met.bin","w");
			if(fp)
			{
				FWRITE(met_mem.pbuf,MET_BUF_SIZE,1,fp);
				FCLOSE(fp);
			}
		}
		met_mem.rCnt++;			
		met_mem.met=(sno/MET_MAX_ITEM)*MET_MAX_ITEM + 1;
		met_mem.size=MET_BUF_SIZE;
		met_mem.crc=CHECK_CRC(met_mem.pbuf,met_mem.size);
		met_mem.bFlag=0x5A;
		return 1;		
	}
	return 0;
}