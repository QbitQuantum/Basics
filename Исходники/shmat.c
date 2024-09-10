FAR void *shmat(int shmid, FAR const void *shmaddr, int shmflg)
{
  FAR struct shm_region_s *region;
  FAR struct task_group_s *group;
  FAR struct tcb_s *tcb;
  uintptr_t vaddr;
  unsigned int npages;
  int ret;

  /* Get the region associated with the shmid */

  DEBUGASSERT(shmid >= 0 && shmid < CONFIG_ARCH_SHM_MAXREGIONS);
  region =  &g_shminfo.si_region[shmid];
  DEBUGASSERT((region->sr_flags & SRFLAG_INUSE) != 0);

  /* Get the TCB and group containing our virtual memory allocator */

  tcb = sched_self();
  DEBUGASSERT(tcb && tcb->group);
  group = tcb->group;
  DEBUGASSERT(group->tg_shm.gs_handle != NULL &&
              group->tg_shm.gs_vaddr[shmid] == 0);

  /* Get exclusive access to the region data structure */

  ret = sem_wait(&region->sr_sem);
  if (ret < 0)
    {
      shmdbg("sem_wait failed: %d\n", ret);
      goto errout;
    }

  /* Set aside a virtual address space to span this physical region */

  vaddr = (uintptr_t)gran_alloc(group->tg_shm.gs_handle,
                                region->sr_ds.shm_segsz);
  if (vaddr == 0)
    {
      shmdbg("gran_alloc() failed\n");
      ret = -ENOMEM;
      goto errout_with_semaphore;
    }

  /* Convert the region size to pages */

  npages = MM_PGALIGNUP(region->sr_ds.shm_segsz);

  /* Attach, i.e, map, on shared memory region to the user virtual address. */

  ret = up_shmat(region->sr_pages, npages, vaddr);
  if (ret < 0)
    {
      shmdbg("up_shmat() failed\n");
      goto errout_with_vaddr;
    }

  /* Save the virtual address of the region.  We will need that in shmat()
   * to do the reverse lookup:  Give the virtual address of the region to
   * detach, we need to get the region table index.
   */

  group->tg_shm.gs_vaddr[shmid] = vaddr;

  /* Increment the count of processes attached to this region */

  region->sr_ds.shm_nattch++;

  /* Save the process ID of the the last operation */

  region->sr_ds.shm_lpid = tcb->pid;

  /* Save the time of the last shmat() */

  region->sr_ds.shm_atime = time(NULL);

  /* Release our lock on the entry */

  sem_post(&region->sr_sem);
  return (FAR void *)vaddr;

errout_with_vaddr:
  gran_free(group->tg_shm.gs_handle, (FAR void *)vaddr,
            region->sr_ds.shm_segsz);
errout_with_semaphore:
  sem_post(&region->sr_sem);
  set_errno(-ret);
errout:
  return (FAR void *)ERROR;
}