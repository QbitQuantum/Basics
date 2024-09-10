int a52_fillbuff(sh_audio_t *sh_audio){
int length=0;
int flags=0;
int sample_rate=0;
int bit_rate=0;

    sh_audio->a_in_buffer_len=0;
    /* sync frame:*/
while(1){
    while(sh_audio->a_in_buffer_len<8){
	int c=demux_getc(sh_audio->ds);
	if(c<0) return -1; /* EOF*/
        sh_audio->a_in_buffer[sh_audio->a_in_buffer_len++]=c;
    }
    if(sh_audio->format!=0x2000) swab(sh_audio->a_in_buffer,sh_audio->a_in_buffer,8);
    length = a52_syncinfo (sh_audio->a_in_buffer, &flags, &sample_rate, &bit_rate);
    if(length>=7 && length<=3840) break; /* we're done.*/
    /* bad file => resync*/
    if(sh_audio->format!=0x2000) swab(sh_audio->a_in_buffer,sh_audio->a_in_buffer,8);
    memmove(sh_audio->a_in_buffer,sh_audio->a_in_buffer+1,7);
    --sh_audio->a_in_buffer_len;
}
    mp_msg(MSGT_DECAUDIO,MSGL_DBG2,"a52: len=%d  flags=0x%X  %d Hz %d bit/s\n",length,flags,sample_rate,bit_rate);
    sh_audio->samplerate=sample_rate;
    sh_audio->i_bps=bit_rate/8;
    sh_audio->samplesize=sh_audio->sample_format==AF_FORMAT_FLOAT_NE ? 4 : 2;
    demux_read_data(sh_audio->ds,sh_audio->a_in_buffer+8,length-8);
    if(sh_audio->format!=0x2000)
	swab(sh_audio->a_in_buffer+8,sh_audio->a_in_buffer+8,length-8);
    
    if(crc16_block(sh_audio->a_in_buffer+2,length-2)!=0)
	mp_msg(MSGT_DECAUDIO,MSGL_STATUS,"a52: CRC check failed!  \n");
    
    return length;
}