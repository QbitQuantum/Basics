/*FGROUP SSM_VME_Access ReadSSM
Analyze SSM memory - like AS python + check of serial versus TTC
*/
int analyze(){    
 int i,j,bit,word,ier;
 //int first=1;
 /*         L0 L1s L2s AE  */
 char *SIGname[]={"ORB","PP ","L0 ","L1s","L1d","L2s","L2d","sBU","lBU","1FF","2FF","ChA","ChB","TBU","PPT","SST","STA","AER"};
 int NPR=6;
 char *PRINT[]={"PP ","L0 ","L1s","L2s","AER","LBH"};
 int COUNT[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  /* COUNT SSM signals */
 int COUNTe[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; /* COUNT errors */
 int COUNTl[18]={0,0,-DISTL0,-DISTL1,0,-DISTL2,0,0,0,0,0,0,0,0,0,0,0,0}; /* How close they can be ? */
 int COUNTa[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; /* Is signal active ? */
 int DIST[18]={0,0,DISTL0,DISTL1,0,DISTL2,0,0,0,0,0,0,0,0,0,0,1,0}; /* How close the signals can be ? */
 int L1DATA[NL1dat],L2DATA[NL2dat];
 int iL1d=0,iL2d=0,ivmes=0;
 int iorbi=0,ipp=0,ialls=0;
 int isdb=0,iltb=0,il1fi=0,il2fi=0,icha=0,ittcbusy=0,ippt=0;
 if(readFile()!=0) exit(9);
 dump=NULL;
 analTTCB();
 printf("analTTCB finished \n");
 ttcboffset=1;
 for(i=ttcboffset;i<Mega;i++){
   //if(i %10000 ==0)printf("%i \n",i);
   word=SSMem[i];
   // start only after first L0
   //bit= ( (word & 4) == 4);
   //if(bit) first=0;
   //if(first) continue;
   for(j=0;j<18;j++){
    bit= ( (word & (1<<j)) == (1<<j));
    switch(j){
     case  0:    /* ORBIT   */
	   lsig(0,bit,i,COUNT,COUNTa,&iorbi,"ORBIT");  
           break;
     case  1:    /* PREPULSE    */
           lsig(1,bit,i,COUNT,COUNTa,&ipp," PP");
	   break;
     case  2:  /* L0 */
	   ssig(2,bit,i,COUNT,COUNTa,COUNTl,COUNTe,DIST,"L0");
           break;
     case  3:  /* L1s */  	   
	   asig(3,bit,i,COUNT,COUNTa,COUNTl,COUNTe,DIST,"L1S");
           break;
     case  4:   /* L1data */
	   ier=data(4,bit,i,COUNTa,L1DATA,NL1dat,&iL1d,"L1DATA");
           break;
     case  5:   /* L2 strobe */
           asig(5,bit,i,COUNT,COUNTa,COUNTl,COUNTe,DIST,"L2S");
	   break;
     case  6:   /* L2 data */
	   ier=data(6,bit,i,COUNTa,L2DATA,NL2dat,&iL2d,"L2DATA");
           break;
     case  7: /* Sub Detector Busy */
	   lsig(7,bit,i,COUNT,COUNTa,&isdb,"SBUSY");
           break;
     case  8: /* LTU BUSY */
	   lsig(8,bit,i,COUNT,COUNTa,&iltb,"ALLBUSY");
           break;
     case  9: /* L1 FIFO Nearly Full */
	   lsig(9,bit,i,COUNT,COUNTa,&il1fi,"L1NF");
           break;
     case 10: /* L2 FIFO Nearly Full */
	   lsig(10,bit,i,COUNT,COUNTa,&il2fi,"L2NF");
           break;
     case 11: /* Channel A (L0) */
	   lsig(11,bit,i,COUNT,COUNTa,&icha,"ChanA");
           break;
     case 12:    /*  Channel B */
           //channelB(12,bit,i,COUNT,COUNTa,&ichb,TT,"ChanB");
           break;
     case 13:   /* TTC  BUSY */
           lsig(13,bit,i,COUNT,COUNTa,&ittcbusy,"TTCBUSY"); 
           break;
     case 14:          /* PP transmit */
           lsig(14,bit,i,COUNT,COUNTa,&ippt,"PPT"); 
           break;
     case 15:    /*  vme SLAVE strobe  */
	   lsig(15,bit,i,COUNT,COUNTa,&ivmes,"VMES");
           break;
     case 16:   /* START ALL - emulator */
	   //lsig(16,bit,i,COUNT,COUNTa,&ialls,"ALLSTART");
	   break;
     case 17: /* ANY ERROR */
	   ssig(17,bit,i,COUNT,COUNTa,COUNTl,COUNTe,DIST,"ANYERR");
           break;
    }
   }
 }
 // to take into acount signals up in all memory
 lsig(1,0,Mega,COUNT,COUNTa,&ipp," PP");
 lsig(7,0,Mega,COUNT,COUNTa,&isdb,"SBUSY");
 lsig(8,0,Mega,COUNT,COUNTa,&iltb,"ALLBUSY");
 lsig(9,0,Mega,COUNT,COUNTa,&il1fi,"L1NF");
 lsig(10,0,Mega,COUNT,COUNTa,&il2fi,"L2NF");
 lsig(11,0,Mega,COUNT,COUNTa,&icha,"LBHALT");
 //lsig(12,0,Mega,COUNT,COUNTa,&ivmem,"VMEM");
 lsig(13,0,Mega,COUNT,COUNTa,&ittcbusy,"TTCBUSY"); 
 lsig(15,0,Mega,COUNT,COUNTa,&ivmes,"VMES");
 lsig(16,0,Mega,COUNT,COUNTa,&ialls,"ALLSTART");
 for(i=0;i<NPR;i++){
  for(j=0;j<18;j++)if(SIGname[j] == PRINT[i])
	  printf("<%s=%i> ",SIGname[j],COUNT[j]);
 }
 printf("\n");
 writeLog();
 return 0;
}