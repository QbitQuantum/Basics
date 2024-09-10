static bool out(char ch)
{
	if (prn_hdl == -2)
		Cauxout(ch);
	else if (prn_hdl == -3)
		Cprnout(ch);
	else
		Fwrite(prn_hdl, 1, &ch);
	return TRUE;
}