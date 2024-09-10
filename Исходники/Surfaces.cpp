byte CSurface3DFrame::FitPanel()//Rectangle()
  {
  byte eTryDiv=C3D_DivNxN;
  if (m_p3D->m_pBoundary)
    {
    CSurface3DBoundary &B=*m_p3D->m_pBoundary;
    if (m_dXMin>=B.m_XMin && m_dXMax<=B.m_XMax &&
        m_dYMin>=B.m_YMin && m_dYMax<=B.m_YMax)
      {
      double BYxmn=B.m_FnYx(m_dXMin);
      double BYxmx=B.m_FnYx(m_dXMax);
      double BXymn=B.m_FnXy(m_dYMin);
      double BXymx=B.m_FnXy(m_dYMax);
      byte LCross=(m_dYMin<BYxmn && BYxmn<m_dYMax) ? 1 : 0;
      byte RCross=(m_dYMin<BYxmx && BYxmx<m_dYMax) ? 2 : 0;
      byte BCross=(m_dXMin<BXymn && BXymn<m_dXMax) ? 4 : 0;
      byte TCross=(m_dXMin<BXymx && BXymx<m_dXMax) ? 8 : 0;
      eTryDiv=PanelLayout[LCross+RCross+TCross+BCross].Divs;

      double Val1=dNAN;
      double Val2=dNAN;
      switch (eTryDiv)
        {
        case C3D_Div2V:
          {
          Val1=BCross ? BXymn : BXymx;
          CSurface3DFrame Frames[2];
          Frames[0].Initialise(m_p3D, m_iLevel+1, m_dXMin, Val1,    1, m_dYMin, m_dYMax, 1);
          Frames[1].Initialise(m_p3D, m_iLevel+1, Val1,    m_dXMax, 1, m_dYMin, m_dYMax, 1);
          if (!FitAndTestPanels(2,1, Frames))
            eTryDiv=C3D_DivNxN;
          }
          break;
        case C3D_Div3V:
          {
          Val1=Min(BXymn, BXymx);
          Val2=Max(BXymn, BXymx);
          CSurface3DFrame Frames[3];
          Frames[0].Initialise(m_p3D, m_iLevel+1, m_dXMin, Val1,    1, m_dYMin, m_dYMax, 1);
          Frames[1].Initialise(m_p3D, m_iLevel+1, Val1,    Val2,    1, m_dYMin, m_dYMax, 1);
          Frames[2].Initialise(m_p3D, m_iLevel+1, Val2,    m_dXMax, 1, m_dYMin, m_dYMax, 1);
          if (!FitAndTestPanels(3,1, Frames))
            eTryDiv=C3D_DivNxN;
          }
          break;
        case C3D_Div2H:
          {
          Val1=LCross ? BYxmn : BYxmx;
          CSurface3DFrame Frames[2];
          Frames[0].Initialise(m_p3D, m_iLevel+1, m_dXMin, m_dXMax, 1, m_dYMin,   Val1, 1);
          Frames[1].Initialise(m_p3D, m_iLevel+1, m_dXMin, m_dXMax, 1, Val1,   m_dYMax, 1);
          if (!FitAndTestPanels(1,2, Frames))
            eTryDiv=C3D_DivNxN;
          }
          break;
        case C3D_Div3H:
          {
          Val1=Min(BYxmn, BYxmx);
          Val2=Max(BYxmn, BYxmx);
          CSurface3DFrame Frames[3];
          Frames[0].Initialise(m_p3D, m_iLevel+1, m_dXMin, m_dXMax, 1, m_dYMin,   Val1, 1);
          Frames[1].Initialise(m_p3D, m_iLevel+1, m_dXMin, m_dXMax, 1, Val1,      Val2, 1);
          Frames[2].Initialise(m_p3D, m_iLevel+1, m_dXMin, m_dXMax, 1, Val2,   m_dYMax, 1);
          if (!FitAndTestPanels(1,3, Frames))
            eTryDiv=C3D_DivNxN;
          }
          break;
        case C3D_Div2x2:
          {
          Val1=BCross ? BXymn : BXymx;
          Val2=LCross ? BYxmn : BYxmx;
          CSurface3DFrame Frames[4];
          Frames[0].Initialise(m_p3D, m_iLevel+1, m_dXMin,    Val1, 1, m_dYMin,    Val2, 1);
          Frames[1].Initialise(m_p3D, m_iLevel+1, Val1,    m_dXMax, 1, m_dYMin,    Val2, 1);
          Frames[2].Initialise(m_p3D, m_iLevel+1, m_dXMin,    Val1, 1, Val2,    m_dYMax, 1);
          Frames[3].Initialise(m_p3D, m_iLevel+1, Val1,    m_dXMax, 1, Val2,    m_dYMax, 1);
          if (!FitAndTestPanels(2,2, Frames))
            eTryDiv=C3D_DivNxN;
          }
          break;
        case C3D_DivNxN:
          if (m_nDivsX*m_nDivsY<2)
            DoBreak();
          break;
        case C3D_Bad:
          DoBreak();
        }
      }
    else
      eTryDiv=C3D_Div1x1;
    }
  else
    eTryDiv=C3D_Div1x1;
  
  if (eTryDiv==C3D_Div1x1)
    {
    CSurface3DPanel * pPanel=BuildPanel();
    
    if (m_iLevel>=8)
      DoBreak();

    if (pPanel->CheckFit(this))
      {
      m_eDivision=eTryDiv;
      m_pPanel=pPanel;
      #if dbgSurfaces
      if (dbg3DTrack())
        dbgpln("Add new Panel %-20s %-5s %08x [%2i] %14.8f %14.8f",
               m_p3D->Name(), s_sDivText[m_eDivision], m_pPanel, m_iLevel, 0.5*(m_dXMin+m_dXMax), 0.5*(m_dYMin+m_dYMax));
      #endif
      }
    else
      {
      delete pPanel;
      eTryDiv= C3D_DivNxN;
      #if dbgSurfaces
      if (dbg3DTrack())
        dbgpln("Drill Down    %-20s %-5s %8s [%2i] %14.8f %14.8f",
               m_p3D->Name(), s_sDivText[eTryDiv], "", m_iLevel, 0.5*(m_dXMin+m_dXMax), 0.5*(m_dYMin+m_dYMax));
      #endif
      }
    }
  
  if (eTryDiv==C3D_DivNxN)
    {
    if (m_nDivsX*m_nDivsY<2)
      DoBreak();
    ASSERT(m_Frames==NULL);
    long nElements=m_nDivsX*m_nDivsY;
    m_Frames=new LPCSurface3DFrame[nElements];
    for (int i=0; i<nElements; i++)
      m_Frames[i]= NULL;
    }
  m_eDivision=eTryDiv;
  return eTryDiv;
  }