double SDFFsequenceElement::extract_real_t_start(){
  double ts=emanager->get_sample_timestep();
  return round(t_start/ts)*ts; //ceil
};