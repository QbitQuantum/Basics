static void
sweep (sonar_configuration *sp)
{
  sonar_bogie *b;

  /* Move the sweep forward (clockwise).
   */
  GLfloat prev_sweep, this_sweep, tick;
  GLfloat cycle_secs = 30 / speed;  /* default to one cycle every N seconds */
  this_sweep = ((cycle_secs - fmod (double_time() - sp->start_time +
                                    sp->sweep_offset,
                                    cycle_secs))
                / cycle_secs
                * M_PI * 2);
  prev_sweep = sp->sweep_th;
  tick = prev_sweep - this_sweep;
  while (tick < 0) tick += M_PI*2;

  sp->sweep_th = this_sweep;

  if (this_sweep < 0 || this_sweep >= M_PI*2) abort();
  if (prev_sweep < 0)  /* skip first time */
    return;

  if (tick < 0 || tick >= M_PI*2) abort();


  /* Go through the 'pending' sensor data, find those bogies who are
     just now being swept, and move them from 'pending' to 'displayed'.
     (Leave bogies that have not yet been swept alone: we'll get to
     them when the sweep moves forward.)
   */
  b = sp->pending;
  while (b)
    {
      sonar_bogie *next = b->next;
      if (point_in_wedge (b->th, this_sweep, prev_sweep))
        {
          if (debug_p > 1) {
            time_t t = time((time_t *) 0);
            fprintf (stderr,
                     "%s: sweep hit: %02d:%02d: %s: (%5.2f %5.2f %5.2f;"
                     " th=[%.2f < %.2f <= %.2f])\n", 
                     progname,
                     (int) (t / 60) % 60, (int) t % 60,
                     b->name, b->r, b->th, b->ttl,
                     this_sweep, b->th, prev_sweep);
          }
          b->ttl = M_PI * 2.1;
          copy_and_insert_bogie (sp->ssd, b, &sp->displayed);
          delete_bogie (sp->ssd, b, &sp->pending);
        }
      b = next;
    }


  /* Update TTL on all currently-displayed bogies; delete the dead.

     Request sensor updates on the ones just now being swept.

     Any updates go into 'pending' and might not show up until
     the next time the sweep comes around.  This is to prevent
     already-drawn bogies from jumping to a new position without
     having faded out first.
  */
  b = sp->displayed;
  while (b)
    {
      sonar_bogie *next = b->next;
      b->ttl -= tick;

      if (b->ttl <= 0)
        {
          if (debug_p > 1)
            fprintf (stderr, "%s: TTL expired: %s (%5.2f %5.2f %5.2f)\n",
                     progname, b->name, b->r, b->th, b->ttl);
          delete_bogie (sp->ssd, b, &sp->displayed);
        }
      b = next;
    }

  update_sensor_data (sp);
}