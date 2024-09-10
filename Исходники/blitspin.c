static unsigned long
blitspin_draw (Display *dpy, Window window, void *closure)
{
  struct state *st = (struct state *) closure;
  int this_delay = st->delay;
  int qwad;

  if (st->img_loader)   /* still loading */
    {
      st->img_loader = load_image_async_simple (st->img_loader, 0, 0, 0, 0, 0);

      if (!st->img_loader) { /* just finished */
        st->first_time = 0;
        st->loaded_p = True;
        st->qwad = -1;
        st->start_time = time ((time_t) 0);
        blitspin_init_2 (st);
      }

      /* Rotate nothing if the very first image is not yet loaded */
      if (! st->loaded_p)
        return this_delay;
    }

  if (!st->img_loader &&
      st->load_ext_p &&
      st->start_time + st->duration < time ((time_t) 0)) {
    /* Start a new image loading, but keep rotating the old image 
       until the new one arrives. */
    st->img_loader = load_image_async_simple (0, st->xgwa.screen, st->window,
                                              st->bitmap, 0, 0);
  }

  if (st->qwad == -1) 
    {
      bitblt(st, st->mask, st->mask, clear,0,0, st->size,    st->size,    0,0);
      bitblt(st, st->mask, st->mask, set,  0,0, st->size>>1, st->size>>1, 0,0);
      st->qwad = st->size>>1;
    }