memcached_return update_continuum(memcached_st *ptr)
{
  uint32_t index;
  uint32_t host_index;
  uint32_t continuum_index= 0;
  uint32_t value;
  memcached_server_st *list;
  uint32_t pointer_counter= 0;
  uint32_t pointer_per_server= MEMCACHED_POINTS_PER_SERVER;
  uint32_t pointer_per_hash= 1;
  uint64_t total_weight= 0;
  uint32_t is_ketama_weighted= 0;
  uint32_t points_per_server= 0;

  is_ketama_weighted= memcached_behavior_get(ptr, MEMCACHED_BEHAVIOR_KETAMA_WEIGHTED);
  points_per_server= is_ketama_weighted ? MEMCACHED_POINTS_PER_SERVER_KETAMA : MEMCACHED_POINTS_PER_SERVER;

  if (ptr->number_of_hosts > ptr->continuum_count)
  {
    memcached_continuum_item_st *new_ptr;

    if (ptr->call_realloc)
      new_ptr= (memcached_continuum_item_st *)ptr->call_realloc(ptr, ptr->continuum, sizeof(memcached_continuum_item_st) * (ptr->number_of_hosts + MEMCACHED_CONTINUUM_ADDITION) * points_per_server);
    else
      new_ptr= (memcached_continuum_item_st *)realloc(ptr->continuum, sizeof(memcached_continuum_item_st) * (ptr->number_of_hosts + MEMCACHED_CONTINUUM_ADDITION) * points_per_server);

    if (new_ptr == 0)
      return MEMCACHED_MEMORY_ALLOCATION_FAILURE;

    ptr->continuum= new_ptr;
    ptr->continuum_count= ptr->number_of_hosts + MEMCACHED_CONTINUUM_ADDITION;
  }

  list = ptr->hosts;

  if (is_ketama_weighted) 
  {
    for (host_index = 0; host_index < ptr->number_of_hosts; ++host_index) 
    {
      if (list[host_index].weight == 0)
      {
        list[host_index].weight = 1;
      }
      total_weight += list[host_index].weight;
    }
  }

  for (host_index = 0; host_index < ptr->number_of_hosts; ++host_index) 
  {
    if (is_ketama_weighted) 
    {
        float pct = (float)list[host_index].weight / (float)total_weight;
        pointer_per_server= floorf(pct * MEMCACHED_POINTS_PER_SERVER_KETAMA / 4 * (float)(ptr->number_of_hosts) + 0.0000000001) * 4;
        pointer_per_hash= 4;
#ifdef HAVE_DEBUG
        printf("ketama_weighted:%s|%d|%llu|%u\n", 
               list[host_index].hostname, 
               list[host_index].port,  
               (unsigned long long)list[host_index].weight, 
               pointer_per_server);
#endif
    }
    for (index= 1; index <= pointer_per_server / pointer_per_hash; ++index) 
    {
      char sort_host[MEMCACHED_MAX_HOST_SORT_LENGTH]= "";
      size_t sort_host_length;

      if (list[host_index].port == MEMCACHED_DEFAULT_PORT)
      {
        sort_host_length= snprintf(sort_host, MEMCACHED_MAX_HOST_SORT_LENGTH, "%s-%d", 
                                   list[host_index].hostname, index - 1);

      }
      else
      {
        sort_host_length= snprintf(sort_host, MEMCACHED_MAX_HOST_SORT_LENGTH, "%s:%d-%d", 
                                   list[host_index].hostname, list[host_index].port, index - 1);
      }
      WATCHPOINT_ASSERT(sort_host_length);

      if (is_ketama_weighted)
      {
        int i;
        for (i = 0; i < pointer_per_hash; i++)
        {
          value= ketama_server_hash(sort_host, sort_host_length, i);
          ptr->continuum[continuum_index].index= host_index;
          ptr->continuum[continuum_index++].value= value;
        }
      }
      else
      {
        value= generate_hash_value(sort_host, sort_host_length, ptr->hash_continuum);
        ptr->continuum[continuum_index].index= host_index;
        ptr->continuum[continuum_index++].value= value;
      }
    }
    pointer_counter+= pointer_per_server;
  }

  WATCHPOINT_ASSERT(ptr);
  WATCHPOINT_ASSERT(ptr->continuum);
  WATCHPOINT_ASSERT(ptr->number_of_hosts * MEMCACHED_POINTS_PER_SERVER <= MEMCACHED_CONTINUUM_SIZE);
  ptr->continuum_points_counter= pointer_counter;
  qsort(ptr->continuum, ptr->continuum_points_counter, sizeof(memcached_continuum_item_st), continuum_item_cmp);

#ifdef HAVE_DEBUG
  for (index= 0; ptr->number_of_hosts && index < ((ptr->number_of_hosts * MEMCACHED_POINTS_PER_SERVER) - 1); index++) 
  {
    WATCHPOINT_ASSERT(ptr->continuum[index].value <= ptr->continuum[index + 1].value);
  }
#endif

  return MEMCACHED_SUCCESS;
}