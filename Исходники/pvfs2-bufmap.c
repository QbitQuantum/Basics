/* pvfs_bufmap_initialize()
 *
 * initializes the mapped buffer interface
 *
 * returns 0 on success, -errno on failure
 */
int pvfs_bufmap_initialize(struct PVFS_dev_map_desc *user_desc)
{
    int ret = -EINVAL;
    int i = 0;
    int offset = 0;

    gossip_debug(GOSSIP_BUFMAP_DEBUG, "pvfs_bufmap_initialize: called "
                 "(ptr (%p) sz (%d) cnt(%d).\n",
                 user_desc->ptr, user_desc->size, user_desc->count);

    down_write(&bufmap_init_sem);
    if (bufmap_init == 1)
    {
        gossip_err("pvfs2: error: bufmap already initialized.\n");
        ret = -EALREADY;
        goto init_failure;
    }

    /* sanity check alignment and size of buffer that caller wants to
     * work with
     */
    if (PAGE_ALIGN((unsigned long)user_desc->ptr) != 
        (unsigned long)user_desc->ptr)
    {
        gossip_err("pvfs2 error: memory alignment (front). %p\n",
                user_desc->ptr);
        goto init_failure;
    }

    if (PAGE_ALIGN(((unsigned long)user_desc->ptr + user_desc->total_size)) != 
        (unsigned long)(user_desc->ptr + user_desc->total_size))
    {
        gossip_err("pvfs2 error: memory alignment (back).(%p + %d)\n",
                user_desc->ptr, user_desc->total_size);
        goto init_failure;
    }

    if (user_desc->total_size != (user_desc->size * user_desc->count))
    {
        gossip_err("pvfs2 error: user provided an oddly "
                    "sized buffer...(%d, %d, %d)\n",
                    user_desc->total_size, user_desc->size, user_desc->count);
        goto init_failure;
    }

    if ((user_desc->size % PAGE_SIZE) != 0)
    {
        gossip_err("pvfs2 error: bufmap size not page size "
                    "divisible (%d).\n", user_desc->size);
        goto init_failure;
    }
    /* Initialize critical variables */
    pvfs2_bufmap_total_size = user_desc->total_size;
    pvfs2_bufmap_desc_count = user_desc->count;
    pvfs2_bufmap_desc_size  = user_desc->size;
    pvfs2_bufmap_desc_shift = LOG2(pvfs2_bufmap_desc_size);
    bufmap_page_count = pvfs2_bufmap_total_size / PAGE_SIZE;
    pages_per_desc    = pvfs2_bufmap_desc_size / PAGE_SIZE;
    /* Initialize descriptor arrays */
    if ((ret = initialize_bufmap_descriptors(pvfs2_bufmap_desc_count)) < 0)
    {
        goto init_failure;
    }

    /* allocate storage to track our page mappings */
    bufmap_page_array = kmalloc(bufmap_page_count * sizeof(*bufmap_page_array), 
                                PVFS2_BUFMAP_GFP_FLAGS);
    if (!bufmap_page_array)
    {
        ret = -ENOMEM;
        goto init_failure;
    }

    /* map the pages */
    down_write(&current->mm->mmap_sem);

    ret = get_user_pages(
        current, current->mm, (unsigned long)user_desc->ptr,
        bufmap_page_count, 1, 0, bufmap_page_array, NULL);

    up_write(&current->mm->mmap_sem);

    if (ret < 0)
    {
        kfree(bufmap_page_array);
        goto init_failure;
    }

    /*
      in theory we could run with what we got, but I will just treat
      it as an error for simplicity's sake right now
    */
    if (ret != bufmap_page_count)
    {
        gossip_err("pvfs2 error: asked for %d pages, only got %d.\n",
                    (int) bufmap_page_count, ret);

        for(i = 0; i < ret; i++)
        {
            SetPageError(bufmap_page_array[i]);
            page_cache_release(bufmap_page_array[i]);
        }
        kfree(bufmap_page_array);
        ret = -ENOMEM;
        goto init_failure;
    }

    /*
      ideally we want to get kernel space pointers for each page, but
      we can't kmap that many pages at once if highmem is being used.
      so instead, we just kmap/kunmap the page address each time the
      kaddr is needed.  this loop used to kmap every page, but now it
      only ensures every page is marked reserved (non-pageable) NOTE:
      setting PageReserved in 2.6.x seems to cause more trouble than
      it's worth.  in 2.4.x, marking the pages does what's expected
      and doesn't try to swap out our pages
    */
    for(i = 0; i < bufmap_page_count; i++)
    {
        flush_dcache_page(bufmap_page_array[i]);
        pvfs2_set_page_reserved(bufmap_page_array[i]);
    }

    /* build a list of available descriptors */
    for(offset = 0, i = 0; i < pvfs2_bufmap_desc_count; i++)
    {
        desc_array[i].page_array = &bufmap_page_array[offset];
        desc_array[i].array_count = pages_per_desc;
        desc_array[i].uaddr =
            (user_desc->ptr + (i * pages_per_desc * PAGE_SIZE));
        offset += pages_per_desc;
    }

    /* clear any previously used buffer indices */
    spin_lock(&buffer_index_lock);
    for(i = 0; i < pvfs2_bufmap_desc_count; i++)
    {
        buffer_index_array[i] = 0;
    }
    spin_unlock(&buffer_index_lock);
    spin_lock(&readdir_index_lock);
    for (i = 0; i < PVFS2_READDIR_DEFAULT_DESC_COUNT; i++)
    {
        readdir_index_array[i] = 0;
    }
    spin_unlock(&readdir_index_lock);

    bufmap_init = 1;
    up_write(&bufmap_init_sem);

    gossip_debug(GOSSIP_BUFMAP_DEBUG, "pvfs_bufmap_initialize: exiting normally\n");
    return 0;

init_failure:
    finalize_bufmap_descriptors();
    up_write(&bufmap_init_sem);
    return ret;
}