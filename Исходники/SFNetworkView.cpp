void SFNetworkView::updateView()
{
	if ( !PNetwork ) 
		return;
	if ( !UpdateDisplay )
		return;
	
	SFRetina& Retina = PNetwork->getRetina();
	UINT32 RetinaWidth = Retina.getWidth();
	
	HDC DC = GetDC( Handle);

	HDC BackBufferDC = CreateCompatibleDC( DC);
	SelectObject( BackBufferDC , BackBuffer);

	PatBlt( BackBufferDC, 0,0, ClientRect.right , ClientRect.bottom, WHITENESS);

	HDC RetinaDC = Retina.startDraw(DC);
	BitBlt(  BackBufferDC , 0, 0, Retina.getWidth() , Retina.getWidth() , RetinaDC , 0, 0, SRCCOPY);
	Retina.endDraw();
	
	std::vector<SFLayer>& Layers = PNetwork->getLayers();
	
	UINT32 OffsetX = RetinaWidth + 2 ;
	UINT32 OffsetY = RetinaWidth + 2;
	for ( UINT32 I = 0 ; I < Layers.size() ; I++ )
	{
		displayOutput(BackBufferDC , Layers[I].getWidth() , Layers[I].getOutput(), Layers[I].getTargetOutput() == NULL ? Layers[I].getSnapshot():Layers[I].getTargetOutput()   , OffsetX, 0 );
		OffsetX += Layers[I].getWidth() + 2 ;
	}
	OffsetX *= 2;
	if ( SelectedLayer == -1 )
		displayReconstruction(BackBufferDC, Layers[0] , Layers[0].getOutput() , 0 , OffsetY);
	else
		displayWeights( BackBufferDC , Layers[SelectedLayer], 0, OffsetY);
	OffsetY += RetinaWidth + 2; 

	char Buf[256];
	sprintf_s( Buf , 256 , "%d" , PNetwork->getTrainingCount() );
	TextOutA( BackBufferDC , RetinaWidth + 4 , RetinaWidth +  5 , Buf, strlen(Buf) );

	StretchBlt( DC , 0, 0, ClientRect.right , (OffsetY *  ClientRect.right) / OffsetX , BackBufferDC, 0, 0, OffsetX , OffsetY ,SRCCOPY);
	
	DeleteDC(BackBufferDC);
	ReleaseDC(Handle,DC);
	Scale = (float)ClientRect.right / (float)OffsetX;
}