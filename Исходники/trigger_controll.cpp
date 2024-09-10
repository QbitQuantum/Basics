    int trigger_controll::load_from_file(char *fname)
    {
        Config *cfg;
        cfg = new Config();
        // Read the file. If there is an error, market and contunue on.
        try
        {
          cfg->readFile(fname);
        }
        catch(const FileIOException &fioex)
        {
            printf("I/O error while reading config file.\n");
            return 1;
        }
        catch(const ParseException &pex)
        {
            std::string str;
            printf("Error parsing config file: " );//+ pex.getLine() + " - " + pex.getError();

    //      return;
        }
        Setting &root = cfg->getRoot();
        if( root.exists("ip_adr")) //make a default config file if settings donot exists
        {
            std::string str;
            root.lookupValue("ip_adr",str);
           ip_adr = str;
        }else{
            ip_adr = "192.168.1.120";
        }
        if( root.exists("delays")) //make a default config file if settings donot exists
        {
            int i;
            Setting &delays = root["delays"];

            if(delays.exists("scintillator"))
            {
                delays.lookupValue("scintillator",i);
                set_scintillator_delay(i);
            }
            if(delays.exists("plane1"))
            {
                delays.lookupValue("plane1",i);
                set_plane_1_delay(i);
            }
            if(delays.exists("plane2"))
            {
                delays.lookupValue("plane2",i);
                set_plane_2_delay(i);
            }
            if(delays.exists("plane3"))
            {
                delays.lookupValue("plane3",i);
                set_plane_3_delay(i);
            }
            if(delays.exists("plane4"))
            {
                delays.lookupValue("plane4",i);
                set_plane_4_delay(i);
            }
            if(delays.exists("plane5"))
            {
                delays.lookupValue("plane5",i);
                set_plane_5_delay(i);
            }
            if(delays.exists("plane6"))
            {
                delays.lookupValue("plane6",i);
                set_plane_6_delay(i);
            }
            if(delays.exists("plane7"))
            {
                delays.lookupValue("plane7",i);
                set_plane_7_delay(i);
            }
            if(delays.exists("plane8"))
            {
                delays.lookupValue("plane8",i);
                set_plane_8_delay(i);
            }
            if(delays.exists("pad"))
            {
                delays.lookupValue("pad",i);
                set_pad_delay(i);
            }
            if(set_delays())
            {
                printf("Error setting delays: %s\n",this->error_str);
                return 1;
            }
        }
        float f;
        int i;
        if(root.exists("pulser_width"))
        {
            root.lookupValue("pulser_width",i);
        }
        if( root.exists("pulser_freq"))
        {
            root.lookupValue("pulser_freq", f);
            if(set_Pulser_width(f,i)){ //error
                printf("error setting pulser dutty");
                return 1;
            }
        }
        if( root.exists("prescaler"))
        {
            root.lookupValue("prescaler", i);
            if(set_prescaler(i))
                return 1;
        }
        if( root.exists("prescaler_delay")){
            root.lookupValue("prescaler_delay", i);
            if(set_prescaler_delay(i))
                return 1;
        }
        /*
        if(! root.exists("readout_period")) //make a default config file if settings donot exists
        {
             root.add("readout_period",Setting::TypeInt) = 1000;
        }
        */
        if(! root.exists("use_planes")) //make a default config file if settings donot exists
        {
            bool use;
            int en=0;
            Setting &use_planes = root["use_planes"];
            if(use_planes.exists("scintillator")){
                use_planes.lookupValue("scintillator", use);
                en =(use);
            }
            if(use_planes.exists("plane1")){
                use_planes.lookupValue("plane1", en);
                use += en<<1;
            }
            if(use_planes.exists("plane2")){
                use_planes.lookupValue("plane2", en);
                use += en<<2;
            }
            if(use_planes.exists("plane3")){
               use_planes.lookupValue("plane3", en);
               use += en<<3;
            }
            if(use_planes.exists("plane4")){
                use_planes.lookupValue("plane4", en);
                use += en<<4;
            }
            if(use_planes.exists("plane5")){
                use_planes.lookupValue("plane5", en);
                use += en<<5;
            }
            if(use_planes.exists("plane6")){
                use_planes.lookupValue("plane6", en);
                use += en<<6;
            }
            if(use_planes.exists("plane7")){
                use_planes.lookupValue("plane7", en);
                use += en<<7;
            }
            if(use_planes.exists("plane8")){
                use_planes.lookupValue("plane8", en);
                use += en<<8;
            }
            if(use_planes.exists("pad")){
                use_planes.lookupValue("pad", en);
                use += en<<9;
            }

            if(set_coincidence_enable(en))
                return 1;
        }
        if( root.exists("coincidence_edge_width"))
        {
            root.lookupValue("coincidence_edge_width", i) ;
            if(set_coincidence_edge_width(i))
                return 1;
        }
        if(root.exists("coincidence_pulse_width"))
        {
            root.lookupValue("coincidence_pulse_width", i) ;
            if(set_coincidence_pulse_width(i))
                return 1;
        }
        if( root.exists("handshake_mask"))
        {
            root.lookupValue("handshake_mask", i) ;
            if(set_handshake_mask(i))
                return 1;
        }
        if(root.exists("handshake_delay"))
        {
            root.lookupValue("handshake_delay", i) ;
            if(set_handshake_delay(i))
                return 1;
        }
        int delay = 0;
        if(root.exists("trig_1_delay"))
        {
            root.lookupValue("trig_1_delay", delay) ;
        }
        if(root.exists("trig_2_delay"))
        {
            root.lookupValue("trig_2_delay", i) ;
            delay = (delay & 0x0FF) | i <<12;
            if(set_trigger_12_delay(delay))
                return 1;
        }
        if(root.exists("trig_3_delay"))
        {
            root.lookupValue("trig_3_delay", i) ;
            if(set_trigger_3_delay(i))
                return 1;
        }
        this->set_time();//send the curent time stamp
        return 0;
    }