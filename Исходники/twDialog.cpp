void twDialog::showWithCompletionHandler(twInvocation *handler){
	twReleaseCapture();
	m_handler=handler;
	m_mode=twDM_handler;
	
	if(m_needsDimming){
		m_dimmer=twDimmer::openDimmer(m_dimmerStyle, new twNoArgumentMemberFunctionInvocation<twDialog>(this, &twDialog::backgroundTouched));
		m_oldDesktop=getParent();
		setParent(m_dimmer);
		m_dimmer->setHidingWindow(this);
	}
	
	m_res=twDR_invalid;
	
	if(twWnd *w=twGetDesktop()){
		twRect r1=w->getRect();
		twRect r2=getRect();
		setRect(twRect( (r1.w-r2.w)/2, (r1.h-r2.h)/2, r2.w, r2.h ));
	}
	
	show();
	focus();
}