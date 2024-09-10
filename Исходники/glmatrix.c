/* Re-randomize the state of one strip.
 */
static void
reset_strip (ModeInfo *mi, strip *s)
{
  matrix_configuration *mp = &mps[MI_SCREEN(mi)];
  int i;
  Bool time_displayed_p = False;  /* never display time twice in one strip */

  memset (s, 0, sizeof(*s));
  s->x = (GLfloat) (frand(GRID_SIZE) - (GRID_SIZE/2));
  s->y = (GLfloat) (GRID_SIZE/2 + BELLRAND(0.5));      /* shift top slightly */
  s->z = (GLfloat) (GRID_DEPTH * 0.2) - frand (GRID_DEPTH * 0.7);
  s->spinner_y = 0;

  s->dx = 0;
/*  s->dx = ((BELLRAND(0.01) - 0.005) * speed); */
  s->dy = 0;
  s->dz = (BELLRAND(0.02) * speed);

  s->spinner_speed = (BELLRAND(0.3) * speed);

  s->spin_speed = (int) BELLRAND(2.0 / speed) + 1;
  s->spin_tick  = 0;

  s->wave_position = 0;
  s->wave_speed = (int) BELLRAND(3.0 / speed) + 1;
  s->wave_tick  = 0;

  for (i = 0; i < GRID_SIZE; i++)
    if (do_clock &&
        !time_displayed_p &&
        (i < GRID_SIZE-5) &&   /* display approx. once per 5 strips */
	!(random() % (GRID_SIZE-5)*5))
      {
	int j;
	char text[80], *p;
        time_t now = time ((time_t *) 0);
        struct tm *tm = localtime (&now);
#if 1	// hacked by katahiromz
	for(p = timefmt; *p; p++)
	  if (p[0] == '%' && p[1] == 'l') p[1] = 'I';
#endif
	strftime (text, sizeof(text)-1, timefmt, tm);

	/* render time into the strip */
	for (j = 0; j < strlen(text) && i < GRID_SIZE; j++, i++)
	  {
	    s->glyphs[i] = char_map [((unsigned char *) text)[j]] + 1;
	    s->highlight[i] = True;
	  }

        time_displayed_p = True;	
      }
    else
      {
	int draw_p = (random() % 7);
	int spin_p = (draw_p && !(random() % 20));
	int g = (draw_p
		 ? mp->glyph_map[(random() % mp->nglyphs)] + 1
		 : 0);
	if (spin_p) g = -g;
	s->glyphs[i] = g;
	s->highlight[i] = False;
      }

  s->spinner_glyph = - (mp->glyph_map[(random() % mp->nglyphs)] + 1);
}