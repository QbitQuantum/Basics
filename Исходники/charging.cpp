// ===========================================================
// chargestring like "UNIT CHARGESTRING", returns secs per unit and charging sum
	int current_period(char *chargestring,float *charge)
// ===========================================================
{
CString tmp;
char curtime[30];
char from[10],to[10];
int	 fh,fm,th,tm,sec,count;

	_strtime(curtime);
	curtime[5]=0; // strip seconds

	count = count_tokens(chargestring);
	if (count<2)	return 0;

	get_token(chargestring,0,tmp,' ');
	sscanf(tmp,"%f",charge);	// charge unit

	for (int t=1;t<count;t++)
	{
		get_token(chargestring,t,tmp,' ');
		sscanf(tmp,"%d:%d-%d:%d=%d",&fh,&fm,&th,&tm,&sec);
		sprintf(from,"%02d:%02d",fh,fm);
		sprintf(to  ,"%02d:%02d",th,tm);

		if (strcmp(curtime,from)>=0 && strcmp(curtime,to)<0)
			return sec;
	}
	return 0;
}