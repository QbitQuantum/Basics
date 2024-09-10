void lockup(void)
/* lock unless locked */
{
  if(!flaglocked) {
    fdlock = lockfile("lock");
    flaglocked = 1;
  }
}