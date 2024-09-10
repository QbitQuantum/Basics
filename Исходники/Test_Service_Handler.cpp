int Test_Service_Handler::send()
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> guard(mtx_);

  ACE_DEBUG ((LM_DEBUG, 
      ACE_TEXT("(%t) %s_Handler(%@)::send() fd=%d\n"),
      is_caller_ ? "Client" : "Server" ,
      this,
      this->handle()));

  //AL:
  if (!cancel_called_)
  {
     //AL: not thread safe
     //static std::string pkt = pkt_header;
     //pkt += pkt_payload;

     size_t len_header  = ACE_OS::strlen(pkt_header);
     size_t len_payload = ACE_OS::strlen(pkt_payload);

     ACE_Message_Block *mb = 0;

     ACE_NEW_RETURN(mb, ACE_Message_Block(len_header+len_payload), -1);

     mb->copy(pkt_header, len_header);
     mb->copy(pkt_payload, len_payload);
    
     int ret = writer_.write(*mb, mb->length());
     if (ret == 0)
     {
        write_count_++;
        return 0;
     }

     mb->release();

  }

  ACE_DEBUG ((LM_DEBUG,
      ACE_TEXT("(%t) %s_Handler(%@)::send failed\n"),
      is_caller_ ? "Client" : "Server" ,
      this));

  //AL: delete_if_reqd();
  this->cancel();

  return -1;
}