EXPORT_C void CHuiCanvasGc::SetDefaults()
	{
	SetTextStyle(0);
    SetPenColor(TRgb(255,255,255));
	SetPenWidth(1.0);
	SetOpacity(1.0);
	SetPolygonDrawMode(EHuiNoFill);
	SetTextAlign(EHuiAlignHLeft, EHuiAlignVTop);
    SetDrawMode(EHuiCanvasDrawModeBlend);
    EnableEffectiveOpacity(ETrue);    
    SetPolygonFillTexture(NULL);
    SetPolygonFillTextureOrigin(TPoint(0,0));
	CancelClipping();
	}