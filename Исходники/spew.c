void readcclass(register classrec *cp)
{
  register int n;
  register defn *dp;
  defn **dput;

  char store[MAXDEF]; /* for tags */

  cp->weight = getw(InFile);
  instring(store, MAXDEF);
  cp->tags = (store[0] == '\0') ? NullTags : save(store);
  n = getw(InFile);
  if (n <= 0)
    badfile();
  dput = &(cp->list); /* link on here */
  while (n--) {
    dp = (defn *)my_alloc((unsigned) sizeof(defn));
    *dput = dp;
    dp->cumul = getw(InFile);
    instring(store, MAXDEF);
    dp->string = save(store);
    dput = &(dp->next);
  }
  *dput = NULL; /* last one */
}