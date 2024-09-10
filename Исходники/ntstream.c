int create_stream(WIN32_STREAM_ID *src, struct nt_sid *sid)
{
 DWORD lo, hi, b;

 if(!sid->is_write)
  return(-1);
 if(sid->rem.LowPart!=0&&sid->rem.HighPart!=0)
 {
  if(!BackupSeek(sid->hf, sid->rem.LowPart, sid->rem.HighPart, &lo, &hi, &sid->lpcontext))
   return(-1);
  if(lo!=sid->rem.LowPart||hi!=sid->rem.HighPart)
   return(-1);
  sid->rem.LowPart=sid->rem.HighPart=0;
 }
 if(!BackupWrite(sid->hf, (unsigned char *)src, W32_SID_HEADER_SIZE, &b, FALSE, TRUE, &sid->lpcontext))
  return(-1);
 if(b!=W32_SID_HEADER_SIZE)
  return(-1);
 sid->rem=src->Size;
 return(0);
}