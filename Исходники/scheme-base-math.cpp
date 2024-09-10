cons_t* proc_truncate(cons_t* p, environment_t*)
{
  assert_length(p, 1);
  assert_number(car(p));

  if ( integerp(car(p)) )
    return integer(car(p)->number.integer);
  else
    return real(truncf(car(p)->number.real));
}