CString Speller::GetFract(double d,int prec){
	
	if(!prec)return "";
	d-=floor(d);
	int i,j;
	LPTSTR ts;
	if(prec<0){
		ts=fcvt(d,20,&i,&j);
		if('0'==*ts)return "";
		for(LPTSTR tail=ts+19;ts<tail;tail--){
			if('0' == *tail)*tail='\0';	//убираем конечные нули
			else break; //до 1-го ненулевого символа.
		}
		CString rez('0',i);
		rez+=ts;
		return rez;
	}
	
	d+=1;
	ts=fcvt(d,prec,&i,&j);
	CString rez(ts+1);
	return rez;
	
}