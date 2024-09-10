arithmtype MulDivMod(void)
{
	int Val=0;
	arithmtype Res = Pow();
	while(1)
	{
		if ( ErrorDesc )
			break;
//if (UnderVerify)
//printf("MulDivMod_Expr=%s\n",Expr);
		if (*Expr=='*')
		{
			Expr++;
			Res = Res * Pow();
		}
		else
		if (*Expr=='/')
		{
			Expr++;
			Val = Pow();
			if ( ErrorDesc==NULL )
				Res = Res / Val;
		}
		else
		if (*Expr=='%')
		{
			Expr++;
			Val = Pow();
			if ( ErrorDesc==NULL )
				Res = Res % Val;
		}
		else
		{
			break;
		}
	}
	return Res;
}