/**
 * Process counter data and dispatch values
 */
static int node_handler_fetch_data(void *arg, const char *val, const char *key)
{
    value_t uv;
    double tmp_d;
    uint64_t tmp_u;
    struct values_tmp *vtmp = (struct values_tmp*) arg;
    uint32_t type = DSET_TYPE_UNFOUND;
    int index = vtmp->index;

    char ds_name[DATA_MAX_NAME_LEN];
    memset(ds_name, 0, sizeof(ds_name));

    if(parse_keys(key, ds_name))
    {
        return 1;
    }

    if(index >= vtmp->d->ds_num)
    {
        //don't overflow bounds of array
        index = (vtmp->d->ds_num - 1);
    }

    /**
     * counters should remain in same order we parsed schema... we maintain the
     * index variable to keep track of current point in list of counters. first
     * use index to guess point in array for retrieving type. if that doesn't
     * work, use the old way to get the counter type
     */
    if(strcmp(ds_name, vtmp->d->ds_names[index]) == 0)
    {
        //found match
        type = vtmp->d->ds_types[index];
    }
    else if((index > 0) && (strcmp(ds_name, vtmp->d->ds_names[index-1]) == 0))
    {
        //try previous key
        type = vtmp->d->ds_types[index-1];
    }

    if(type == DSET_TYPE_UNFOUND)
    {
        //couldn't find right type by guessing, check the old way
        type = backup_search_for_type(vtmp->d, ds_name);
    }

    switch(type)
    {
        case DSET_LATENCY:
            if(vtmp->avgcount_exists == -1)
            {
                sscanf(val, "%" PRIu64, &vtmp->avgcount);
                vtmp->avgcount_exists = 0;
                //return after saving avgcount - don't dispatch value
                //until latency calculation
                return 0;
            }
            else
            {
                double sum, result;
                sscanf(val, "%lf", &sum);

                if(vtmp->avgcount == 0)
                {
                    vtmp->avgcount = 1;
                }

                /** User wants latency values as long run avg */
                if(long_run_latency_avg)
                {
                    result = (sum / vtmp->avgcount);
                }
                else
                {
                    result = get_last_avg(vtmp->d, ds_name, vtmp->latency_index, sum, vtmp->avgcount);
                    if(result == -ENOMEM)
                    {
                        return -ENOMEM;
                    }
                }

                uv.gauge = result;
                vtmp->avgcount_exists = -1;
                vtmp->latency_index = (vtmp->latency_index + 1);
            }
            break;
        case DSET_BYTES:
            sscanf(val, "%lf", &tmp_d);
            uv.gauge = tmp_d;
            break;
        case DSET_RATE:
            sscanf(val, "%" PRIu64, &tmp_u);
            uv.derive = tmp_u;
            break;
        case DSET_TYPE_UNFOUND:
        default:
            ERROR("ceph plugin: ds %s was not properly initialized.", ds_name);
            return -1;
    }

    sstrncpy(vtmp->vlist.type, ceph_dset_types[type], sizeof(vtmp->vlist.type));
    sstrncpy(vtmp->vlist.type_instance, ds_name, sizeof(vtmp->vlist.type_instance));
    vtmp->vlist.values = &uv;
    vtmp->vlist.values_len = 1;

    vtmp->index = (vtmp->index + 1);
    plugin_dispatch_values(&vtmp->vlist);

    return 0;
}