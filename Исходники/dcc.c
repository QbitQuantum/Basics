int dcc_send(void)
{
short count=0;
int16 tstat;
long stat;
char temps[2048],temps2[2048];

while(count<10){
if(dcc[count].dir==DCOUT && dcc[count].stat){
tstat=CNbyte_count(dcc[count].cn);

if(tstat<E_NODATA && dcc[count].stat==SACTIVE){
sprintf(temps2,"**DCC: Error in send to %s",dcc[count].avec);
sendout(temps2,cwin,col[CERRORS]);
resetadcc(count);
if(is_dw_open(dcc[count].dcw))wd_close(dcc[count].dcw);
return 0;
}
if(dcc[count].stat==SAWAIT && tstat>=E_NODATA){
sprintf(temps,"--DCC send to %s connected",dcc[count].avec);
sendout(temps,cwin,col[CDCCINFO]);
dcc[count].stat=SACTIVE;
dcc[count].lack=dcc[count].cnt;
}

if(tstat>=4 && dcc[count].stat==SACTIVE){
CNget_block(dcc[count].cn,(char *)&dcc[count].lack,4);
}
if(dcc[count].lack==dcc[count].cnt && dcc[count].dcfh<0){
sprintf(temps,"--DCC send to %s completed",dcc[count].avec);
sendout(temps,cwin,col[CDCCINFO]);
resetadcc(count);
if(is_dw_open(dcc[count].dcw))wd_close(dcc[count].dcw);
return 0;
} 

if(dcc[count].stat==SACTIVE && dcc[count].lack==dcc[count].cnt){
stat=Fread(dcc[count].dcfh,(long)dctbufsize,(char *)&dcctempbuffer);
if(stat>0)TCP_send(dcc[count].cn,(char *)&dcctempbuffer,(int16)stat);
dobar(dcc[count].dcw,(long)dcc[count].cnt,dcc[count].len,count);
if(stat<dctbufsize){
Fclose(dcc[count].dcfh);
dcc[count].dcfh=-1;
}
dcc[count].cnt=dcc[count].cnt+stat;
}

}
count++;
}
return 0;
}