//fpga and switch reg reload
int sys_reg_load_form_yangy(void)
{
	char buff[100];
	int i,ret,j;
	FILE *fp;
	int  addr_s;
	char *pbuf = buff;
	short *pdata = malloc(16*sizeof(short));
	int pswitch = 0;
    int val;
    int tmp_vid;
    int reg;
    DEBUG(GLOBAL_OUT_GROUP,"%s:%d",__FUNCTION__,__LINE__);
	fp = fopen("/etc/fpgaconfig","r");
	if(fp==NULL){

		return -1;
	}

	while((strstr(buff,"[FPGA REGS]") == NULL) && !feof(fp))
		fgets(buff,100,fp);

	// find FPGA REG CONFIG INFORMATION
	while(!feof(fp)){

		fgets(buff,100,fp);

		if(buff[0]=='[')
			break;
		if((buff[0]=='\r')||(buff[0]=='\n'))
			continue;

		pbuf = buff;
		addr_s=0;
		addr_s = strtol(pbuf,NULL,16)&0xffff;
		//DEBUG(GLOBAL_OUT_GROUP," %04hx,",addr_s);
		//usleep(1);
		pbuf +=5;
				/*
        for(i=0;i<16;i++){
            if((*pbuf=='\r') || (*pbuf == '\n') || (*pbuf == '\0')) break;
			reg_Val = strtol(pbuf,NULL,16);
			*(pdata+i)=reg_Val;
            sys_wr_fpga_reg(((addr_s+i)),reg_Val);  //<<1
            pbuf +=5;
		}

		memset(tmp_buf,0,sizeof(tmp_buf));

        tmp_len=sprintf(tmp_buf,"%04hx:",addr_s&0xffff);
		for(i=0;i<16;i++){

            tmp_len+=sprintf(tmp_buf+tmp_len,"%04hx ",(*(pdata+i))&0xffff);
		}
		DEBUG(GLOBAL_OUT_GROUP,"%s",tmp_buf);
		*/

		for(i=0;i<16;i++){
            if((*pbuf=='\r') || (*pbuf == '\n') || (*pbuf == '\0')) break;
			*(pdata+i) = strtol(pbuf,NULL,16);
			pbuf +=5;

		}
		sys_wr_fpga_continue((addr_s),pdata,i*2);
	}
	free(pdata);
	fclose(fp);

    usleep(100);

	fp = fopen("/etc/fpgaconfig","r");
	if(fp==NULL){

		return -1;
	}
    memset(buff,0,100);
	while((strstr(buff,"[88E6161 REGS]") == NULL) && (!feof(fp)) )
		fgets(buff,100,fp);
    addr_s=0x0;
    while(!feof(fp)){
        //memset(buff,0,100);
		fgets(buff,100,fp);
		if(buff[0]=='[')
			break;
		if((buff[0]=='\r')||(buff[0]=='\n'))
			continue;
		pbuf = buff;
		for(j=0;j<6;j++){
			//*(pdata+i) = strtol(pbuf,NULL,16);
			val = strtol(pbuf,NULL,16);
			if((*pbuf=='\r') || (*pbuf == '\n') || (*pbuf == '\0')) break;
			smiWriteReg(addr_s++,0,val);
			pbuf +=5;
			//DEBUG(GLOBAL_OUT_GROUP,"phyaddr=0x%2x,regaddr=0x%2x,value=0x%4x\n",i,j,val);
		}
		if(j>=6) break;
	}
    addr_s=0x10;
    while(!feof(fp)){
        //memset(buff,0,100);
		fgets(buff,100,fp);
		if(buff[0]=='[')
			break;
		if((buff[0]=='\r')||(buff[0]=='\n'))
			continue;
		pbuf = buff;
		for(j=0;(j<16);j++){
			//*(pdata+i) = strtol(pbuf,NULL,16);
			val = strtol(pbuf,NULL,16);
			if((*pbuf=='\r') || (*pbuf == '\n') || (*pbuf == '\0')) break;
			smiWriteReg(addr_s,j,val);
			pbuf +=5;
			//DEBUG(GLOBAL_OUT_GROUP,"phyaddr=0x%2x,regaddr=0x%2x,value=0x%4x\n",i,j,val);
		}
		addr_s++;
		if(addr_s>=0x16) break;
	}
	while(!feof(fp)){
        memset(buff,0,100);
        fgets(buff,15,fp);

		if(buff[0]=='[')
			break;
		if((buff[0]=='\r'))
            continue;
        if(buff[0]=='\n')
			continue;

		pbuf = buff;
		init_read_times();
        reg=0;
        while((reg&0x8000) && read_times_larger_than_0())
        {
            smiReadReg(0x1b,5,&reg);
        }

        val = strtol(pbuf,NULL,16)&0xffff;
        pbuf +=5;
        //syslog(LOG_DAEMON,"%s:vid=%x",__FUNCTION__,val);
        if( ((val & 0x1000)==0) || ((val&0xfff) == 0xfff) || val==0 ) break;
        tmp_vid = (val&0xffff);

        val = strtol(pbuf,NULL,16)&0xffff;
        pbuf +=5;
        smiWriteReg(0x1b,7,val);

        val = strtol(pbuf,NULL,16)&0xffff;
        pbuf +=5;
        smiWriteReg(0x1b,8,val);

//        val = strtol(pbuf,NULL,16)&0xffff;
//        pbuf +=5;
//        smiWriteReg(0x1b,9,val);

        smiWriteReg(0x1b,6,(tmp_vid&0xffff));
        smiWriteReg(0x1b,2,0);

        smiWriteReg(0x1b,5,0xb000);
    }
	fclose(fp);
    //if(pswitch>0)
       // close(pswitch);

	return 0;

}