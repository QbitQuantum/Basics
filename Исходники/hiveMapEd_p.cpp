//-----------------------------
void GameMain()
{
  DDraw->FillSurface(DDraw->DDSBack,0) ;

  //turn
  CheckAction(mouse,EditInfo,world) ;
  mouse.button = mouse_NO ;
  //map scroll
  ThisTickCount = GetTickCount() ;
  if(ThisTickCount-MouseScrollTickCount>map_scroll_DELAY)
  {
    MouseScrollTickCount=ThisTickCount ;
    MoveMapByMouse(mouse.x,mouse.y,
                   (world->player[player_ID]).current_x_screen,(world->player[player_ID]).current_y_screen,
                   screen_HEIGHT,screen_WIDTH) ;
  } ;
  //drawind
  res=world->Draw(player_ID,screen,DDraw->DDSBack) ; // draw world
  CheckError(res,"world->Draw") ;
  if(mouse.x_frame>=0&&mouse.y_frame>=0)                                                                  //
  {                                                                                                       //  Draw
    res=(mouse.sprite)->Draw(DDraw->DDSBack,(mouse.x>>5)<<5,(mouse.y>>5)<<5,mouse.x_frame,mouse.y_frame) ;//  mouse
    CheckError(res,"mouse->Draw") ;                                                                       //
  } ;                                                                                                     //