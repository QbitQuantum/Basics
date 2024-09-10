void COpenProgDlg::Write18Fx(int dim,int dim2,int wbuf=8,int eraseW1=0x10000,int eraseW2=0x10000,int options=0)
// write 16 bit PIC 18Fxxxx
// dim=program size 	dim2=eeprom size	wbuf=write buffer size {<=64}
// eraseW1=erase word @3C0005	(not used if > 0x10000)
// eraseW2=erase word @3C0004	(not used if > 0x10000)
// options:
//	bit [3:0]
//     0 = vdd before vpp (12V)
//     1 = vdd before vpp (9V)
//     2 = low voltage entry with 32 bit key
//	bit [7:4]
//     0 = normal eeprom write algoritm
//     1 = with unlock sequence 55 AA
//	bit [11:8]
//     0 = 5ms erase delay, 1ms code write time, 5ms EE write delay, 5ms config write time
//     1 = 550ms erase delay, 1.2ms code write time, no config or EEPROM
//     2 = 550ms erase delay, 3.4ms code write time, no config or EEPROM
{
	CString str;
	int size=memCODE.GetSize(),sizeEE=memEE.GetSize();
	int k=0,k2,z=0,i,j;
	int err=0,devID=0;
	int EEalgo=(options>>4)&0xF,entry=options&0xF,optWrite=(options>>8)&0xF;
	if(dim>0x1FFFFF||dim<0){
		PrintMessage(strings[S_CodeLim]);	//"Code size out of limits\r\n"
		return;
	}
	if(dim2>0x800||dim2<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(wbuf>64){
		PrintMessage(strings[S_WbufLim]);	//"Write buffer size out of limits\r\n"
		return;
	}
	if(entry==2&&!CheckV33Regulator()){
		PrintMessage(strings[S_noV33reg]);	//Can't find 3.3V expansion board
		return;
	}
	double vpp=entry<2?(entry==0?12:8.5):-1;
	if(!StartHVReg(vpp)){
		PrintMessage(strings[S_HVregErr]); //"HV regulator error\r\n"
		return;
	}
	if(saveLog){
		OpenLogFile();	//"log.txt"
		fprintf(logfile,"Write18F(%d,%d,%d,%d)    (0x%X,0x%X,0x%X,0x%X)\n",dim,dim2,wbuf,options,dim,dim2,wbuf,options);
	}
	if(dim>size) dim=size;
	if(dim%wbuf){			//grow to an integer number of rows
		dim+=wbuf-dim%wbuf;
		j=size;
		if(j<dim)memCODE.SetSize(dim);
		for(;j<dim;j++) memCODE[j]=0xFF;
	}
	if(dim2>sizeEE) dim2=sizeEE;
	if(dim<1){
		PrintMessage(strings[S_NoCode]);	//"Empty data area\r\n"
		return;
	}
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T1T2;
	bufferU[j++]=1;						//T1=1u
	bufferU[j++]=100;					//T2=100u
	bufferU[j++]=EN_VPP_VCC;		//enter program mode
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;		//VDD+VPP
	bufferU[j++]=0x5;
	if(entry==2){					//LV entry with key
		bufferU[j++]=EN_VPP_VCC;		//VDD
		bufferU[j++]=0x1;
		bufferU[j++]=WAIT_T3;
		bufferU[j++]=WAIT_T3;
		bufferU[j++]=TX16;
		bufferU[j++]=2;
		bufferU[j++]=0x4D;
		bufferU[j++]=0x43;
		bufferU[j++]=0x48;
		bufferU[j++]=0x50;
		bufferU[j++]=EN_VPP_VCC;		//VDD+VPP
		bufferU[j++]=0x5;
		bufferU[j++]=WAIT_T3;
	}
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x0E;			//3F
	bufferU[j++]=0x3F;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x6E;			//-> TBLPTRU
	bufferU[j++]=0xF8;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x0E;			//FF
	bufferU[j++]=0xFF;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x6E;			//-> TBLPTRH
	bufferU[j++]=0xF7;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x0E;			//FE
	bufferU[j++]=0xFE;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x6E;			//-> TBLPTRL
	bufferU[j++]=0xF6;
	bufferU[j++]=TBLR_INC_N;		//DevID1-2	0x3FFFFE-F
	bufferU[j++]=2;
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T3;
	bufferU[j++]=5100>>8;
	bufferU[j++]=5100&0xff;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(3);
	if(entry==2) msDelay(7);
	read();
	if(saveLog)WriteLogIO();
	for(z=1;bufferI[z]!=TBLR_INC_N&&z<DIMBUF;z++);
	if(z<DIMBUF-3){
		PrintMessage2(strings[S_DevID2],bufferI[z+3],bufferI[z+2]);	//"DevID: 0x%02X%02X\r\n"
		PIC18_ID(bufferI[z+2]+(bufferI[z+3]<<8));
	}
	j=1;
//****************** erase memory ********************
	PrintMessage(strings[S_StartErase]);	//"Erase ... "
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x0E;			//3C
	bufferU[j++]=0x3C;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x6E;			//-> TBLPTRU
	bufferU[j++]=0xF8;
	bufferU[j++]=CORE_INS;
	bufferU[j++]=0x6A;			//TBLPTRH=0
	bufferU[j++]=0xF7;
	if(eraseW1<0x10000){
		bufferU[j++]=CORE_INS;
		bufferU[j++]=0x0E;			//05
		bufferU[j++]=0x05;
		bufferU[j++]=CORE_INS;
		bufferU[j++]=0x6E;			//-> TBLPTRL
		bufferU[j++]=0xF6;
		bufferU[j++]=TABLE_WRITE;		// eraseW1@3C0005
		bufferU[j++]=(eraseW1>>8)&0xFF; 	//0x3F;
		bufferU[j++]=eraseW1&0xFF; 		//0x3F;
	}