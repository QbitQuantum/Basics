int AmRtpStream::send( unsigned int ts, unsigned char* buffer, unsigned int size )
{
  if ((mute) || (hold))
    return 0;

  if(!size)
    return -1;

  AmRtpPacket rp;
  rp.payload = payload;
  rp.marker = false;
  rp.sequence = sequence++;
  rp.timestamp = ts;   
  rp.ssrc = l_ssrc;
  rp.compile((unsigned char*)buffer,size);

  rp.setAddr(&r_saddr);
  if(rp.send(l_sd) < 0){
    ERROR("while sending RTP packet.\n");
    return -1;
  }
 
  return size;
}