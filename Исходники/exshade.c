int main(int argc, char *argv[])
{
   PALETTE pal;
   BITMAP *buffer;
   BITMAP *planet;
   char buf[256];

   if (allegro_init() != 0)
      return 1;
   install_keyboard();
   install_mouse();

   if (set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0) != 0) {
      if (set_gfx_mode(GFX_SAFE, 320, 240, 0, 0) != 0) {
	 set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 allegro_message("Unable to set any graphic mode\n%s\n",
			 allegro_error);
	 return 1;
      }
   }

   replace_filename(buf, argv[0], "planet.pcx", sizeof(buf));

   planet = load_bitmap(buf, pal);
   if (!planet) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error reading %s\n", buf);
      return 1;
   }

   buffer = create_bitmap(SCREEN_W, SCREEN_H);
   clear_bitmap(buffer);

   set_palette(pal);

   create_rgb_table(&rgb_table, pal, NULL);
   rgb_map = &rgb_table;

   create_light_table(&light_table, pal, 0, 0, 0, NULL);
   color_map = &light_table;

   set_trans_blender(0, 0, 0, 128);

   do {
      poll_mouse();

      draw_gouraud_sprite(buffer, planet, SCREEN_W/2, SCREEN_H/2,
			  distance(SCREEN_W/2, SCREEN_H/2, mouse_x, mouse_y),
			  distance(SCREEN_W/2 + planet->w, SCREEN_H/2,
				   mouse_x, mouse_y),
			  distance(SCREEN_W/2 + planet->w,
				   SCREEN_H/2 + planet->h, mouse_x, mouse_y),
			  distance(SCREEN_W/2, SCREEN_H/2 + planet->h,
				   mouse_x, mouse_y));

      textout_ex(buffer, font, "Gouraud Shaded Sprite Demo", 0, 0,
		 palette_color[10], -1);

      show_mouse(buffer);
      blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
      show_mouse(NULL);

   } while (!keypressed());

   destroy_bitmap(planet);
   destroy_bitmap(buffer);

   return 0;
}