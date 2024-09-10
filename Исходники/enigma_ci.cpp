void enigmaCI::init_enigmaCI()
{
	CONNECT(ci_messages.recv_msg, enigmaCI::updateCIinfo );
	int fd=eSkin::getActive()->queryValue("fontsize", 20);

	DVBCI=eDVB::getInstance()->DVBCI;

	if( eSystemInfo::getInstance()->hasCI() > 1 )
	{
		setText(_("Common Interface Modules"));
		move(ePoint(160, 90));
		cresize(eSize(350, 330));
		DVBCI2=eDVB::getInstance()->DVBCI2;
		CONNECT(ci2_messages.recv_msg, enigmaCI::updateCI2info );
	}
	else
	{
		setText(_("Common Interface Module"));
		move(ePoint(160, 120));
		cresize(eSize(350, 250));
	}

	reset=new eButton(this);
	reset->setText(_("Reset"));
	reset->move(ePoint(10, 13));
	reset->resize(eSize(330, fd+10));
	reset->setHelpText(_("reset the Common Interface module"));
	reset->loadDeco();

	CONNECT(reset->selected, enigmaCI::resetPressed);

	init=new eButton(this);
	init->setText(_("Init"));
	init->move(ePoint(10, 53));
	init->resize(eSize(330, fd+10));
	init->setHelpText(_("send the ca-pmt to CI"));
	init->loadDeco();

	CONNECT(init->selected, enigmaCI::initPressed);		

	app=new eButton(this);
	app->setText(_("waiting for module"));
	app->move(ePoint(10, 93));
	app->resize(eSize(330, fd+10));
	app->setHelpText(_("enter Common Interface menu (mmi)"));
	app->loadDeco();

	CONNECT(app->selected, enigmaCI::appPressed);		

	if( eSystemInfo::getInstance()->hasCI() > 1 )
	{
		reset2=new eButton(this);
		reset2->setText(_("Reset"));
		reset2->move(ePoint(10, 143));
		reset2->resize(eSize(330, fd+10));
		reset2->setHelpText(_("reset the Common Interface module"));
		reset2->loadDeco();

		CONNECT(reset2->selected, enigmaCI::reset2Pressed);		

		init2=new eButton(this);
		init2->setText(_("Init"));
		init2->move(ePoint(10, 183));
		init2->resize(eSize(330, fd+10));
		init2->setHelpText(_("send the ca-pmt to CI"));
		init2->loadDeco();

		CONNECT(init2->selected, enigmaCI::init2Pressed);		

		app2=new eButton(this);
		app2->setText(_("waiting for module"));
		app2->move(ePoint(10, 223));
		app2->resize(eSize(330, fd+10));
		app2->setHelpText(_("enter Common Interface menu (mmi)"));
		app2->loadDeco();

		CONNECT(app2->selected, enigmaCI::app2Pressed);		
	}
	else
	{
		int handleTwo=0;
		eConfig::getInstance()->getKey("/ezap/ci/handleTwoServices", handleTwo);
		twoServices = new eCheckbox(this);
		twoServices->move(ePoint(10,128));
		twoServices->resize(eSize(330,(fd+10)*2));
		twoServices->setCheck(handleTwo);
		twoServices->setFlags(RS_WRAP|eLabel::flagVCenter);
		twoServices->setText(_("can handle two services"));
		twoServices->setHelpText(_("can your CI descramble two services at the same time?"));
		CONNECT(twoServices->checked, enigmaCI::handleTwoServicesChecked);
	}

	status = new eStatusBar(this);	
	status->move( ePoint(0, clientrect.height()-50) );
	status->resize( eSize( clientrect.width(), 50) );
	status->loadDeco();

	CONNECT(DVBCI->ci_progress, enigmaCI::gotCIinfoText);
	DVBCI->messages.send(eDVBCI::eDVBCIMessage(eDVBCI::eDVBCIMessage::getAppName));

	if( eSystemInfo::getInstance()->hasCI() > 1 )
	{
		CONNECT(DVBCI2->ci_progress, enigmaCI::gotCI2infoText);
		DVBCI2->messages.send(eDVBCI::eDVBCIMessage(eDVBCI::eDVBCIMessage::getAppName));
	}
}