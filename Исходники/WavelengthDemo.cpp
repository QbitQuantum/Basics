//-------------------------------------------------------------------------------------------
void ShowLambda(void) 
{	char *res;
	long ver = 0;
	res = (char *)malloc(20);

	// calculate display precision
	if ( dblLambda >= 1000.0 ) ver = 2; else ver = 1;
	if ( iVersion >= 4 ) 
		ver += iVersion;

	if ( dblLambda < 1.0 ) 
	{
		gcvt(dblLambda, 2, res);
		// < 1 is errorvalue, so write w/o "nm"
		SetDlgItemText(hwDlg, IDC_LAMBDA, res);
	}
	else
	{
		gcvt(dblLambda, ver, res);
		wsprintf(cBuffer, lpszLambdaTemplate, res);
		// finally here write the calculated wavelength
		SetDlgItemText(hwDlg, IDC_LAMBDA, cBuffer);
	}

	free(res);
}