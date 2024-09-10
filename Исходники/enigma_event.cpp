void eEventDisplay::init_eEventDisplay(const ePtrList<EITEvent>* e)
{
	eventlist=0;
	events=0;

	scrollbar = new eProgress(this);
	scrollbar->setName("scrollbar");
	scrollbar->setStart(0);
	scrollbar->setPerc(100);

	descr = new eWidget(this);
	descr->setName("epg_description");

	eventTime = new eLabel(this);
	eventTime->setName("time");

	eventDate = new eLabel(this);
	eventDate->setName("date");

	channel = new eLabel(this);
	channel->setName("channel");

	timer_icon = new eLabel(this);
	timer_icon->setName("timer_icon");

	eSkin *skin=eSkin::getActive();
	if (skin->build(this, "eventview"))
		eFatal("skin load of \"eventview\" failed");

	long_description=new eLabel(descr);
	long_description->setFlags(RS_WRAP);

	// try to recalc long description label... ( no broken text lines.. )
	float lineheight=fontRenderClass::getInstance()->getLineHeight( long_description->getFont() );
	int lines = (int)(descr->getSize().height() / lineheight);
	pageHeight = (int)(lines * lineheight);
	descr->resize( eSize( descr->getSize().width(), pageHeight+(int)(lineheight/6)));
	long_description->resize(eSize(descr->getSize().width(), pageHeight*16));

#ifndef DISABLE_FILE
	addActionToHelpList( &i_epgSelectorActions->addDVRTimerEvent );
#endif
#ifndef DISABLE_NETWORK
	addActionToHelpList( &i_epgSelectorActions->addNGRABTimerEvent );
#endif
	addActionToHelpList( &i_epgSelectorActions->addSwitchTimerEvent );
	addActionToHelpList( &i_epgSelectorActions->removeTimerEvent );
	addActionToHelpList( &i_enigmaEventViewActions->close );

	if (e)
		setList(*e);
	else if (evt)
		setEvent(evt);
	addActionMap( &i_enigmaEventViewActions->map );
	addActionMap( &i_epgSelectorActions->map );
	
	setHelpID(11);
}