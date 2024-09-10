void randomizer_base::setupIOMappings( )
{
    int ninput_streams = 0;
    int noutput_streams = 0;
    std::vector<std::string>::iterator pname;
    std::string sid("");
    int inMode=RealMode;

    if ( !validGRBlock() ) return;
    ninput_streams  = gr_sptr->get_max_input_streams();
    gr_io_signature_sptr g_isig = gr_sptr->input_signature();

    noutput_streams = gr_sptr->get_max_output_streams();
    gr_io_signature_sptr g_osig = gr_sptr->output_signature();

    LOG_DEBUG( randomizer_base, "GNUHAWK IO MAPPINGS IN/OUT " << ninput_streams << "/" << noutput_streams );

    //
    // Someone reset the GR Block so we need to clean up old mappings if they exists
    // we need to reset the io signatures and check the vlens
    //
    if ( _istreams.size() > 0 || _ostreams.size() > 0 ) {

        LOG_DEBUG( randomizer_base, "RESET INPUT SIGNATURE SIZE:" << _istreams.size() );
        IStreamList::iterator istream;
        for ( int idx=0 ; istream != _istreams.end(); idx++, istream++ ) {
            // re-add existing stream definitons
            LOG_DEBUG(  randomizer_base, "ADD READ INDEX TO GNU RADIO BLOCK");
            if ( ninput_streams == -1 ) gr_sptr->add_read_index();

            // setup io signature
            istream->associate( gr_sptr );
        }

        LOG_DEBUG( randomizer_base, "RESET OUTPUT SIGNATURE SIZE:" << _ostreams.size() );
        OStreamList::iterator ostream;
        for ( int idx=0 ; ostream != _ostreams.end(); idx++, ostream++ ) {
            // need to evaluate new settings...???
            ostream->associate( gr_sptr );
        }

        return;
    }


   //
   // Setup mapping of RH port to GNU RADIO Block input streams
   // For version 1,  we are ignoring the GNU Radio input stream -1 case that allows multiple data 
   // streams over a single connection.  We are mapping a single RH Port to a single GNU Radio stream.
   // Stream Identifiers will  be pass along as they are received
   //
    LOG_TRACE( randomizer_base, "setupIOMappings INPUT PORTS: " << inPorts.size() );
    pname = inputPortOrder.begin();
    for( int i=0; pname != inputPortOrder.end(); pname++ ) {

        // grab ports based on their order in the scd.xml file
        RH_ProvidesPortMap::iterator p_in = inPorts.find(*pname);
        if ( p_in != inPorts.end() ) {
            bulkio::InOctetPort *port = dynamic_cast< bulkio::InOctetPort * >(p_in->second);
            int mode = inMode;
            sid = "";

            // need to add read index to GNU Radio Block for processing streams when max_input == -1
            if ( ninput_streams == -1 ) gr_sptr->add_read_index();

            // check if we received SRI during setup
            BULKIO::StreamSRISequence_var sris = port->activeSRIs();
            if (  sris->length() > 0 ) {
                BULKIO::StreamSRI sri = sris[sris->length()-1];
                mode = sri.mode;
            }
            std::vector<int> in;
            io_mapping.push_back( in );
            _istreams.push_back( gr_istream< bulkio::InOctetPort > ( port, gr_sptr, i, mode, sid ));
            LOG_DEBUG( randomizer_base, "ADDING INPUT MAP IDX:" << i << " SID:" << sid );
            // increment port counter
            i++;
        }
    } 

    //
    // Setup mapping of RH port to GNU RADIO Block input streams
    // For version 1,  we are ignoring the GNU Radio output stream -1 case that allows multiple data 
    // streams over a single connection.  We are mapping a single RH Port to a single GNU Radio stream.
    //
    LOG_TRACE( randomizer_base, "setupIOMappings OutputPorts: " << outPorts.size() );
    pname = outputPortOrder.begin();
    for( int i=0; pname != outputPortOrder.end(); pname++ ) {

        // grab ports based on their order in the scd.xml file
        RH_UsesPortMap::iterator p_out = outPorts.find(*pname);
        if ( p_out != outPorts.end() ) {
            bulkio::OutOctetPort *port = dynamic_cast< bulkio::OutOctetPort * >(p_out->second);
            int idx = -1;
            BULKIO::StreamSRI sri = createOutputSRI( i, idx );
            if (idx == -1) idx = i;
            if(idx < (int)io_mapping.size()) io_mapping[idx].push_back(i);
            int mode = sri.mode;
            sid = sri.streamID;
            _ostreams.push_back( gr_ostream< bulkio::OutOctetPort > ( port, gr_sptr, i, mode, sid ));
            LOG_DEBUG( randomizer_base, "ADDING OUTPUT MAP IDX:" << i << " SID:" << sid );
            _ostreams[i].setSRI(sri, i );
            // increment port counter
            i++;
        }
    }
}