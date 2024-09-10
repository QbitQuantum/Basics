pse_op_error_t sqlite_read_db(uint32_t leaf_id, pse_vmc_hash_tree_cache_t* cache)
{
    PROFILE_START("sqlite_read_db");
   
    int            rc;
    pse_op_error_t ret = OP_SUCCESS;
    sqlite3_stmt*  stat = NULL;
    char           sql_sentence[1024] = {0};
    int            result;
    uint32_t       node_id;
    const void*    ptr_blob_content;
    uint32_t       blob_len;
    uint32_t       record_count = 0;
    uint32_t       read_list_array[INIT_TOTAL_NODE_NUMBER_FOR_READING] = {0};
    sqlite3        *db = NULL;
    uint8_t*       node_ptr = NULL;
    uint32_t       child_node_id = leaf_id;
    uint32_t       internal_index = 0;
    uint32_t       count = 0;

    if( !cache)
    {
        PROFILE_END("sqlite_read_db");
        return OP_ERROR_INVALID_PARAMETER;
    }

    if(leaf_id < INIT_MIN_LEAF_NODE_ID || leaf_id > INIT_MAX_LEAF_NODE_ID)
    {
        PROFILE_END("sqlite_read_db");
        return OP_ERROR_INVALID_PARAMETER;
    }

    ret = sqlite_open_db(&db);
    if(OP_SUCCESS != ret) 
    {
        pse_vmc_db_state = PSE_VMC_DB_STATE_DOWN;
        PROFILE_END("sqlite_read_db");
        return ret;
    }

    // layout of read_list_array is : Leaf Node ID + ancestor Node IDs + Brother Node IDs.
    find_all_related_node_index(leaf_id, read_list_array);

    // prepare sql statement
    if (_snprintf_s(sql_sentence, sizeof(sql_sentence), "select * from HASH_TREE_NODE_TABLE where ID IN (") < 0)
    {
        ret = OP_ERROR_INTERNAL;
        goto clean_up;
    }
    
    for(uint32_t index=0; index < INIT_TOTAL_NODE_NUMBER_FOR_READING; index++)
    {
        char id[10];

        if (_snprintf_s(id, sizeof(id), "%u", read_list_array[index]) < 0) 
        {
            ret = OP_ERROR_INTERNAL;
            goto clean_up;
        }

        if (strncat_s(sql_sentence, sizeof(sql_sentence), id, strnlen_s(id, 10)) != 0)
        {
            ret = OP_ERROR_INTERNAL;
            goto clean_up;
        }

        if (index != INIT_TOTAL_NODE_NUMBER_FOR_READING - 1)
        {
            if (strncat_s(sql_sentence, sizeof(sql_sentence), ",", 1) != 0)
            {
                ret = OP_ERROR_INTERNAL;
                goto clean_up;
            }
        }
    }
    if (strcat_s(sql_sentence, sizeof(sql_sentence), ") order by ID desc") != 0)
    {
        ret = OP_ERROR_INTERNAL;
        goto clean_up;
    }

    // prepare sql statement
    rc = sqlite3_prepare_v2(db, sql_sentence, -1, &stat, 0);
    EXIT_IFNOT_SQLITE_OK(rc, clean_up)

    // query
    // the result set are sorted, from leaf to up layers
    while ((result = sqlite3_step(stat)) == SQLITE_ROW)
    {
        // to calculate number of records returned 
        record_count++;

        node_id = sqlite3_column_int(stat, 0);
        ptr_blob_content = sqlite3_column_blob(stat, 1);
        if(!ptr_blob_content)
        {
            ret = OP_ERROR_INVALID_VMC_DB;
            goto clean_up;
        }
        blob_len = sqlite3_column_bytes(stat, 1);

        if(1 == node_id)
        {
            assert(0);
            ret = OP_ERROR_INVALID_VMC_DB;
            goto clean_up;
        }
        else if(INIT_MIN_LEAF_NODE_ID <= node_id)
        {
            // node_id has already been checked and 
            // it will not exceed INIT_MAX_LEAF_NODE_ID
            assert(node_id <= INIT_MAX_LEAF_NODE_ID);

            // leaf node
            if(blob_len != LEAF_NODE_SIZE)
            {
                ret = OP_ERROR_INVALID_VMC_DB;
                goto clean_up;
            }

            if (node_id == leaf_id)
            {
                cache->self.node_id = node_id;
                node_ptr = (uint8_t*)&cache->self.leaf;
            }
            else
            {
                cache->brother.node_id = node_id;
                node_ptr = (uint8_t*)&cache->brother.leaf;
            }
        }
        else 
        {
            assert(node_id <= INIT_MAX_LEAF_NODE_ID);

            // internal nodes
            if(blob_len != INTERNAL_NODE_SIZE)
            {
                ret = OP_ERROR_INVALID_VMC_DB;
                goto clean_up;
            }

            if (node_id == child_node_id / 2)
            {
                // this is ancestor node
                node_ptr = (uint8_t*)&cache->ancestors[internal_index].internal;
                cache->ancestors[internal_index].node_id = node_id;
            }
            else 
            {
                // this is brother of ancestors
                node_ptr = (uint8_t*)&cache->brother_of_ancestors[internal_index].internal;
                cache->brother_of_ancestors[internal_index].node_id = node_id;
            }

            count++;
            if (count == 2)
            {
                // internal nodes are arranged as pairs, one is ancestor, another is the brother of the ancestor
                count = 0;
                internal_index++;   // go up a level
                child_node_id = node_id; // now current node becomes child
            }
        }

        // copy blob data to output buffer
        if(0 != memcpy_s(node_ptr, 
                        blob_len, 
                        ptr_blob_content, 
                        blob_len))
        {
            ret = OP_ERROR_INTERNAL;
            goto clean_up;
        }
    }

    if (record_count != INIT_TOTAL_NODE_NUMBER_FOR_READING)
    {
        ret = OP_ERROR_INVALID_VMC_DB;
        goto clean_up;
    }

    if (result != SQLITE_DONE)
    {
        ret = OP_ERROR_SQLITE_INTERNAL;
    }
    
clean_up:
    assert(db != NULL);
    sqlite3_finalize(stat);
    sqlite3_close_v2(db);

    PROFILE_END("sqlite_read_db");
    return ret;
}