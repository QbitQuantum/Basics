void  TfrmSoundLib::OnAttenuationDraw(CanvasValue* sender, void* _canvas, const Irect& _rect)
{
	TCanvas* canvas 	= (TCanvas*)_canvas;
    const TRect& rect	= *((TRect*)&_rect);
//	canvas
    int w = rect.Width();
    int h = rect.Height();
    int x0= rect.left;
    int y0= rect.top;

    canvas->Brush->Color = clBlack;
    canvas->FillRect(rect);
    canvas->Pen->Color = TColor(0x00006600);
    canvas->MoveTo(x0,y0);
    for (int i=0; i<X_GRID+1; i++){
        canvas->LineTo(x0+i*w/X_GRID,y0+h);
        canvas->MoveTo(x0+(i+1)*w/X_GRID,y0+0);
    }
    canvas->MoveTo(x0+0,y0+0);
    for (int j=0; j<Y_GRID+1; j++){
        canvas->LineTo(x0+w,y0+j*h/Y_GRID);
        canvas->MoveTo(x0+0,y0+(j+1)*h/Y_GRID);
    }
    canvas->Pen->Color = clYellow;
    canvas->MoveTo(x0+0,y0+iFloor(float(h)-float(h)*0.01f)); // snd cull = 0.01f
    canvas->LineTo(x0+w,y0+iFloor(float(h)-float(h)*0.01f));

    ESoundThumbnail* thm	= m_THM_Current.back();
    float d_cost 			= thm->MaxDist()/w;
    AnsiString temp;
//    float v = m_D3D.range;
//    temp.sprintf("Range = %.2f",v); lbRange->Caption = temp;
    canvas->Pen->Color = clLime;
    for (int d=1; d<w; d++){
        float R = d*d_cost;
    	float b = thm->MinDist()/(psSoundRolloff*R);
//		float b = m_Brightness/(m_Attenuation0+m_Attenuation1*R+m_Attenuation2*R*R);
        float bb = h-(h*b);
        int y = iFloor(y0+bb); clamp(y,int(rect.Top),int(rect.Bottom));
        if (1==d)	canvas->MoveTo(x0+d,y);
        else		canvas->LineTo(x0+d,y);
    }
}