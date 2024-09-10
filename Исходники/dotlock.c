/* Windows specific code of release_dotlock.  */
static int
dotlock_release_w32 (dotlock_t h)
{
  OVERLAPPED ovl;

  memset (&ovl, 0, sizeof ovl);
  if (!UnlockFileEx (h->lockhd, 0, 1, 0, &ovl))
    {
      my_error_2 ("release_dotlock: error removing lockfile `%s': %s\n",
                  h->lockname, w32_strerror (-1));
      return -1;
    }

  return 0;
}