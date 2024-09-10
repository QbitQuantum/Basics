void time_to_string(Time *t,char *out){
  //sprintf("%d:%02d'%02d\"%02d",t->hour,t->min,t->sec,t->ms);
  out[0]  = ITOA(t->hour);
  out[1]  = ':';
  out[2]  = ITOA(t->min/10);
  out[3]  = ITOA(t->min%10);
  out[4]  = '\'';
  out[5]  = ITOA(t->sec/10);
  out[6]  = ITOA(t->sec%10);
  out[7]  = '\"';
  out[8]  = ITOA(t->ms/100);
  out[9]  = ITOA(t->ms%100/10);
}