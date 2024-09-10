void copy_octet_base::setupIOMappings()
{
  int ninput_streams = 0;
  int noutput_streams = 0;

  if ( !validGRBlock() ) return;
  
  ninput_streams  = gr_sptr->get_max_input_streams();
  gr_io_signature_sptr g_isig = gr_sptr->input_signature();  
  noutput_streams = gr_sptr->get_max_output_streams();
  gr_io_signature_sptr g_osig = gr_sptr->output_signature();

  //
  // RESOLVE: Still need to resolve the issue with the input port/stream to output port.  We also need to resolve issue
  // with "ganging" ports together as an input to a GNU RADIO Block. transform cplx to real ... r/i -> float
  //
  
  LOG_DEBUG( copy_octet_base, "GNUHAWK IO MAPPINGS IN/OUT " << ninput_streams << "/" << noutput_streams );
  std::string sid("");

  //
  // Someone reset the GR Block so we need to clean up old mappings if they exists
  // we need to reset the io signatures and check the vlens
  //
 
 
   if ( _istreams.size() > 0 || _ostreams.size() > 0 ) {


 
    LOG_DEBUG(  copy_octet_base, "RESET INPUT SIGNATURE SIZE:" << _istreams.size() );
    IStreamList::iterator istream;
    for ( int idx=0 ; istream != _istreams.end(); idx++, istream++ ) {
        // re-add existing stream definitons
      LOG_DEBUG(  copy_octet_base, "ADD READ INDEX TO GNU RADIO BLOCK");
      if ( ninput_streams == -1 ) gr_sptr->add_read_index();

      // setup io signature 
      istream->associate( gr_sptr );
    }
 
    LOG_DEBUG(  copy_octet_base, "RESET OUTPUT SIGNATURE SIZE:" << _ostreams.size() );
    OStreamList::iterator ostream;
    for ( int idx=0 ; ostream != _ostreams.end(); idx++, ostream++ ) {
        // need to evaluated new settings...???
        ostream->associate( gr_sptr );
    }

    return;
  }


     
  // setup mapping of RH Port to GNU RADIO BLOCK input streams as a 1-1 mapping (basically we ignore streamID when pulling data from port)
  // for case ninput == -1 and 1 port we map out streamID to each GNU Radio Block input stream this is done in the notifySRI callback method
  if ( ninput_streams != -1 || ( ninput_streams == -1 && inPorts.size() > 1 ) ) {
  
    int nstreams = inPorts.size();
    if ( ninput_streams != -1 ) nstreams = std::min( nstreams, ninput_streams);
    
    RH_ProvidesPortMap::iterator p_in = inPorts.begin();
    for ( int i=0; i < nstreams && p_in != inPorts.end(); i++, p_in++ ) {
      // need to add read index to GNU Radio Block for processing, 
      if ( ninput_streams == -1 ) gr_sptr->add_read_index();
      _istreams.push_back( gr_istream< BULKIO_dataOctet_In_i > ( dynamic_cast< BULKIO_dataOctet_In_i * >(p_in->second), sid, gr_sptr, i));
    }
  }
  else {   // ninput_stream is variable == -1 and  component ports == 1
    //
    // need to worry about sync between when service function starts and pushSRI happens, 
    //
    for ( RH_ProvidesPortMap::iterator p_in = inPorts.begin(); p_in != inPorts.end(); p_in++ ) {

      BULKIO_dataOctet_In_i *port = dynamic_cast< BULKIO_dataOctet_In_i * >(p_in->second);
      BULKIO::StreamSRISequence_var sris = port->activeSRIs();
      for ( uint32_t i=0 ; i < sris->length(); i++ ) {
         BULKIO::StreamSRI sri = sris[i];
         int mode = sri.mode;
	 sid = sri.streamID;
	 _istreams.push_back( gr_istream< BULKIO_dataOctet_In_i > ( port, sid, gr_sptr, i, mode ));
      }
	  
    }
  }
 

  if ( noutput_streams != -1  || (noutput_streams == -1 && outPorts.size() > 1  ) ) {
    int32_t nstreams = outPorts.size();
    if ( noutput_streams != -1 ) {
      if ( nstreams != noutput_streams ) 
         LOG_WARN( copy_octet_base, "Number of OUTPUT PORTS is different than number of GNU RADIO STREAMS  PORTS/STREAMS " <<  nstreams << "/" << noutput_streams );
      nstreams = std::min( nstreams, noutput_streams);
    }

    // add number of output streams based min ( gr block output streams, or output ports)
    LOG_TRACE( copy_octet_base, "setupIOMappings OutputPorts: " << nstreams );
    RH_UsesPortMap::iterator p_out = outPorts.begin();
    for ( int i=0; i < nstreams && p_out != outPorts.end(); i++, p_out++ ) {
       _ostreams.push_back( gr_ostream < BULKIO_dataOctet_Out_i >( dynamic_cast< BULKIO_dataOctet_Out_i *>(p_out->second), sid, gr_sptr, i ));
    }
  } 
  else if ( (noutput_streams == -1 && outPorts.size() == 1) && ( ninput_streams == 0 ) ) {
    // RESOLVE: should generate maps based on port connections when output streams is variable and no input stream
    RH_UsesPortMap::iterator p_out = outPorts.begin();
    uint32_t idx =0;
    std::string sid("");
    uint32_t nstreams = getNOutputStreams();
    for( ; idx < nstreams; idx++ ) {
       _ostreams.push_back( gr_ostream < BULKIO_dataOctet_Out_i >( dynamic_cast< BULKIO_dataOctet_Out_i *>(p_out->second), sid, gr_sptr, idx ));
    }
  }

  // for each output stream definition, call createOutputSRI to create initial value for the stream 
  OStreamList::iterator ostream = _ostreams.begin();
  for ( int i=0;  ostream != _ostreams.end(); i++, ostream++ ) {
    BULKIO::StreamSRI sri = createOutputSRI( i );
    ostream->setSRI(sri, i );
    ostream->pushSRI();
  }
  
     
}