static struct throbber *
make_throbber (struct state *st, Drawable d, int w, int h, unsigned long pixel)
{
  XGCValues gcv;
  unsigned long flags;
  struct throbber *t = (struct throbber *) malloc (sizeof (*t));
  t->x = w / 2;
  t->y = h / 2;
  t->max_size = (w > h ? w : h);
  //t->speed = get_integer_resource (st->dpy, "speed", "Speed");
  t->speed = speed;
  t->fuse = 1 + (random() % 4);
  //t->thickness = get_integer_resource (st->dpy, "thickness", "Thickness");
  t->thickness = thickness;

  if (t->speed < 0) t->speed = -t->speed;
  t->speed += (((random() % t->speed) / 2) - (t->speed / 2));
  if (t->speed > 0) t->speed = -t->speed;

  flags = GCForeground;
# ifndef HAVE_COCOA
  if (st->transparent_p)
    {
      gcv.foreground = ~0L;
      gcv.plane_mask = st->base_pixel | st->plane_masks[random() % st->nplanes];
      flags |= GCPlaneMask;
    }
  else
# endif /* !HAVE_COCOA */
    {
      gcv.foreground = pixel;
    }

  gcv.line_width = t->thickness;
  gcv.cap_style = CapProjecting;
  gcv.join_style = JoinMiter;

  flags |= (GCLineWidth | GCCapStyle | GCJoinStyle);
  t->gc = XCreateGC (st->dpy, d, flags, &gcv);

# ifdef HAVE_COCOA
  if (st->transparent_p)
    {
      /* give a non-opaque alpha to the color */
      unsigned long pixel = gcv.foreground;
      unsigned long amask = BlackPixelOfScreen (st->xgwa.screen);
      unsigned long a = (0xCCCCCCCC & amask);
      pixel = (pixel & (~amask)) | a;

      jwxyz_XSetAlphaAllowed (st->dpy, t->gc, True);
      XSetForeground (st->dpy, t->gc, pixel);
    }
# endif /* HAVE_COCOA */

  switch (random() % 11) {
  case 0: case 1: case 2: case 3: t->draw = draw_star; break;
  case 4: case 5: case 6: case 7: t->draw = draw_circle; break;
  case 8: t->draw = draw_hlines; break;
  case 9: t->draw = draw_vlines; break;
  case 10: t->draw = draw_corners; break;
  default: abort(); break;
  }

  if (t->draw == draw_circle) 
    t->max_size *= 1.5;

  if (random() % 4)
    t->size = t->max_size;
  else
    t->size = t->thickness, t->speed = -t->speed;

  return t;
}