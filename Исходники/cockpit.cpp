void CCockpit::DrawEnergy (void)
{
	static int nIdEnergy = 0;

	char szEnergy [20];

#if 0
CBitmap* bmP = BitBlt (GAUGE_NUMERICAL, NUMERICAL_GAUGE_X, NUMERICAL_GAUGE_Y);
#else
PageInGauge (GAUGE_NUMERICAL);
CBitmap* bmP = gameData.pig.tex.bitmaps [0] + GaugeIndex (GAUGE_NUMERICAL);
#endif
CCanvas::Push ();
CCanvas::SetCurrent (CurrentGameScreen ());
fontManager.SetColorRGBi (RGBA_PAL2 (25, 18, 6), 1, 0, 0);
sprintf (szEnergy, "%d", m_info.nEnergy);
int w, h, aw;
fontManager.SetScale (floor (float (CCanvas::Current ()->Width ()) / 640.0f));
fontManager.Current ()->StringSize (szEnergy, w, h, aw);
nIdEnergy = PrintF (&nIdEnergy,-(ScaleX (NUMERICAL_GAUGE_X + bmP->Width () / 2) - w / 2), 
						  NUMERICAL_GAUGE_Y + (gameStates.video.nDisplayMode ? 5 : 2), szEnergy);
fontManager.SetScale (1.0f);
CCanvas::Pop ();
}