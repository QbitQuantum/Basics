//-----------------------Render--------------------------------------
//
//	given a GDI surface this function renders the ship and the
//	landing pad
//-------------------------------------------------------------------
void CController::Render(HDC &surface)
{
  //change the mapping mode so that the origin is at the bottom left
  //of our window and so that the y axis increases as it goes from
  //bottom to top     
  SetMapMode( surface, MM_ANISOTROPIC );
  SetViewportExtEx( surface, 1, -1, NULL );
  SetWindowExtEx( surface, 1, 1, NULL );
  SetViewportOrgEx( surface, 0, m_cyClient, NULL );

   //select in the pen we want to use
  HPEN OldPen = (HPEN)SelectObject(surface, GetStockObject(WHITE_PEN));

  //first render the stars
  for (int i=0; i<m_vecStarVB.size(); ++i)
  {
    //add some twinkle
    if (RandFloat() > 0.1)
    {
      SetPixel(surface, m_vecStarVB[i].x, m_vecStarVB[i].y, RGB(255, 255, 255));
    }
  }
  
  //render the user controlled ship
  m_pUserLander->Render(surface);

  //render the landing pad...
  RenderLandingPad(surface);

      
  //return the mapping mode to its default state so text is rendered
  //correctly
  SetMapMode( surface, MM_ANISOTROPIC );
  SetViewportExtEx( surface, 1, 1, NULL );
  SetWindowExtEx( surface, 1, 1, NULL );
  SetViewportOrgEx( surface, 0, 0, NULL );

  //Render additional information
  SetBkMode(surface, TRANSPARENT);
  SetTextColor(surface, RGB(0,0,255));
 
  string s= "Cursor Keys - Rotate   Spacebar - Thrust   R - Retry";
  TextOutA(surface, 30, m_cyClient - 20, s.c_str(), s.size());

  //replace the pen
  SelectObject(surface, OldPen);
}