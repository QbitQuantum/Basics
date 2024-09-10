void eSatfind::init_eSatfind()
{
    p_snr=new eProgress(this);
    p_snr->setName("snr");

    p_agc=new eProgress(this);
    p_agc->setName("agc");

    p_ber=new eProgress(this);
    p_ber->setName("ber");

    c_sync=new eCheckbox(this, 0, 0);
    c_sync->setName("sync");

    c_lock=new eCheckbox(this, 0, 0);
    c_lock->setName("lock");

    lsnr_num=new eLabel(this);
    lsnr_num->setName("snr_num");

    lsync_num=new eLabel(this);
    lsync_num->setName("agc_num");

    lber_num=new eLabel(this);
    lber_num->setName("ber_num");

    sat = new eComboBox(this, 3);
    sat->setName("sat");
    CONNECT(sat->selchanged, eSatfind::satChanged );

    transponder = new eComboBox(this, 5);
    transponder->setName("transponder");

    CONNECT(updateTimer.timeout, eSatfind::update);

    eLabel *l = new eLabel(this);
    l->setName("lSat");

    if (eSkin::getActive()->build(this, "eSatfind"))
        return;

    eDVBServiceController *sapi=eDVB::getInstance()->getServiceAPI();

    if (sapi && sapi->transponder)
        current = sapi->transponder;

    eListBoxEntryText *sel=0;

    if ( eSystemInfo::getInstance()->getFEType() == eSystemInfo::feTerrestrial )
    {
        setText(_("Signalfind"));
        l->setText(_("Region:"));
    }

    std::map<int,eSatellite*> sats;
    for ( std::list<eLNB>::iterator it( eTransponderList::getInstance()->getLNBs().begin() ); it != eTransponderList::getInstance()->getLNBs().end(); it++)
        for ( ePtrList<eSatellite>::iterator s ( it->getSatelliteList().begin() ); s != it->getSatelliteList().end(); s++)
            sats[s->getOrbitalPosition()]=s;

    for ( std::list<tpPacket>::const_iterator i(eTransponderList::getInstance()->getNetworks().begin()); i != eTransponderList::getInstance()->getNetworks().end(); ++i)
        if ( ( sats.find(i->orbital_position) != sats.end()) || (eSystemInfo::getInstance()->getFEType() != eSystemInfo::feSatellite) )
        {
            if ( eSystemInfo::getInstance()->getFEType() == eSystemInfo::feSatellite && current && i->orbital_position == current->satellite.orbital_position )
                sel = new eListBoxEntryText(*sat, i->name, (void*)&*i);
            else
                new eListBoxEntryText(*sat, i->name, (void*)&*i);
        }

    if ( sat->getCount() )
    {
        if ( sel )
            sat->setCurrent(sel,true);
        else
            sat->setCurrent(0,true);
    }

    CONNECT( eFrontend::getInstance()->s_RotorRunning, eSatfind::RotorRunning );
    CONNECT( eFrontend::getInstance()->tunedIn, eSatfind::tunedIn );

    CONNECT(transponder->selchanged, eSatfind::tpChanged);

    /* help text for satfinder screen */
    setHelpText(_("\tSatFind\n\n>>> [MENU] >>> [6] Setup\n>>> Service Searching >>> SatFind\n. . . . . . . . . .\n\n" \
                  "Here you can see the quality of the signal your receiver is getting from your dish/lnb(s).\n. . . . . . . . . .\n\n" \
                  "Usage:\n\nSNR\tSignal to Noise Ratio\n\nAGC\tAutomatic Gain Control\n\nBER\tBit Error Rate\n\n" \
                  "SATTELITE\tSelect satellite to monitor\n\nTRANSPONDER\tSelect transponder to monitor\n\n[OK]/[EXIT]\tClose window"));
}