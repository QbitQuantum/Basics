bool MagicFun2( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep)
{
	if( nStep < 2 ) nStep = 2;
	int num=height/nStep;
	for(int i=0;i<nStep;i++)
	{
		for(int j=0;j<num;j++)
		{
			BitBlt( hDestDC,xd,yd+j*nStep+i,width,1, hSrcDC,x, y+j*nStep+i,SRCCOPY);
		}
		SleepEx( nDelay);
	}
	BitBlt( hDestDC , xd , yd , width , height ,hSrcDC,x,y,SRCCOPY);
	return TRUE;
}