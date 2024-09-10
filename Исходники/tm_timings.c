void get_time(){
  clock_num++;

  if(clock_num>MAX_CLOCK-1)
    return;

  

  CLOCK(time_tab[clock_num]);
}