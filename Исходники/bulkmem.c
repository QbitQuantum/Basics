int open_memory(client_handle_t *handle, open_mem_t *open)
{
    socket_info_t *s;
    memory_handle_t region;
    
    if ((handle == NULL) || CHECK_HANDLE(*handle))
	return CS_BAD_HANDLE;
    s = SOCKET(*handle);
    if (open->Attributes & MEMORY_TYPE_AM)
	region = s->a_region;
    else
	region = s->c_region;
    while (region) {
	if (region->info.CardOffset == open->Offset) break;
	region = region->info.next;
    }
#ifdef __BEOS__
    if (region->dev_info[0] != '\0') {
	char n[80];
	struct module_info *m;
	sprintf(n, MTD_MODULE_NAME("%s"), region->dev_info);
	if (get_module(n, &m) != B_OK)
	    dprintf("cs: could not find MTD module %s\n", n);
    }
#endif
    if (region && region->mtd) {
	*handle = (client_handle_t)region;
	DEBUG(1, "cs: open_memory(0x%p, 0x%x) = 0x%p\n",
	      handle, open->Offset, region);
	return CS_SUCCESS;
    } else
	return CS_BAD_OFFSET;
} /* open_memory */