void eZapNetworkSetup::init_eZapNetworkSetup()
{
	__u32 sip=ntohl(0x0a000061),
				snetmask=ntohl(0xFF000000),
				sdns=ntohl(0x7f000001),
				sgateway=ntohl(0x7f000001);

	int de[4];
	int sdosetup=0;
	int connectionType=0;
	int webifport=80;
	int useDHCP=0;

#ifdef USE_IFUPDOWN
	bool automatic_start;
	std::string Ip, Netmask, Broadcast, Gateway;
	useDHCP=!getInetAttributes("eth0", automatic_start, Ip, Netmask, Broadcast, Gateway);
	sdosetup=automatic_start;
#else
	eConfig::getInstance()->getKey("/elitedvb/network/usedhcp", useDHCP);
	eConfig::getInstance()->getKey("/elitedvb/network/dosetup", sdosetup);
#endif
	if (useDHCP)
	{
		getIP("eth0", sip, snetmask);
		getDefaultGateway(sgateway);
		getNameserver(sdns);
	}
	else
	{
#ifdef USE_IFUPDOWN
		int tmp[4];
		if ( sscanf(Ip.c_str(), "%d.%d.%d.%d", tmp, tmp+1, tmp+2, tmp+3) == 4 )
			sip = tmp[0]<<24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3];
		else
			eDebug("couldn't parse ip(%s)", Ip.length()?Ip.c_str():"");

		if ( sscanf(Netmask.c_str(), "%d.%d.%d.%d", tmp, tmp+1, tmp+2, tmp+3) == 4 )
			snetmask = tmp[0]<<24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3];
		else
			eDebug("couldn't parse netmask(%s)", Netmask.length()?Netmask.c_str():"");

		if ( sscanf(Gateway.c_str(), "%d.%d.%d.%d", tmp, tmp+1, tmp+2, tmp+3) == 4 )
			sgateway = tmp[0]<<24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3];
		else
			eDebug("couldn't parse gateway(%s)", Gateway.length()?Gateway.c_str():"");

		getNameserver(sdns);  // read always from /etc/resolv.conf
#else
		eConfig::getInstance()->getKey("/elitedvb/network/ip", sip);
		eConfig::getInstance()->getKey("/elitedvb/network/netmask", snetmask);
		eConfig::getInstance()->getKey("/elitedvb/network/gateway", sgateway);
		eConfig::getInstance()->getKey("/elitedvb/network/dns", sdns);
#endif
	}
	eConfig::getInstance()->getKey("/elitedvb/network/connectionType", connectionType);
	eConfig::getInstance()->getKey("/elitedvb/network/webifport", webifport);

	eNumber::unpack(sip, de);
	ip=CreateSkinnedNumberWithLabel("ip",0, 4, 0, 255, 3, de, 0, "lip", !useDHCP);
	ip->setFlags(eNumber::flagDrawPoints);
	CONNECT(ip->selected, eZapNetworkSetup::fieldSelected);

	dhcp = CreateSkinnedCheckbox("dhcp", useDHCP);
	CONNECT(dhcp->checked, eZapNetworkSetup::dhcpStateChanged);

	eNumber::unpack(snetmask, de);
	netmask=CreateSkinnedNumberWithLabel("netmask",0, 4, 0, 255, 3, de, 0, "lnetmask", !useDHCP);
	netmask->setFlags(eNumber::flagDrawPoints);
	CONNECT(netmask->selected, eZapNetworkSetup::fieldSelected);

	eListBoxEntryText *sel=0;
	combo_type=CreateSkinnedComboBoxWithLabel("combo_type", 3, "lcombo_type");
#ifdef ENABLE_PPPOE
	if ( !connectionType )
#endif
	{
		sel = new eListBoxEntryText( *combo_type, _("LAN"), (void*)0, 0, _("communicate to Local Area Network"));
#ifdef ENABLE_PPPOE
		new eListBoxEntryText( *combo_type, _("WAN(PPPoE)"), (void*)1, 0, _("communicate to the Internet via DSL"));
#endif
	}
#ifdef ENABLE_PPPOE
	else
	{
		new eListBoxEntryText( *combo_type, _("LAN"), (void*)0, 0, _("communicate to Local Area Network"));
		sel = new eListBoxEntryText( *combo_type, _("WAN(PPPoE)"), (void*)1, 0, _("communicate to the Internet via DSL"));
	}
	CONNECT(combo_type->selchanged, eZapNetworkSetup::typeChanged);
	tdsl = new eButton(this);
	tdsl->move(ePoint(340,90));
	tdsl->resize(eSize(100, fd+10));
	tdsl->setText("T-DSL");
	tdsl->loadDeco();
	tdsl->hide();
	tdsl->setHelpText(_("T-Online User press ok here"));
	CONNECT( tdsl->selected, eZapNetworkSetup::tdslPressed );
#endif

	eNumber::unpack(sdns, de);
	dns=CreateSkinnedNumberWithLabel("dns",0, 4, 0, 255, 3, de, 0, "lNameserver", !useDHCP);
	dns->setFlags(eNumber::flagDrawPoints);
	CONNECT(dns->selected, eZapNetworkSetup::fieldSelected);

#ifdef ENABLE_PPPOE
	lLogin=new eLabel(this);
	lLogin->setText(_("Login:"******"/elitedvb/network/login", strLogin);
	login=new eTextInputField(this,lLogin);
	login->move(ePoint(160, 130));
	login->resize(eSize(280, fd+10));
	login->setMaxChars(100);
	login->loadDeco();
	login->setHelpText(_("press ok to edit your provider login name"));
	if ( strLogin )
		login->setText(strLogin);
	login->hide();
	CONNECT(login->selected, eZapNetworkSetup::loginSelected );
#endif

	eNumber::unpack(sgateway, de);
	gateway=CreateSkinnedNumberWithLabel("gateway",0, 4, 0, 255, 3, de, 0, "lgateway", !useDHCP);
	gateway->setFlags(eNumber::flagDrawPoints);
	CONNECT(gateway->selected, eZapNetworkSetup::fieldSelected);

#ifdef ENABLE_PPPOE
	lPassword=new eLabel(this);
	lPassword->setText(_("Password:"******"press ok to edit your provider password"));
	password->hide();
	CONNECT(password->selected, eZapNetworkSetup::passwordSelected);
#endif

	dosetup=CreateSkinnedCheckbox("dosetup", sdosetup);

	port=CreateSkinnedNumberWithLabel("port",webifport, 1, 0, 65536, 5, 0, 0, "lport");
	port->setFlags(eNumber::flagDrawPoints);
	CONNECT(port->selected, eZapNetworkSetup::fieldSelected);

#ifdef ENABLE_PPPOE
	int flags = getRejectFlags();
	rejectWWW=new eCheckbox(this, flags&1, 1);
	rejectWWW->setText("WWW");
	rejectWWW->move(ePoint(20,255));
	rejectWWW->resize(eSize(90, fd+4));
	rejectWWW->setHelpText(eString().sprintf(_("reject incoming connections on port %d"), webifport));
	rejectWWW->hide();

	rejectTelnet=new eCheckbox(this, flags&2, 1);
	rejectTelnet->setText("Telnet");
	rejectTelnet->move(ePoint(130,255));
	rejectTelnet->resize(eSize(90, fd+4));
	rejectTelnet->setHelpText(eString().sprintf(_("reject incoming connections on port %d"), 23));
	rejectTelnet->hide();

	rejectSamba=new eCheckbox(this, flags&4, 1);
	rejectSamba->setText("Samba");
	rejectSamba->move(ePoint(240,255));
	rejectSamba->resize(eSize(100, fd+4));
	rejectSamba->setHelpText(_("reject incoming connections on ports 137,138,139"));
	rejectSamba->hide();

	rejectFTP=new eCheckbox(this, flags&8, 1);
	rejectFTP->setText("FTP");
	rejectFTP->move(ePoint(360,255));
	rejectFTP->resize(eSize(70, fd+4));
	rejectFTP->setHelpText(eString().sprintf(_("reject incoming connections on port %d"), 21));
	rejectFTP->hide();
#endif

	CONNECT(CreateSkinnedButton("ok")->selected, eZapNetworkSetup::okPressed);

#ifndef DISABLE_NFS
	nfs = CreateSkinnedButton("nfs");
	CONNECT(nfs->selected, eZapNetworkSetup::nfsPressed );
#else
	CreateSkinnedButton("nfs")->hide();
#endif

	BuildSkin("eZapNetworkSetup");
	setHelpID(82);

	combo_type->setCurrent(sel,true);

#ifdef ENABLE_PPPOE
	if ( readSecretString( secrets ) && secrets )
	{
		unsigned int pos = secrets.find("*");
		if ( pos != eString::npos )
		{
			login->setText( secrets.left(pos) );
			password->setText("******");
		}
	}
#endif
}