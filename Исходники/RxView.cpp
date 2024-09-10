//---------------------------------------------------------------------------
void __fastcall TRxViewDlg::DrawWater(BOOL fClear)
{
	if( m_pRxSet == NULL ) return;
	if( !m_pBitmapFFT ) return;

    TCanvas *pCanvas = m_pBitmapFFT->Canvas;

    int fo = m_pRxSet->m_pDem->m_CarrierFreq;
	if( !m_MouseDown ){
		int ww = m_WaterWidth / ((m_pRxSet->Is170()||m_pRxSet->IsMFSK()) ? 4 : 8);
		int cfo = fo;
        if( m_pRxSet->IsMFSK() ){
			int off = m_pRxSet->m_pDem->m_MFSK_BW/2;
			if( m_pRxSet->m_Mode == MODE_mfsk_L ){
				cfo -= off;
            }
            else {
				cfo += off;
            }
        }
		if( (cfo < (m_WaterLowFQ+ww)) || (cfo > (m_WaterHighFQ-ww)) ){
			CalcWaterCenter();
	    }
    }

    TRect rc;
   	rc.Left = 0; rc.Top = 0; rc.Right = m_fftXW; rc.Bottom = m_fftYW;
	if( fClear ){
	   	pCanvas->Brush->Color = MainVARI->m_tWaterColset[0].c;
   		pCanvas->Pen->Color = MainVARI->m_tWaterColset[0].c;
   		pCanvas->FillRect(rc);
        InitWater();
    }

	TRect trc = rc;
    rc.Bottom--;
	trc.Top++;
	pCanvas->CopyRect(trc, pCanvas, rc);
	int xo = ((m_WaterLowFQ+(MainVARI->m_FFTSampFreq/FFT_SIZE))*FFT_SIZE/MainVARI->m_FFTSampFreq) + 0.5;
	int xl = 0.5 + (fo - m_pRxSet->m_Speed - m_WaterLowFQ) * m_fftXW / m_WaterWidth;
	int xh = 0.5 + (fo + m_pRxSet->m_Speed - m_WaterLowFQ) * m_fftXW / m_WaterWidth;
   	int x, y, xx;
	int sum = 0;
    int max = 0;
    int wmax = 0;
    double k = 256.0 / m_StgWater.VW;
   	for( x = 0; x < m_fftXW; x++ ){
		xx = xo + (x * m_FFTWindow / m_fftXW);
        y = MainVARI->m_fftout[xx];
        if( max < y ) max = y;
		if( (x >= xl) && (x <= xh) ){
            if( wmax < y ) wmax = y;
        }
		sum += y;

        y = (y - m_StgWater.Sum) * k;
		if( y < 0 ) y = 0;
        if( y >= 256 ) y = 255;

        pCanvas->Pixels[x][0] = MainVARI->m_tWaterColors[y];
   	}
    sum /= m_fftXW;
	if( (wmax-sum) >= 320 ){
       	max = wmax;
    }
	m_StgWater.Sum = (m_StgWater.Sum + sum) / 2;
    m_StgWater.Max = (m_StgWater.Max + max) / 2;
    m_StgWater.VW = m_StgWater.Max - m_StgWater.Sum;
	int low, high;
	if( m_pRxSet->m_pFFT->m_FFTGain ){
       	low = 5120; high = 7000;
    }
    else {
       	low = 6000; high = 6000;
    }
    if( MainVARI->m_TX == txINTERNAL ) high = 100000;
    if( m_StgWater.VW < low ) m_StgWater.VW = low;
    if( m_StgWater.VW > high ) m_StgWater.VW = high;
}