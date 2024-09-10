void init_test_data(void)

{

  int i;
  time_t now = time(NULL);
  test_ac_data_t *ac;

  /*
   * set up random number generator
   */
  
  STATS_uniform_seed(now);

  Ac_num = 0;
  N_ac = Glob->params.test_aircraft.len;

  Ac_data = (test_ac_data_t *) umalloc (N_ac * sizeof(test_ac_data_t));
  
  ac = Ac_data;
  for (i = 0; i < N_ac; i++, ac++) {

    ac->change_time = 0;
    ac->start_lat = Glob->params.test_aircraft.val[i].start_lat;
    ac->start_lon = Glob->params.test_aircraft.val[i].start_lon;
    ac->lat = ac->start_lat;
    ac->lon = ac->start_lon;
    ac->altitude = Glob->params.test_aircraft.val[i].altitude * 0.3048;
    ac->speed = (Glob->params.test_aircraft.val[i].speed * 1.852) / 3600.0;
    ac->callsign = STRdup(Glob->params.test_aircraft.val[i].callsign);
    ac->time_last = now;
    ac->heading = STATS_uniform_gen() * 360.0;
    ac->head_bias = 0.0;

  }

}