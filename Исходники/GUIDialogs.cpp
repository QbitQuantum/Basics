void EndPrinting ( void )
{
	if ( pd.hDC )
	{
		int nError = EndPage(pd.hDC); 
		if (nError <= 0)
		{
			DeleteDC ( pd.hDC ); 
			pd.hDC = NULL;
			return;
		}

		// end printing
		EndDoc(pd.hDC);

		// Delete DC when done.
		DeleteDC ( pd.hDC ); 
		pd.hDC = NULL;
	}
}