unsigned int print_ticket(unsigned int source,unsigned int destination)
{
	unsigned int final_amount =0,final_amount_cpy =0,fx =0,final_length_cpy =0,j,final_amount_length =0;
	unsigned char final_disp[20],afx[5];
	if(source > destination)
	{
		final_amount = (source - destination)*5;
	}
	if(destination>source)
	{
		final_amount = (destination - source)*5;
	}	
	final_amount_cpy = final_amount;
	final_disp[0] = 'R';
	final_disp[1] = 's';
	final_disp[2] = ':';
	final_disp[3] = '1';
	final_disp[4] = '*';
	final_amount_length=10;
		for(j=0;j<=final_amount_length;j++)
			{
			fx=final_amount_cpy%10;
			afx[j]=inttochar(fx);
			final_amount_cpy = final_amount_cpy/10;
			}
		final_length_cpy=final_amount_length;
		for(j=0;j<=final_amount_length;j++)
			{
			final_disp[j+5]=afx[final_length_cpy-1];
			final_length_cpy=final_length_cpy-1;
			}
	final_disp[final_amount_length+5] = '=';
	final_length_cpy=final_amount_length;
		for(j=0;j<=final_amount_length;j++)
		{
			final_disp[final_amount_length+6+j]=afx[final_length_cpy-1];
			final_length_cpy=final_length_cpy-1;
		}
	DelayMs(2);
	strcpypgm2ram((char*)LCDText, final_disp);
	display_row(1);
	//display_row(1,final_disp);
	return final_amount;
}