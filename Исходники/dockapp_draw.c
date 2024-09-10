void
dockapp_draw_bar_calculate( float draw_size, int bar_draw_x, int bar_draw_y )
{
   float draw_percent_f;
   int draw_percent;

   draw_percent_f = ( GET_HRS_F( draw_size ) / DOCKAPP_BAR_WIDTH ) * 100.0f;
   draw_percent = ( int ) nearbyint( draw_percent_f );

  if ( DOCKAPP_BAR_WIDTH == draw_percent )
  {
     dockapp_draw_bar( draw_percent,
		       bar_draw_x,
		       bar_draw_y,
		       DOCKAPP_BAR_OFF_X,
		       DOCKAPP_BAR_OFF_Y );
  }
  else
  {
     dockapp_draw_bar( draw_percent,
		       bar_draw_x,
		       bar_draw_y,
		       DOCKAPP_BAR_ON_X,
		       DOCKAPP_BAR_ON_Y );
  }
}