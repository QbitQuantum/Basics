static void
compiz_damage(void)
{
   CompDisplay *d;
   CompScreen *s;
   CompWindow *w;
   Eina_Bool thaw = EINA_FALSE;

   for (d = core.displays; d; d = d->next)
     for (s = d->screens; s; s = s->next)
       {
          if (!s->damageMask)
            for (w = s->windows; w; w = w->next)
              {
                 E_Client *ec;

                 ec = compiz_win_to_client(w);
                 if (w->grabbed && ((!ec->moving) && (!e_client_util_resizing_get(ec))))
                   w->screen->windowUngrabNotify(w);
                 if ((w->attrib.x == ec->client.x) && (w->attrib.y == ec->client.y))
                   continue;
                 moveWindow(w, ec->client.x - w->attrib.x, ec->client.y - w->attrib.y, TRUE, TRUE);
                 syncWindowPosition(w);
                 compiz_texture_clear(w->texture);
              }
          if (s->damageMask)
            {
               evas_damage_rectangle_add(e_comp->evas, 0, 0, 1, 1);
               thaw = EINA_TRUE;
            }
       }
   if (eina_array_count(events) || thaw)
     ecore_animator_thaw(compiz_anim);
   else
     ecore_animator_freeze(compiz_anim);
}