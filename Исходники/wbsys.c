void unlck(LCK *lk)
{
#ifdef _MSC_VER
  if (0==_InterlockedExchange(&lk->FLG, 0))
    dprintf((diagout,">>>>ERROR<<<< unlcking unlck %d\n",lk->NAME));
#else
# ifdef unix
  pthread_mutex_unlock(&lk->FLG);
# else
  if (lk->FLG) lk->FLG=0;
  else dprintf((diagout,">>>>ERROR<<<< unlcking unlck %d\n",lk->NAME));
# endif
#endif
}