void PASCAL TimeProc(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	sprintf(str, "%s", "res//");
	
	if (c > 5472)
	{
		timeKillEvent(wTimerID);
	}
	if (c / 10 == 0)
		sprintf(buff, "B000%d.BMP", c);
	else if (c / 100 == 0)
		sprintf(buff, "B00%d.BMP", c);
	else if (c / 1000 == 0)
		sprintf(buff, "B0%d.BMP", c);
	else
	{
		sprintf(buff, "B%d.BMP", c);
	}
	str1 = str;
	str1 += buff;
	temp = c%25;
	if (temp == 0)
		count++;
	if (count == 10)count = 0;
	DrawImg(str1,count);
	c++;
}