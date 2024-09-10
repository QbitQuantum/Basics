int
main (int argc, char *argv[])
{
  int table_bytes;
  int lock_bytes;
  int i;

  srand ( getpid ()  + getuid () );

  start_pes (0);
  me = _my_pe ();
  npes = _num_pes ();

  /*
   * size of the per-PE partition
   */
  ip_pe = table_size / npes;

  /*
   * each PE only stores what it owns
   */
  table_bytes = sizeof (*table) * ip_pe;
  table = shmalloc (table_bytes);             /* !!! unchecked !!! */
  /*
   * initialize table
   */
  for (i = 0; i < ip_pe; i+= 1)
    {
      table[i] = 0;
    }

  /*
   * each PE needs to be able to lock everywhere
   */
  lock_bytes = sizeof (*lock) * table_size;
  lock = shmalloc (lock_bytes);            	/* !!! unchecked !!! */
  /*
   * initialize locks
   */
  for (i = 0; i < table_size; i+= 1)
    {
      lock[i] = 0L;
    }

  /*
   * make sure all PEs have initialized symmetric data
   */
  shmem_barrier_all ();

  for (i = 0; i < 4; i += 1)
    {
      const int updater = rand () % npes;

      if (me == updater)
        {
          const int i2u = rand () % table_size;
          const int nv = rand () % 100;

          printf ("PE %d: About to update index %d with %d...\n",
                  me, i2u, nv
                 );

          table_update (nv, i2u);
        }
    }

  shmem_barrier_all ();

  /*
   * everyone shows their part of the table
   */
  table_dump ();

  /*
   * clean up allocated memory
   */
  shmem_barrier_all ();
  shfree (lock);
  shfree (table);

  return 0;
}