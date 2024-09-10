//-----------------------------
void GameInit()
{
  app_run = 1 ;
  log_file = fopen("LOG\\debug.log","w+") ;
  if(log_file)fprintf(log_file,"GameInit\n") ;
  DDraw = new c_DDraw(main_handle,main_hinstance,&DDRestore,screen_WIDTH,screen_HEIGHT,screen_BITDEPTH) ;
  DDraw->Init(log_file);
  SetRect(&screen,0,0,screen_WIDTH-1,screen_HEIGHT-1) ;

  TIME =0 ;
  ThisTickCount=GetTickCount();
  LastTickCount=ThisTickCount;

  SpriteList = new c_SpriteList() ;
  SpriteList->Add(DDraw->DDraw,"art\\particicle.bmp",sprite_PARTICICLE_X_COUNT,sprite_PARTICICLE_Y_COUNT,log_file) ;
  SpriteList->Add(DDraw->DDraw,"art\\buildings.bmp",sprite_BUILDINGS_X_COUNT,sprite_BUILDINGS_Y_COUNT,log_file) ;
  SpriteList->Add(DDraw->DDraw,"art\\fontBig.bmp",font_STD_X_COUNT,font_STD_Y_COUNT,log_file) ;
  SpriteList->Add(DDraw->DDraw,"art\\buttons.bmp",sprite_BUTTONS_X_COUNT,sprite_BUTTONS_Y_COUNT,log_file) ;
  SpriteList->Add(DDraw->DDraw,"art\\panels.bmp",sprite_PANELS_X_COUNT,sprite_PANELS_Y_COUNT,log_file) ;
  SpriteList->Add(DDraw->DDraw,"art\\fontSmall.bmp",font_STD_X_COUNT,font_STD_Y_COUNT*3,log_file) ;

  panels = SpriteList->Find(sprite_PANELS_ID) ;

  player_ID = 0 ;

  font = new c_Font(SpriteList->Find(sprite_FONTBIG_ID)) ;

  mouse.x=1;
  mouse.y=1;
  mouse.sprite=SpriteList->Find(sprite_BUILDINGS_ID);
  mouse.x_frame = building_type_SELECT ;
  mouse.y_frame=building_y_frame_GOODPLACE;

  world = new c_World(SpriteList->Find(sprite_BUILDINGS_ID)) ;
  (world->player[player_ID]).current_x_screen=94;
  (world->player[player_ID]).current_y_screen=94;


  (world->building[100][100]).type = building_type_MAIN ;

  (world->building[105][105]).type  = building_type_BASE ;
  (world->building[105][105]).owner = building_type_BASE ;
  int start_x=105-building_territory_ADD_COUNT,
      end_x  =105+building_territory_ADD_COUNT,
      start_y=105-building_territory_ADD_COUNT,
      end_y  =105+building_territory_ADD_COUNT;
  if(start_x<0)start_x=0;
  if(end_x>=world_X_COUNT)end_x=world_X_COUNT-1;
  if(start_y<0)start_y=0;
  if(end_y>=world_Y_COUNT)end_y=world_Y_COUNT-1;
  FILE *f=fopen("LOG\\territory.log","w+") ;
  for(int x=start_x;x<=end_x;x++)
    for(int y=start_y;y<=end_y;y++)
    {
      fprintf(f,"coord(%d;%d)\n",x,y) ;
      if((world->building[x][y]).territory==building_territory_NEUTRAL)
      {
        fprintf(f,"set to %d\n",player_ID);
        (world->building[x][y]).territory=player_ID ;
      };
    } ;
  fclose(f) ;

  (world->player[player_ID]).show_territory=1;

  s_ParticicleInfo PInfo ;
  PInfo.TurnTime = 1 ;
  PInfo.GenerateTime = 50 ;
  PInfo.TurnCount = 1000 ;
  PInfo.GenerateCountPerTurn = 1 ;
  PInfo.width = screen_X_CELL_SIZE ;
  PInfo.height = screen_Y_CELL_SIZE ;
  PInfo.enable = 1 ;
  PInfo.dx = 0.5 ;
  PInfo.dy = 0.0 ;
  PInfo.dxVariation = 0 ;
  PInfo.dyVariation = 0 ;
  PInfo.x_frame_count = 3 ;
  PInfo.y_frame_count = 3 ;
  PInfo.ParticicleCount = 100 ;
  particicle = new c_Particicle(SpriteList->Find(sprite_PARTICICLE_ID),100,100,PInfo) ;

  HiveElements = new c_HiveElements(world,&mouse,SpriteList->Find(sprite_BUTTONS_ID),
                                    build_panel_X,build_panel_Y,common_panel_X,common_panel_Y,
                                    SpriteList->Find(sprite_FONTSMALL_ID),player_ID) ;
} ;