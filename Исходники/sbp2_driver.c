void DeinitIEEE1394(void){
	TerminateThread(iLinkIntrCBThreadID);
	DeleteThread(iLinkIntrCBThreadID);
	DeleteEventFlag(sbp2_event_flag);
}