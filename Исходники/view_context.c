int set_scroll_pos(HWND hwnd,int ctrl,FILE *f)
{
	int result=FALSE;
	double p;
	__int64 size,offset;
	int pos;
	if(f==0)
		return result;
	offset=_ftelli64(f);
	_fseeki64(f,0,SEEK_END);
	size=_ftelli64(f);
	if(size==0){
		SendDlgItemMessage(hwnd,ctrl,SBM_SETPOS,0,TRUE);
		return result;
	}
	_fseeki64(f,offset,SEEK_SET);
	p=(double)offset/(double)size;
	p*=10000;
	pos=(int)floor(p);
	if(pos>10000)
		pos=10000;
	scroll_pos=pos;
	SendDlgItemMessage(hwnd,ctrl,SBM_SETPOS,pos,TRUE);
	result=TRUE;
	return result;
}