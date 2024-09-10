GCC_INLINE int fc_solve_check_and_add_state(
    fc_solve_soft_thread_t * soft_thread,
    fcs_state_extra_info_t * new_state_val,
    fcs_state_extra_info_t * * existing_state_val
    )
{
#if (FCS_STATE_STORAGE == FCS_STATE_STORAGE_INTERNAL_HASH)
#ifdef FCS_ENABLE_SECONDARY_HASH_VALUE
    SFO_hash_value_t hash_value_int;
#endif
#endif
#if (FCS_STATE_STORAGE == FCS_STATE_STORAGE_INDIRECT)
    fcs_standalone_state_ptrs_t * pos_ptr;
    int found;
#endif
    fc_solve_hard_thread_t * hard_thread = soft_thread->hard_thread;
    fc_solve_instance_t * instance = hard_thread->instance;
    fcs_state_t * new_state_key = new_state_val->key;

    int is_state_new;

    if (check_if_limits_exceeded())
    {
        return FCS_STATE_BEGIN_SUSPEND_PROCESS;
    }

    if ((instance->max_depth >= 0) &&
        (new_state_val->depth >= instance->max_depth))
    {
        return FCS_STATE_EXCEEDS_MAX_DEPTH;
    }


    fc_solve_cache_stacks(hard_thread, new_state_key, new_state_val);

    fc_solve_canonize_state(new_state_val,
            INSTANCE_FREECELLS_NUM,
            INSTANCE_STACKS_NUM
            );

/*
    The objective of this part of the code is:
    1. To check if new_state_key / new_state_val is already in the prev_states
       collection.
    2. If not, to add it and to set check to true.
    3. If so, to set check to false.
  */

#if (FCS_STATE_STORAGE == FCS_STATE_STORAGE_INTERNAL_HASH)
#ifdef FCS_ENABLE_SECONDARY_HASH_VALUE
    {
        const char * s_ptr = (char*)new_state_key;
        const char * s_end = s_ptr+sizeof(*new_state_key);
        hash_value_int = 0;
        while (s_ptr < s_end)
        {
            hash_value_int += (hash_value_int << 5) + *(s_ptr++);
        }
        hash_value_int += (hash_value_int>>5);
    }
    if (hash_value_int < 0)
    {
        /*
         * This is a bit mask that nullifies the sign bit of the
         * number so it will always be positive
         * */
        hash_value_int &= (~(1<<((sizeof(hash_value_int)<<3)-1)));
    }
#endif
    {
        void * existing_key_void, * existing_val_void;
    is_state_new = (fc_solve_hash_insert(
        &(instance->hash),
        new_state_key,
        new_state_val,
        &existing_key_void,
        &existing_val_void,
        perl_hash_function(
            (ub1 *)new_state_key,
            sizeof(*new_state_key)
            )
#ifdef FCS_ENABLE_SECONDARY_HASH_VALUE
        , hash_value_int
#endif
        ) == 0);
        if (! is_state_new)
        {
            *existing_state_val = existing_val_void;
        }
    }
#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_GOOGLE_DENSE_HASH)
    {
        void * existing_key_void, * existing_val_void;

        is_state_new = (fc_solve_states_google_hash_insert(
            instance->hash,
            new_state_key,
            new_state_val,
            &existing_key_void,
            &existing_val_void
            ) == 0);

        if (! is_state_new)
        {
            *existing_state_val = existing_val_void;
        }
    }
#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_INDIRECT)
    /* Try to see if the state is found in indirect_prev_states */
    if ((pos_ptr = (fcs_standalone_state_ptrs_t *)bsearch(&new_state_key,
                instance->indirect_prev_states,
                instance->num_indirect_prev_states,
                sizeof(instance->indirect_prev_states[0]),
                fc_solve_state_compare_indirect)) == NULL)
    {
        /* It isn't in prev_states, but maybe it's in the sort margin */
        pos_ptr = (fcs_standalone_state_ptrs_t *)fc_solve_bsearch(
            &new_state_key,
            instance->indirect_prev_states_margin,
            instance->num_prev_states_margin,
            sizeof(instance->indirect_prev_states_margin[0]),
            fc_solve_state_compare_indirect_with_context,
            NULL,
            &found);

        if (found)
        {
            is_state_new = 0;
            *existing_state_val = pos_ptr->val;
        }
        else
        {
            /* Insert the state into its corresponding place in the sort
             * margin */
            memmove((void*)(pos_ptr+1),
                    (void*)pos_ptr,
                    sizeof(*pos_ptr) *
                    (instance->num_prev_states_margin-
                      (pos_ptr-instance->indirect_prev_states_margin)
                    ));
            pos_ptr->key = new_state_key;
            pos_ptr->val = new_state_val;

            instance->num_prev_states_margin++;

            if (instance->num_prev_states_margin >= PREV_STATES_SORT_MARGIN)
            {
                /* The sort margin is full, let's combine it with the main array */

                instance->indirect_prev_states = 
                    realloc(
                        instance->indirect_prev_states,
                        sizeof(instance->indirect_prev_states[0])
                        * (instance->num_indirect_prev_states
                            + instance->num_prev_states_margin
                        )
                    );

                fc_solve_merge_large_and_small_sorted_arrays(
                    instance->indirect_prev_states,
                    instance->num_indirect_prev_states,
                    instance->indirect_prev_states_margin,
                    instance->num_prev_states_margin,
                    sizeof(instance->indirect_prev_states[0]),
                    fc_solve_state_compare_indirect_with_context,
                    NULL
                );

                instance->num_indirect_prev_states += instance->num_prev_states_margin;

                instance->num_prev_states_margin=0;
            }
            is_state_new = 1;
        }

    }
    else
    {
        *existing_state_val = pos_ptr->val;
        is_state_new = 0;
    }

#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_LIBREDBLACK_TREE)
    *existing_state_val = (fcs_state_extra_info_t *)rbsearch(new_state_val,
            instance->tree
            );
    is_state_new = ((*existing_state_val) == new_state_val);

#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_LIBAVL2_TREE)

    *existing_state_val = (fcs_state_extra_info_t *)
        fcs_libavl2_states_tree_insert(instance->tree, new_state_val);
    is_state_new = ((*existing_state_val) == NULL);

#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_GLIB_TREE)
    *existing_state_val = g_tree_lookup(instance->tree, (gpointer)new_state_key);
    if (*existing_state_val == NULL)
    {
        /* The new state was not found. Let's insert it.
         * The value must be the same as the key, so g_tree_lookup()
         * will return it. */
        g_tree_insert(
            instance->tree,
            (gpointer)new_state_key,
            (gpointer)new_state_val
            );
        is_state_new = 1;
    }
    else
    {
        is_state_new = 0;
    }



#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_GLIB_HASH)
    *existing_state_val = g_hash_table_lookup(instance->hash, 
            (gpointer)new_state_key);
    if (*existing_state_val == NULL)
    {
        /* The new state was not found. Let's insert it.
         * The value must be the same as the key, so g_tree_lookup()
         * will return it. */
        g_hash_table_insert(
            instance->hash,
            (gpointer)new_state_key,
            (gpointer)new_state_val

            );
        is_state_new = 1;
    }
    else
    {
        is_state_new = 0;
    }

#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_DB_FILE)
    {
        DBT key, value;
        key.data = new_state;
        key.size = sizeof(*new_state);
        if (instance->db->get(
            instance->db,
            NULL,
            &key,
            &value,
            0
            ) == 0)
        {
            /* The new state was not found. Let's insert it.
             * The value must be the same as the key, so g_tree_lookup()
             * will return it. */

            value.data = key.data;
            value.size = key.size;
            instance->db->put(
                instance->db,
                NULL,
                &key,
                &value,
                0);
            is_state_new = 1;
        }
        else
        {
            is_state_new = 0;
        }
    }
#elif (FCS_STATE_STORAGE == FCS_STATE_STORAGE_JUDY)
    {
        PWord_t * PValue;

        JHSI(PValue, instance->judy_array, new_state_key, sizeof(*new_state_key));

        /* later_todo : Handle out-of-memory. */
        if (*PValue == 0)
        {
            /* A new state. */
            is_state_new = 1;
            *PValue = (PWord_t)(*existing_state_val = new_state_val);
        }
        else
        {
            /* Already exists. */
            is_state_new = 0;
            *existing_state_val = (fcs_state_extra_info_t *)(*PValue);
        }
    }
#else
#error no define
#endif
    if (is_state_new)
    {
        /* The new state was not found in the cache, and it was already inserted */
        if (new_state_val->parent_val)
        {
            new_state_val->parent_val->num_active_children++;
        }
        instance->num_states_in_collection++;

        if (new_state_val->moves_to_parent != NULL)
        {
            new_state_val->moves_to_parent =
                fc_solve_move_stack_compact_allocate(
                    hard_thread,
                    new_state_val->moves_to_parent
                    );
        }

        return FCS_STATE_DOES_NOT_EXIST;
    }
    else
    {
        return FCS_STATE_ALREADY_EXISTS;
    }
}