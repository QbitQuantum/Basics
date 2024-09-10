//---------------------------------------------------------------------
void __fastcall TClockAdjDlg::TimerTimer(TObject *Sender)
{
	if( pBitmap == NULL ) return;
	if( pDem == NULL ) return;
	if( pTick == NULL ) return;

	int *p = pTick->GetData();
	if( p == NULL ) return;

	TCanvas *tp = pBitmap->Canvas;

	int mx = -MAXINT;
	int mi = MAXINT;
	int x, xx, d;
	double k1 = 16384.0/double(m_agcMax - m_agcMin);
	double k2;
	if( SBAGC->Down ){
		k2 = 128.0 / 16384.0;
	}
	else {
		k2 = (128.0 * (s_Gain & 0x00ff)) / (4096 * 16);
	}
	int ax = -1;
	for( xx = 0; xx < pTick->m_Samp; xx++ ){
		int xv = xx + m_rBase;
		x = fmod(xv, m_Samp);
		x = x * pBitmap->Width / m_Samp;
		if( ax != x ){
			ax = x;
			if( !x ){
				if( m_MaxD ){
					tp->Pixels[m_MaxP][0] = clRed;
				}
				m_MaxD = 0;
				m_MaxP = 0;
				TRect rc;
				rc.Left = 0;
				rc.Right = pBitmap->Width - 1;
				rc.Top = 0;
				rc.Bottom = pBitmap->Height - 2;
				TRect src(rc);
				src.Bottom--;
				rc.Top++;
				tp->CopyRect(rc, tp, src);
			}
			d = p[xx];
			if( m_MaxD < d ){
				m_MaxD = d;
				m_MaxP = x;
			}
			if( mx < d ) mx = d;
			if( mi > d ) mi = d;
			if( SBAGC->Down ){
				d -= m_agcMin;
				if( m_agcMax > 0 ) d = double(d) * k1;
			}
			d = double(d) * k2;

			if( d >= 128 ) d = 127;
			if( d <= 0 ) d = 0;
			tp->Pixels[x][0] = TColor(ColorTable[127-d]);
		}
	}
	m_rBase += pTick->m_Samp;
#if 0
	for( x = 0; x < XR; x++){
		xx = (x * pTick->m_Samp)/pBitmap->Width;
		d = p[xx];
		if( mx < d ) mx = d;
		if( mi > d ) mi = d;
		if( SBAGC->Down ){
			d -= m_agcMin;
			if( m_agcMax > 0 ) d = double(d) * k1;
		}
		d = double(d) * k2;

		if( d >= 128 ) d = 127;
		if( d <= 0 ) d = 0;
		tp->Pixels[x][0] = TColor(ColorTable[127-d]);
	}
#endif
	m_agcSumMax -= m_agcMax;
	m_agcSumMax += mx;
	if( m_agcSumMax < (4096*AGCAVG) ) m_agcSumMax = (4096*AGCAVG);
	m_agcMax = m_agcSumMax / AGCAVG;
	m_agcMin = mi;
	if( m_agcMin > 2048 ) m_agcMin = 2048;
	m_PointY++;
	PaintBox->Canvas->Draw(0, 0, (TGraphic*)pBitmap);
	PaintCursor();
}