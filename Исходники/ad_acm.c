static int decode_audio(sh_audio_t *sh_audio,unsigned char *buf,int minlen,int maxlen)
{
    ACMSTREAMHEADER ash;
    HRESULT hr;
    DWORD srcsize=0;
    DWORD len=minlen;
    acm_context_t *priv = sh_audio->context;

    acmStreamSize(priv->handle, len, &srcsize, ACM_STREAMSIZEF_DESTINATION);
    mp_msg(MSGT_WIN32,MSGL_DBG3,"acm says: srcsize=%ld  (buffsize=%d)  out_size=%ld\n",srcsize,sh_audio->a_in_buffer_size,len);

    if(srcsize<sh_audio->wf->nBlockAlign){
       srcsize=sh_audio->wf->nBlockAlign;
       acmStreamSize(priv->handle, srcsize, &len, ACM_STREAMSIZEF_SOURCE);
       if(len>maxlen) len=maxlen;
    }

//    if(srcsize==0) srcsize=((WAVEFORMATEX *)&sh_audio->o_wf_ext)->nBlockAlign;
    if(srcsize>sh_audio->a_in_buffer_size) srcsize=sh_audio->a_in_buffer_size; // !!!!!!
    if(sh_audio->a_in_buffer_len<srcsize){
      sh_audio->a_in_buffer_len+=
        demux_read_data(sh_audio->ds,&sh_audio->a_in_buffer[sh_audio->a_in_buffer_len],
        srcsize-sh_audio->a_in_buffer_len);
    }
    mp_msg(MSGT_WIN32,MSGL_DBG3,"acm convert %d -> %ld bytes\n",sh_audio->a_in_buffer_len,len);
    memset(&ash, 0, sizeof(ash));
    ash.cbStruct=sizeof(ash);
    ash.fdwStatus=0;
    ash.dwUser=0;
    ash.pbSrc=sh_audio->a_in_buffer;
    ash.cbSrcLength=sh_audio->a_in_buffer_len;
    ash.pbDst=buf;
    ash.cbDstLength=len;
    hr=acmStreamPrepareHeader(priv->handle,&ash,0);
    if(hr){
      mp_msg(MSGT_WIN32,MSGL_V,"ACM_Decoder: acmStreamPrepareHeader error %d\n",(int)hr);
      return -1;
    }
    hr=acmStreamConvert(priv->handle,&ash,0);
    if(hr){
      mp_msg(MSGT_WIN32,MSGL_DBG2,"ACM_Decoder: acmStreamConvert error %d\n",(int)hr);
      switch(hr)
      {
	case ACMERR_NOTPOSSIBLE:
	case ACMERR_UNPREPARED:
	    mp_msg(MSGT_WIN32, MSGL_DBG2, "ACM_Decoder: acmStreamConvert error: probarly not initialized!\n");
      }
//      return -1;
    }
    mp_msg(MSGT_WIN32,MSGL_DBG2,"acm converted %ld -> %ld\n",ash.cbSrcLengthUsed,ash.cbDstLengthUsed);
    if(ash.cbSrcLengthUsed>=sh_audio->a_in_buffer_len){
      sh_audio->a_in_buffer_len=0;
    } else {
      sh_audio->a_in_buffer_len-=ash.cbSrcLengthUsed;
      memcpy(sh_audio->a_in_buffer,&sh_audio->a_in_buffer[ash.cbSrcLengthUsed],sh_audio->a_in_buffer_len);
    }
    len=ash.cbDstLengthUsed;
    hr=acmStreamUnprepareHeader(priv->handle,&ash,0);
    if(hr){
      mp_msg(MSGT_WIN32,MSGL_V,"ACM_Decoder: acmStreamUnprepareHeader error %d\n",(int)hr);
    }
    return len;
}