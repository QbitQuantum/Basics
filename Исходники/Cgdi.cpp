Cgdi::Cgdi()
{
  m_BlackPen = CreatePen(PS_SOLID, 1, colors[black]);
  m_WhitePen = CreatePen(PS_SOLID, 1, colors[white]);
  m_RedPen = CreatePen(PS_SOLID, 1, colors[red]);
  m_GreenPen = CreatePen(PS_SOLID, 1, colors[green]);
  m_BluePen = CreatePen(PS_SOLID, 1, colors[blue]);
  m_GreyPen = CreatePen(PS_SOLID, 1, colors[grey]);
  m_PinkPen = CreatePen(PS_SOLID, 1, colors[pink]);
  m_YellowPen = CreatePen(PS_SOLID, 1, colors[yellow]);
  m_OrangePen = CreatePen(PS_SOLID, 1, colors[orange]);
  m_PurplePen = CreatePen(PS_SOLID, 1, colors[purple]);
  m_BrownPen = CreatePen(PS_SOLID, 1, colors[brown]);
  
  m_DarkGreenPen = CreatePen(PS_SOLID, 1, colors[dark_green]);

  m_LightBluePen = CreatePen(PS_SOLID, 1, colors[light_blue]);
  m_LightGreyPen = CreatePen(PS_SOLID, 1, colors[light_grey]);
  m_LightPinkPen = CreatePen(PS_SOLID, 1, colors[light_pink]);

  m_ThickBlackPen = CreatePen(PS_SOLID, 2, colors[black]);
  m_ThickWhitePen = CreatePen(PS_SOLID, 2, colors[white]);
  m_ThickRedPen = CreatePen(PS_SOLID, 2, colors[red]);
  m_ThickGreenPen = CreatePen(PS_SOLID, 2, colors[green]);
  m_ThickBluePen = CreatePen(PS_SOLID, 2, colors[blue]);

  m_GreenBrush = CreateSolidBrush(colors[green]);
  m_RedBrush   = CreateSolidBrush(colors[red]);
  m_BlueBrush  = CreateSolidBrush(colors[blue]);
  m_GreyBrush  = CreateSolidBrush(colors[grey]);
  m_BrownBrush = CreateSolidBrush(colors[brown]);
  m_YellowBrush = CreateSolidBrush(colors[yellow]);
  m_LightBlueBrush = CreateSolidBrush(colors[light_blue]);
  m_DarkGreenBrush = CreateSolidBrush(colors[dark_green]);
  m_OrangeBrush = CreateSolidBrush(colors[orange]);
  m_PurpleBrush = CreateSolidBrush(colors[purple]);

  m_tmpPen = CreatePen(PS_SOLID,1,RGB(0,0,0));
  m_tmpBrush = CreateSolidBrush(RGB(0,0,0));

  m_hdc = NULL;
}