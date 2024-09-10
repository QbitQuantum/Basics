void COpenProgDlg::Write12F5xx(int dim,int OscAddr)
{
// write 12 bit PIC
// dim=program size     max~4300=10CC
// OscAddr=OSCCAL address (saved at the beginning), -1 not to use it
// vdd before vpp
// CONFIG @ 0x7FF upon entering program mode
// BACKUP OSCCAL @ dim+5 (saved at the beginning)
// erase: BULK_ERASE_PROG (1001) +10ms
// write: BEGIN_PROG (1000) + Tprogram 2ms + END_PROG2 (1110);
	CString str;
	int usa_BKosccal,usa_osccal,size;
	int k=0,z=0,i,j,w;
	int err=0;
	WORD osccal=-1,BKosccal=-1;
	if(OscAddr>dim) OscAddr=dim-1;
	CButton* b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_OSCCAL);
	usa_osccal=b->GetCheck();
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_BK);
	usa_BKosccal=b->GetCheck();
	size=dati_hex.GetSize();
	if(OscAddr==-1) usa_BKosccal=usa_osccal=0;
	if(size<0x1000){
		PrintMessage(strings[S_NoConfigW2]);	//"Impossibile trovare la locazione CONFIG (0xFFF)\r\n"
		return;
	}
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Write12F5xx(%d,%d)\n",dim,OscAddr);
	}
	for(i=0;i<size;i++) dati_hex[i]&=0xFFF;
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
	bufferU[j++]=NOP;
	bufferU[j++]=EN_VPP_VCC;		//VDD+VPP
	bufferU[j++]=0x5;
	bufferU[j++]=NOP;
	if(OscAddr!=-1){
		for(i=-1;i<OscAddr-0xff;i+=0xff){
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=0xff;
		}
		bufferU[j++]=INC_ADDR_N;
		bufferU[j++]=OscAddr-i;
		bufferU[j++]=READ_DATA_PROG;	// OSCCAL
		if(OscAddr<dim){
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=dim-OscAddr;
		}
		bufferU[j++]=INC_ADDR_N;
		bufferU[j++]=0x4;				// 400->404
		bufferU[j++]=READ_DATA_PROG;	// backup OSCCAL
	}
	bufferU[j++]=NOP;				//uscita program mode
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T3;
	bufferU[j++]=10000>>8;
	bufferU[j++]=10000&0xff;
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(15);
	read();
	if(saveLog)WriteLogIO();
	if(OscAddr!=-1){
		for(z=4;z<DIMBUF-2&&bufferI[z]!=READ_DATA_PROG;z++);
		if(z<DIMBUF-2) osccal=(bufferI[z+1]<<8)+bufferI[z+2];
		for(z+=3;z<DIMBUF-2&&bufferI[z]!=READ_DATA_PROG;z++);
		if(z<DIMBUF-2) BKosccal=(bufferI[z+1]<<8)+bufferI[z+2];
		if(osccal==-1||BKosccal==-1){
			PrintMessage(strings[S_ErrOsccal]);	//"Errore in lettura OSCCAL e BKOSCCAL"
			PrintMessage("\r\n");
			return;
		}
		PrintMessage1(strings[S_Osccal],osccal);	//"OSCCAL: 0x%03X\r\n"
		PrintMessage1(strings[S_BKOsccal],BKosccal);	//"Backup OSCCAL: 0x%03X\r\n"
	}
//****************** erase memory ********************
	PrintMessage(strings[S_StartErase]);	//"Cancellazione ... "
	j=1;
	bufferU[j++]=EN_VPP_VCC;			// enter program mode
	bufferU[j++]=0x1;
	bufferU[j++]=NOP;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x5;
	if(dim>OscAddr+1){				//12F519 (Flash+EEPROM)
		bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
		bufferU[j++]=WAIT_T3;			// delay T3=10ms
		for(i=-1;i<dim-0xff;i+=0xff){	// 0x43F
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=0xff;
		}
		bufferU[j++]=INC_ADDR_N;
		bufferU[j++]=dim-i-1;
		bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase EEPROM
		bufferU[j++]=WAIT_T3;			// delay T3=10ms
		if(programID){
			bufferU[j++]=INC_ADDR;
			bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
			bufferU[j++]=WAIT_T3;			// delay T3=10ms
		}
	}
	else{							//12Fxxx
		if(programID){
			for(i=-1;i<dim-0xff;i+=0xff){
				bufferU[j++]=INC_ADDR_N;
				bufferU[j++]=0xff;
			}
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=dim-i;
			bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
			bufferU[j++]=WAIT_T3;			// delay T3=10ms
		}
		else{
			bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
			bufferU[j++]=WAIT_T3;			// delay T3=10ms
		}
	}
	bufferU[j++]=EN_VPP_VCC;		// uscita program mode
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=WAIT_T3;			// delay T3=10ms before entering program mode
	bufferU[j++]=EN_VPP_VCC;		// enter program mode
	bufferU[j++]=0x1;
	bufferU[j++]=NOP;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x5;
	bufferU[j++]=INC_ADDR;				// 7FF->000
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T3;
	bufferU[j++]=2000>>8;				//T3=2ms
	bufferU[j++]=2000&0xff;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(30);
	if(dim>OscAddr+1) msDelay(20);
	read();
	PrintMessage(strings[S_Compl]);	//"completed\r\n"
	if(saveLog)WriteLogIO();
//****************** write code ********************
	PrintMessage(strings[S_StartCodeProg]);	//"Scrittura codice ... "
	int dim1=dim;
	if(programID) dim1=dim+5;
	if(dati_hex[dim+4]>=0xFFF) dati_hex[dim+4]=BKosccal;  //reload BKosccal if not present
	if(usa_BKosccal) dati_hex[OscAddr]=BKosccal;
	else if(usa_osccal) dati_hex[OscAddr]=osccal;
	for(i=k=w=0,j=1;i<dim1;i++){
		if(dati_hex[i]<0xfff){
			bufferU[j++]=LOAD_DATA_PROG;
			bufferU[j++]=dati_hex[i]>>8;		//MSB
			bufferU[j++]=dati_hex[i]&0xff;		//LSB
			bufferU[j++]=BEGIN_PROG;
			bufferU[j++]=WAIT_T3;				//Tprogram 2ms
			bufferU[j++]=END_PROG2;
			bufferU[j++]=WAIT_T2;				//Tdischarge
			bufferU[j++]=READ_DATA_PROG;
			w++;
		}
		bufferU[j++]=INC_ADDR;
		if(j>DIMBUF-10||i==dim1-1){
			PrintStatus(strings[S_CodeWriting],i*100/dim,i);	//"Write: %d%%, ind. %03X"
			bufferU[j++]=FLUSH;
			for(;j<DIMBUF;j++) bufferU[j]=0x0;
			write();
			msDelay(w*3+3);
			w=0;
			read();
			for(z=1;z<DIMBUF-7;z++){
				if(bufferI[z]==INC_ADDR&&dati_hex[k]>=0xfff) k++;
				else if(bufferI[z]==LOAD_DATA_PROG&&bufferI[z+5]==READ_DATA_PROG){
					if (dati_hex[k]!=(bufferI[z+6]<<8)+bufferI[z+7]){
						PrintMessage("\r\n");
						PrintMessage3(strings[S_CodeWError],k,dati_hex[k],(bufferI[z+6]<<8)+bufferI[z+7]);	//"Errore in scrittura all'indirizzo %3X: scritto %03X, letto %03X\r\n"
						err++;
						if(max_err&&err>max_err){
							PrintMessage1(strings[S_MaxErr],err);	//"Exceeded maximum number of errors (%d), write interrupted\r\n"
							PrintMessage(strings[S_IntW]);	//"write interrupted"
							i=dim1;
							z=DIMBUF;
						}
					}
					k++;
					z+=8;
				}
			}
			j=1;
			if(saveLog){
				fprintf(logfile,strings[S_Log8],i,i,k,k,err);	//"i=%d, k=%d, errori=%d\n"
				WriteLogIO();
			}
		}
	}