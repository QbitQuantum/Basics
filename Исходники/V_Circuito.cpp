/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormR::ImprimirVClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	TPrinter	*I = Printer();
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	Graphics::TBitmap * bmp = new Graphics::TBitmap();
	bmp = FormR->Image1->Picture->Bitmap;

	// Impresion en vertical.
	I->Orientation = poPortrait;
	bmp->Width = tamanioCircuito.x;
	bmp->Height = tamanioCircuito.y;

	/*~~~~~~~*/
	TRect	rc;
	/*~~~~~~~*/

	rc.Left = 0;
	rc.Top = 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	double	proporcionI = (double) ((double) I->PageHeight / (double) I->PageWidth);
	double	factor = 2.3;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
	rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);

	/*~~~~~~~~~~~~~~~~~~~~*/
	bool	imprimir = true;
	/*~~~~~~~~~~~~~~~~~~~~*/

	if(rc.Right >= I->PageWidth || rc.Bottom >= I->PageHeight)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	m = ANSIMENSAJE(msgVisuCircuitoErrorImprimir);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(MessageDlg(m, mtError, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		{
			while(rc.Right >= I->PageWidth || rc.Bottom >= I->PageHeight)
			{
				factor -= 0.1;
				rc.Right = (int) ((double) bmp->Width * (double) proporcionI * factor);
				rc.Bottom = (int) ((double) bmp->Height * (double) proporcionI * factor);
			}	// end-while
			imprimir = true;
		}
		else
			imprimir = false;
	}			// end-if

	if(imprimir == true)
	{
		I->BeginDoc();
		I->Canvas->StretchDraw(rc, bmp);
		I->EndDoc();
	}			// end-if
}