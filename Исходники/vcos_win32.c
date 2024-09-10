VCOS_STATUS_T
vcos_win32_named_semaphore_create(VCOS_NAMED_SEMAPHORE_T *sem, const char *name, VCOS_UNSIGNED count)
{
   char buf[64];
   HANDLE h;
   int ret = vcos_snprintf(buf, sizeof(buf), "Global\\%s", name);
   if (ret < 0)
   {
      vcos_assert(0);
      return VCOS_ENOSPC;
   }

   h = CreateSemaphoreA(NULL, count, 1<<16, buf);
   if (h != NULL)
   {
      sem->sem = h;
      return VCOS_SUCCESS;
   }
   else
      return vcos_win32_map_error();
}