void InactivityPoller::checkUp()
{
	LASTINPUTINFO lp;
    lp.cbSize = sizeof(lp);
    GetLastInputInfo(&lp);
    int cur_t=(GetTickCount()-lp.dwTime);
	if (cur_t >= timeout_){
		if (isActive_){
			isActive_=false;
			Notify();
		}
	}
	else {
		if(!isActive_){
			isActive_=true;
			Notify();
		}
	}
}