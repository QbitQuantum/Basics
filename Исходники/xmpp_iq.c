double seconds_since_last_use(void)
{
  return difftime(time(NULL), iqlast);
}