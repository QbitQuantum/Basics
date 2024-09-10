int munmap(FAR void *start, size_t length)
{
  FAR struct fs_rammap_s *prev;
  FAR struct fs_rammap_s *curr;
  FAR void *newaddr;
  unsigned int offset;
  int ret;
  int err;

  /* Find a region containing this start and length in the list of regions */

  rammap_initialize();
  ret = sem_wait(&g_rammaps.exclsem);
  if (ret < 0)
    {
      return ERROR;
    }

  /* Seach the list of regions */

  for (prev = NULL, curr = g_rammaps.head; curr; prev = curr, curr = curr->flink)
    {
      /* Does this region include any part of the specified range? */

      if ((uintptr_t)start < (uintptr_t)curr->addr + curr->length &&
          (uintptr_t)start + length >= (uintptr_t)curr->addr)
        {
          break;
        }
    }

  /* Did we find the region */

  if (!curr)
    {
      fdbg("Region not found\n");
      err = EINVAL;
      goto errout_with_semaphore;
    }

  /* Get the offset from the beginning of the region and the actual number
   * of bytes to "unmap".  All mappings must extend to the end of the region.
   * There is no support for free a block of memory but leaving a block of
   * memory at the end.  This is a consequence of using kumm_realloc() to
   * simulate the unmapping.
   */

  offset = start - curr->addr;
  if (offset + length < curr->length)
    {
      fdbg("Cannot umap without unmapping to the end\n");
      err = ENOSYS;
      goto errout_with_semaphore;
    }

  /* Okay.. the region is beging umapped to the end.  Make sure the length
   * indicates that.
   */

  length = curr->length - offset;

  /* Are we unmapping the entire region (offset == 0)? */

  if (length >= curr->length)
    {
      /* Yes.. remove the mapping from the list */

      if (prev)
        {
          prev->flink = curr->flink;
        }
      else
        {
          g_rammaps.head = curr->flink;
        }

      /* Then free the region */

      kumm_free(curr);
    }

  /* No.. We have been asked to "unmap' only a portion of the memory
   * (offset > 0).
   */

  else
    {
      newaddr = kumm_realloc(curr->addr, sizeof(struct fs_rammap_s) + length);
      DEBUGASSERT(newaddr == (FAR void*)(curr->addr));
      curr->length = length;
    }

  sem_post(&g_rammaps.exclsem);
  return OK;

errout_with_semaphore:
  sem_post(&g_rammaps.exclsem);
  set_errno(err);
  return ERROR;
}