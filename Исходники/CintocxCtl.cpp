void CCintocxCtrl::OnDestroy() 
{
	COleControl::OnDestroy();

	// schedule destroy event
	EventQue.Push(NULL,this,TERMINATEEVENT);
#ifndef WIN32EVENT
	CintEvent.PulseEvent();
#else
	PulseEvent(CintEvent);
#endif
}