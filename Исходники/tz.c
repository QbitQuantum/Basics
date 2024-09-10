/** Save the current timezone (The TZ environment variable) and set a new one.
 * \param newzone The new timezone.
 */
void
save_and_set_tz(const char *newzone)
{
  const char *tz;

  if (!newzone)
    newzone = "";

  tz = getenv("TZ");
  if (tz)
    saved_tz = mush_strdup(tz, "timezone");
  else
    saved_tz = NULL;

#ifdef WIN32
  _putenv_s("TZ", newzone);
#else
  setenv("TZ", newzone, 1);
#endif

  tzset();
}