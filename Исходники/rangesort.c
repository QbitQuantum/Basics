void add_unique_range_nosort(
                            range_list_t *ranges, 
                            GElf_Off start, 
                            GElf_Off length, 
                            void *user,
                            void (*err_fn)(range_error_t, range_t *, range_t *),
                            void (*user_dtor)(void * )) 
{
    if (ranges->num_ranges == ranges->array_length) {
        ranges->array_length += PARALLEL_ARRAY_SIZE;
        ranges->array = REALLOC(ranges->array, 
                                ranges->array_length*sizeof(range_t));
    }
    ranges->array[ranges->num_ranges].start  = start;
    ranges->array[ranges->num_ranges].length = length;
    ranges->array[ranges->num_ranges].user   = user;
    ranges->array[ranges->num_ranges].err_fn = err_fn;
    ranges->array[ranges->num_ranges].user_dtor = user_dtor;
    ranges->num_ranges++;
}