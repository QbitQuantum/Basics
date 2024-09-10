/*
 * alloc_list
 *
 * helper function to allocate a list for scamper_fds_init
 */
static dlist_t *alloc_list(char *name)
{
  dlist_t *list;
  if((list = dlist_alloc()) == NULL)
    printerror(errno, strerror, __func__, "alloc %s failed", name);
  return list;
}