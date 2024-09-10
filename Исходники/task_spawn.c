int task_spawn(FAR pid_t *pid, FAR const char *name, main_t entry,
      FAR const posix_spawn_file_actions_t *file_actions,
      FAR const posix_spawnattr_t *attr,
      FAR char *const argv[], FAR char *const envp[])
{
  struct sched_param param;
  pid_t proxy;
#ifdef CONFIG_SCHED_WAITPID
  int status;
#endif
  int ret;

  svdbg("pid=%p name=%s entry=%p file_actions=%p attr=%p argv=%p\n",
        pid, name, entry, file_actions, attr, argv);

  /* If there are no file actions to be performed and there is no change to
   * the signal mask, then start the new child task directly from the parent task.
   */

#ifndef CONFIG_DISABLE_SIGNALS
  if ((file_actions == NULL || *file_actions == NULL) &&
      (attr == NULL || (attr->flags & POSIX_SPAWN_SETSIGMASK) == 0))
#else
  if (file_actions ==  NULL || *file_actions == NULL)
#endif
    {
      return task_spawn_exec(pid, name, entry, attr, argv);
    }

  /* Otherwise, we will have to go through an intermediary/proxy task in order
   * to perform the I/O redirection.  This would be a natural place to fork().
   * However, true fork() behavior requires an MMU and most implementations
   * of vfork() are not capable of these operations.
   *
   * Even without fork(), we can still do the job, but parameter passing is
   * messier.  Unfortunately, there is no (clean) way to pass binary values
   * as a task parameter, so we will use a semaphore-protected global
   * structure.
   */

  /* Get exclusive access to the global parameter structure */

  spawn_semtake(&g_spawn_parmsem);

  /* Populate the parameter structure */

  g_spawn_parms.result       = ENOSYS;
  g_spawn_parms.pid          = pid;
  g_spawn_parms.file_actions = file_actions ? *file_actions : NULL;
  g_spawn_parms.attr         = attr;
  g_spawn_parms.argv         = argv;
  g_spawn_parms.u.task.name  = name;
  g_spawn_parms.u.task.entry = entry;

  /* Get the priority of this (parent) task */

  ret = sched_getparam(0, &param);
  if (ret < 0)
    {
      int errcode = get_errno();

      sdbg("ERROR: sched_getparam failed: %d\n", errcode);
      spawn_semgive(&g_spawn_parmsem);
      return errcode;
    }

  /* Disable pre-emption so that the proxy does not run until waitpid
   * is called.  This is probably unnecessary since the task_spawn_proxy has
   * the same priority as this thread; it should be schedule behind this
   * task in the ready-to-run list.
   */

#ifdef CONFIG_SCHED_WAITPID
  sched_lock();
#endif

  /* Start the intermediary/proxy task at the same priority as the parent
   * task.
   */

  proxy = task_create("task_spawn_proxy", param.sched_priority,
                      CONFIG_POSIX_SPAWN_PROXY_STACKSIZE,
                      (main_t)task_spawn_proxy,
                      (FAR char * const*)NULL);
  if (proxy < 0)
    {
      ret = get_errno();
      sdbg("ERROR: Failed to start task_spawn_proxy: %d\n", ret);

      goto errout_with_lock;
    }

   /* Wait for the proxy to complete its job */

#ifdef CONFIG_SCHED_WAITPID
   ret = waitpid(proxy, &status, 0);
   if (ret < 0)
     {
       sdbg("ERROR: waitpid() failed: %d\n", errno);
       goto errout_with_lock;
     }
#else
   spawn_semtake(&g_spawn_execsem);
#endif

   /* Get the result and relinquish our access to the parameter structure */

   ret = g_spawn_parms.result;

errout_with_lock:
#ifdef CONFIG_SCHED_WAITPID
  sched_unlock();
#endif
  spawn_semgive(&g_spawn_parmsem);
  return ret;
}