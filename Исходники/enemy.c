void get_closest_player(enemy *e){
  int i, d2, d2min;

  e->closest = NULL;

  d2min = MAX_X * MAX_X;

  for (i = 0; i < MAX_PLAYERS; i++)
    if (players[i] && (d2 = distance_squared(e, players[i]) ) < d2min){
      d2min = d2;
      e->closest = players[i];
    }
}