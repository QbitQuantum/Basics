MOboolean moNetOSCOut::Init()
{
    int dev;
    MOuint i, n, n_dev, n_hosts;
    moText conf, dev_name;

    // Loading config file.
    if (moMoldeoObject::Init()) {
      moMoldeoObject::CreateConnectors();
    } else return false;


    moDefineParamIndex( NETOSCOUT_HOSTS, moText("hosts") );
    moDefineParamIndex( NETOSCOUT_PORT, moText("port") );
    moDefineParamIndex( NETOSCOUT_DEVICES, moText("devices") );
    moDefineParamIndex( NETOSCOUT_LATENCY, moText("latency") );
    moDefineParamIndex( NETOSCOUT_MAXEVENTS, moText("max_events") );
    moDefineParamIndex( NETOSCOUT_SENDEVENTS, moText("send_events") );
    moDefineParamIndex( NETOSCOUT_DELETEEVENTS, moText("delete_events") );
    moDefineParamIndex( NETOSCOUT_SENDMOLDEOAPI, moText("send_moldeo_api") );
    moDefineParamIndex( NETOSCOUT_DEBUG, moText("debug") );


    // Reading list of devices which will be used as source of events to send over the network.
    /*
    for(dev = MO_IODEVICE_KEYBOARD; dev <= MO_IODEVICE_TABLET; dev++) recog_devices[dev] = false;
    n = m_Config.GetParamIndex("devices");
    n_dev = m_Config.GetValuesCount(n);
    for(i = 0; i < n_dev; i++)
    {
		dev_name = m_Config.GetParam(n).GetValue(i).GetSubValue(0).Text();

        dev = -1;
        if(!stricmp(dev_name, "keyboard")) dev = MO_IODEVICE_KEYBOARD;
        if(!stricmp(dev_name, "mouse")) dev = MO_IODEVICE_MOUSE;
        if(!stricmp(dev_name, "midi")) dev = MO_IODEVICE_MIDI;
        if(!stricmp(dev_name, "mixer")) dev = MO_IODEVICE_MIXER;
        if(!stricmp(dev_name, "joystick")) dev = MO_IODEVICE_JOYSTICK;
		if(!stricmp(dev_name, "tablet")) dev = MO_IODEVICE_TABLET;
		if(!stricmp(dev_name, "tracker")) dev = MO_IODEVICE_TRACKER;

        if(-1 < dev) recog_devices[dev] = true;
    }
    */

    // Reading hosts names and ports.
    n = m_Config.GetParamIndex("hosts");
	n_hosts = m_Config.GetValuesCount(n);

	host_name.Init(n_hosts, moText(""));

    host_port.Init(n_hosts, 0);

    transmitSockets.Init(n_hosts,NULL);

    for(i = 0; i < n_hosts; i++)
    {
		host_name.Set(i, m_Config.GetParam(n).GetValue(i).GetSubValue(0).Text());
		host_port.Set(i, m_Config.GetParam(n).GetValue(i).GetSubValue(1).Int());
	}

    i = 0;

    UpdateParameters();

	for(i = 0; i < n_hosts; i++)
	{
#ifdef OSCPACK
	    unsigned long ii = GetHostByName(host_name[i]);
        char buffer[100];
        snprintf(buffer, 100, "%lu", ii); // Memory-safe version of sprintf.
        moText str = buffer;
	    //MODebug2->Message( moText("moNetOscOut:: host: ") + moText(host_name[i]) + moText(" ip int:") + (moText)str );
	    IpEndpointName ipendpointname( ii, host_port[i] ) ;
		transmitSockets[i] = new UdpTransmitSocket( ipendpointname );
#else
    //transmitSockets[i] = new lo::Address( host_name[i], IntToStr(host_port[i]) );
    transmitSockets[i] = lo_address_new( host_name[i], IntToStr(host_port[i]) );
#endif

		if (transmitSockets[i]) {
        MODebug2->Message(moText("NetOSCOut UdptransmitSocket Created at")+host_name[i]+":"+ IntToStr(host_port[i]) );
    }


	    //eventPacket[i] = new moEventPacket(sendInterval, maxEventNum);
	}

    //OUTPUT_BUFFER_SIZE = 1024; // 10 = maximum length of a 32 bit int in decimal rep.
    OUTPUT_BUFFER_SIZE = 60000;
    packetBuffer = new char[OUTPUT_BUFFER_SIZE];
    #ifdef OSCPACK
    packetStream = new osc::OutboundPacketStream( packetBuffer, OUTPUT_BUFFER_SIZE );
    #endif
	return true;
}