void WDL_VirtualStaticText::OnPaint(LICE_IBitmap *drawbm, int origin_x, int origin_y, RECT *cliprect)
{
  RECT r=m_position;
  r.left+=origin_x;
  r.right+=origin_x;
  r.top += origin_y;
  r.bottom += origin_y;

  if (m_bkbm && m_bkbm->bgimage)
  {
    WDL_VirtualWnd_ScaledBlitBG(drawbm,m_bkbm,
      r.left,r.top,r.right-r.left,r.bottom-r.top,
      r.left,r.top,r.right-r.left,r.bottom-r.top,
      1.0,LICE_BLIT_MODE_COPY|LICE_BLIT_FILTER_BILINEAR|LICE_BLIT_USE_ALPHA);

    if (m_dotint && LICE_GETA(m_bg)) 
    {
        float amt = LICE_GETA(m_bg)/255.0f;

        // todo: apply amt

        float rv=LICE_GETR(m_bg)/255.0f;
        float gv=LICE_GETG(m_bg)/255.0f;
        float bv=LICE_GETB(m_bg)/255.0f;

        float avg=(rv+gv+bv)*0.33333f;
        if (avg<0.05f)avg=0.05f;

        float sc=0.5f*amt;
        float sc2 = (amt-sc)/avg;

        float sc3=32.0f * amt;
        float sc4=64.0f*(avg-0.5f) * amt;

        // tint
        LICE_MultiplyAddRect(drawbm,
          r.left,r.top,
            r.right-r.left,
            r.bottom-r.top,
            sc+rv*sc2 + (1.0-amt),
            sc+gv*sc2 + (1.0-amt),
            sc+bv*sc2 + (1.0-amt),
            1,
            (rv-avg)*sc3+sc4,
            (gv-avg)*sc3+sc4,
            (bv-avg)*sc3+sc4,
            0);
    }
  }
  else 
  {
    if (LICE_GETA(m_bg))
    {
      LICE_FillRect(drawbm,r.left,r.top,r.right-r.left,r.bottom-r.top,m_bg,LICE_GETA(m_bg)/255.0f,LICE_BLIT_MODE_COPY);
    }

    if (m_wantborder)
    {    
      int cidx=COLOR_3DSHADOW;

      int pencol = WDL_STYLE_GetSysColor(cidx);
      pencol = LICE_RGBA_FROMNATIVE(pencol,255);

      LICE_Line(drawbm,r.left,r.bottom-1,r.left,r.top,pencol,1.0f,LICE_BLIT_MODE_COPY,false);
      LICE_Line(drawbm,r.left,r.top,r.right-1,r.top,pencol,1.0f,LICE_BLIT_MODE_COPY,false);
      cidx=COLOR_3DHILIGHT;
      pencol = WDL_STYLE_GetSysColor(cidx);
      pencol = LICE_RGBA_FROMNATIVE(pencol,255);
      LICE_Line(drawbm,r.right-1,r.top,r.right-1,r.bottom-1,pencol,1.0f,LICE_BLIT_MODE_COPY,false);
      LICE_Line(drawbm,r.right-1,r.bottom-1,r.left,r.bottom-1,pencol,1.0f,LICE_BLIT_MODE_COPY,false);

      r.left++;
      r.bottom--;
      r.top++;
      r.right--;

    }
  }


  if (m_text.Get()[0])
  {

    r.left += m_margin_l;
    r.right -= m_margin_r;
    r.top += m_margin_t;
    r.bottom -= m_margin_b;

    m_didvert=m_vfont && (r.right-r.left)<(r.bottom-r.top);
    LICE_IFont *font = m_didvert ? m_vfont : m_font;


    if (font)
    {
      font->SetBkMode(TRANSPARENT);

    
      m_didalign=m_align;
      if (m_didalign==0)
      {
        RECT r2={0,0,0,0};
        font->DrawText(drawbm,m_text.Get(),-1,&r2,DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_NOPREFIX|DT_CALCRECT);
        if (r2.right > r.right-r.left) m_didalign=-1;
      }

      int tcol=m_fg ? m_fg : LICE_RGBA_FROMNATIVE(WDL_STYLE_GetSysColor(COLOR_BTNTEXT));
      font->SetTextColor(tcol);
      if (m_fg && LICE_GETA(m_fg) != 0xff) font->SetCombineMode(LICE_BLIT_MODE_COPY,LICE_GETA(m_fg)/255.0f);
      font->DrawText(drawbm,m_text.Get(),-1,&r,DT_SINGLELINE|DT_VCENTER|(m_didalign<0?DT_LEFT:m_didalign>0?DT_RIGHT:DT_CENTER)|DT_NOPREFIX);
      if (m_fg && LICE_GETA(m_fg) != 0xff) font->SetCombineMode(LICE_BLIT_MODE_COPY,1.0f);
    }


  }
  WDL_VWnd::OnPaint(drawbm,origin_x,origin_y,cliprect);
}