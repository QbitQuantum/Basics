//---------------------------------------------------------
CSG_String		SG_Get_String(double Value, int Precision, bool bScientific)
{
	CSG_String	s;

	if( Precision >= 0 )
	{
		s.Printf(SG_T("%.*f"), Precision, Value);
	}
	else if( Precision == -1 )
	{
		s.Printf(SG_T("%f"), Value);
	}
	else // if( Precision == -2 )
	{
		Precision	= SG_Get_Significant_Decimals(Value, abs(Precision));

		s.Printf(SG_T("%.*f"), SG_Get_Significant_Decimals(Value, abs(Precision)), Value);

		if( Precision > 0 )
		{
			while( s.Length() > 1 && s[s.Length() - 1] == '0' )
			{
				s	= s.Left(s.Length() - 1);
			}

			if( s.Length() > 1 && (s[s.Length() - 1] == '.' || s[s.Length() - 1] == ',') )
			{
				s	= s.Left(s.Length() - 1);
			}
		}
	}

	s.Replace(",", ".");

	return( s );
}