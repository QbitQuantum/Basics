void interrupt far com1_isr(void)
  {
  // performs rs232 functions on com1
  unsigned intr;
  unsigned i;
  //unsigned lsb;
  //unsigned msb;
    
  _enable();
    
  // disable com1 uart interrupts      
  _outp(COM1_MCR, _inp(COM1_MCR) & 0xf7);
  
  start_com1_isr:
  
  // check contents of COM1_IIR  
  intr = _inp(COM1_IIR);
  intr = intr & 0x0f; // mask off b7 to b4
  
  if((intr & 0x01) == 0) // if a valid com1 interrupt is pending
    {   
    // shift IIR value right one bit and test to see which routine is required
    intr = intr >> 1;
  
    // do rs232 input interrupt routine
    if(intr == 0)
      {
      // read the rs232 status register
      unsigned msr_char = _inp(COM1_MSR);
      goto start_com1_isr;
      }
     
    // do tx buffer empty interrupt routine
    if(intr == 1)
      {
      // either write to tx FIFO or read int id register again
      
      // the idea here is to continue a tx once it has started,
      // not to start one in the first place
      
      // the tx is started by the main() program writing the first
      // char to the tx buffer, which will send the char out
      
      // once the tx fifo has drained, the tbe bit will be
      // set in the iir, indicating that the tx buffer is ready for more
      
      if(com1_tx==0)  // no message to tx
        {
        _inp(COM1_IIR);
        goto start_com1_isr;
        }
      if(com1_tx==1)  // tx remaining message
        {
        for(i=0; i<16;i++) // load 16 characters into the tx fifo
          {
          if(com1_tx==0) break;
          else  // only if more message needs to be sent
            {
            _outp(COM1_TX, tx1_message[tx1_index]); // write the next character
            tx1_index++;
            tx1_counter++;
            if(tx1_index >= tx1_len)  // entire message has been sent
              {
              tx1_index = 0;
              com1_tx = 0;
              tx1_len = 0;
              goto start_com1_isr;  
              }
            }
          }
        }
      goto start_com1_isr;    
      }
      
    // rx data received interrupt routine (>= 14 bytes in receive buffer)
    if(intr == 2)
      {
      // read rx register
            
      // read 12 bytes from the rx register (still at least 2 bytes left)
      for(i = 0; i < 12; i++)
        {
        rx1_message[rx1_index] = _inp(COM1_RX);
        rx1_index++;
        if(rx1_index >= sizeof(rx1_message))
          rx1_index = 0;
        }
        
      goto start_com1_isr;
      }
    
    // else do serialization error/break routine  
    if(intr == 3)
      {
      // read serialization/line status register
      unsigned lsr_char = _inp(COM1_LSR);
      goto start_com1_isr;
      }
    
    // do rx character timeout routine: message end
    if(intr == 6)
      {
      // drain rx fifo
      while((_inp(COM1_LSR) & 0x01) == 1)
        {
        rx1_message[rx1_index] = _inp(COM1_RX);
        rx1_index++;
        if(rx1_index >= sizeof(rx1_message)) rx1_index = 0;
        }
      
      //if(rx1_index >= 88) // complete frame received
      if(rx1_index >= 213) // complete frame received  // for PD0 format db & jtm 11/16/2007
        {
        // timestamp the adcp message
        _disable();
        time_stamp(&adcp_time);
        _enable();

        //memcpy(adcp_buffer, rx1_message, 88);
        //_fmemcpy(adcp_buffer, rx1_message, sizeof(adcp_buffer));//for PD0 format db & jtm 11/16/2007
        _fmemcpy(adcp_buffer, rx1_message, 213);//for PD0 format db & jtm 11/16/2007
        //rx1_index = 0;
        adcp_new_data = 1;
        adcp_data_frame = frame;
        }
      rx1_index = 0;
      goto start_com1_isr;      
      } // end rx character timeout routine
        
    goto start_com1_isr;
    }  // end if((intr & 0x01) == 0)