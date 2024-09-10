int shmctl(int shmid, int cmd, struct shmid_ds *buf)
{
  FAR struct shm_region_s *region;
  int ret;

  DEBUGASSERT(shmid >= 0 && shmid < CONFIG_ARCH_SHM_MAXREGIONS);
  region =  &g_shminfo.si_region[shmid];
  DEBUGASSERT((region->sr_flags & SRFLAG_INUSE) != 0);

  /* Get exclusive access to the region data structure */

  ret = sem_wait(&region->sr_sem);
  if (ret < 0)
    {
      shmerr("ERROR: sem_wait failed: %d\n", ret);
      return ret;
    }

  /* Handle the request according to the received cmd */

  switch (cmd)
    {
      case IPC_STAT:
        {
          /* Place the current value of each member of the shmid_ds data
           * structure associated with shmid into the structure pointed to
           * by buf.
           */

          DEBUGASSERT(buf);
          memcpy(buf, &region->sr_ds, sizeof(struct shmid_ds));
        }
        break;

      case IPC_SET:
        {
          /* Set the value of the shm_perm.mode member of the shmid_ds
           * data structure associated with shmid to the corresponding
           * value found in the structure pointed to by buf.
           */

          region->sr_ds.shm_perm.mode = buf->shm_perm.mode;
        }
        break;

      case IPC_RMID:
        {
          /* Are any processes attached to the region? */

          if (region->sr_ds.shm_nattch > 0)
            {
              /* Yes.. just set the UNLINKED flag.  The region will be removed when there are no longer any processes attached to it.
               */

               region->sr_flags |= SRFLAG_UNLINKED;
            }
          else
            {
              /* No.. free the entry now */

              shm_destroy(shmid);

              /* Don't try anything further on the deleted region */

              return OK;
            }
        }
        break;

      default:
        shmerr("ERROR: Unrecognized command: %d\n", cmd);
        ret = -EINVAL;
        goto errout_with_semaphore;
    }

  /* Save the process ID of the the last operation */

  region = &g_shminfo.si_region[shmid];
  region->sr_ds.shm_lpid = getpid();

  /* Save the time of the last shmctl() */

  region->sr_ds.shm_ctime = time(NULL);

  /* Release our lock on the entry */

  sem_post(&region->sr_sem);
  return ret;

errout_with_semaphore:
  sem_post(&region->sr_sem);
  set_errno(-ret);
  return ERROR;
}