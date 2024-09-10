int
write_mteObjectsEntryStatus(int action,
                            u_char * var_val,
                            u_char var_val_type,
                            size_t var_val_len,
                            u_char * statP, oid * name, size_t name_len)
{
    struct mteObjectsTable_data *StorageTmp = NULL;
    static struct mteObjectsTable_data *StorageNew, *StorageDel;
    size_t          newlen =
        name_len - (sizeof(mteObjectsTable_variables_oid) / sizeof(oid) +
                    3 - 1);
    static int      old_value;
    int             set_value;
    static netsnmp_variable_list *vars, *vp;
    struct header_complex_index *hciptr;


    StorageTmp =
        header_complex(mteObjectsTableStorage, NULL,
                       &name[sizeof(mteObjectsTable_variables_oid) /
                             sizeof(oid) + 3 - 1], &newlen, 1, NULL, NULL);

    if (var_val_type != ASN_INTEGER || var_val == NULL) {
        snmp_log(LOG_ERR,
                 "write to mteObjectsEntryStatus not ASN_INTEGER\n");
        return SNMP_ERR_WRONGTYPE;
    }

    if (StorageTmp && StorageTmp->storagetype == ST_READONLY) {
        return SNMP_ERR_NOTWRITABLE;
    }

    set_value = *((long *) var_val);


    /*
     * check legal range, and notReady is reserved for us, not a user 
     */
    if (set_value < 1 || set_value > 6 || set_value == RS_NOTREADY)
        return SNMP_ERR_INCONSISTENTVALUE;


    switch (action) {
    case RESERVE1:
        /*
         * stage one: test validity 
         */
        if (StorageTmp == NULL) {
            /*
             * create the row now? 
             */


            /*
             * ditch illegal values now 
             */
            if (set_value == RS_ACTIVE || set_value == RS_NOTINSERVICE)
                return SNMP_ERR_INCONSISTENTVALUE;


            /*
             * destroying a non-existent row is actually legal 
             */
            if (set_value == RS_DESTROY) {
                return SNMP_ERR_NOERROR;
            }


            /*
             * illegal creation values 
             */
            if (set_value == RS_ACTIVE || set_value == RS_NOTINSERVICE) {
                return SNMP_ERR_INCONSISTENTVALUE;
            }
        } else {
            /*
             * row exists.  Check for a valid state change 
             */
            if (set_value == RS_CREATEANDGO
                || set_value == RS_CREATEANDWAIT) {
                /*
                 * can't create a row that exists 
                 */
                return SNMP_ERR_INCONSISTENTVALUE;
            }
            /*
             * XXX: interaction with row storage type needed 
             */
        }
        break;




    case RESERVE2:
        /*
         * memory reseveration, final preparation... 
         */
        if (StorageTmp == NULL) {
            /*
             * creation 
             */
            vars = NULL;


            snmp_varlist_add_variable(&vars, NULL, 0, ASN_OCTET_STR, NULL, 0);  /* mteOwner */
            snmp_varlist_add_variable(&vars, NULL, 0, ASN_OCTET_STR, NULL, 0);  /* mteObjectsName */
            snmp_varlist_add_variable(&vars, NULL, 0, ASN_UNSIGNED, NULL, 0);   /* mteObjectsIndex */

            if (header_complex_parse_oid
                (&
                 (name
                  [sizeof(mteObjectsTable_variables_oid) / sizeof(oid) +
                   2]), newlen, vars) != SNMPERR_SUCCESS) {
                /*
                 * XXX: free, zero vars 
                 */
                return SNMP_ERR_INCONSISTENTNAME;
            }
            vp = vars;


            StorageNew = SNMP_MALLOC_STRUCT(mteObjectsTable_data);
            if (StorageNew == NULL)
                return SNMP_ERR_GENERR;
            StorageNew->mteOwner = netsnmp_strdup_and_null(vp->val.string,
                                                           vp->val_len);
            StorageNew->mteOwnerLen = vp->val_len;
            vp = vp->next_variable;
            StorageNew->mteObjectsName  =
                netsnmp_strdup_and_null(vp->val.string,
                                        vp->val_len);
            StorageNew->mteObjectsNameLen = vp->val_len;
            vp = vp->next_variable;
            StorageNew->mteObjectsIndex = *(vp->val.integer);

            /*
             * XXX: fill in default row values here into StorageNew 
             */
            StorageNew->mteObjectsID = calloc(1, sizeof(oid) * sizeof(2));      /* 0.0 */
            StorageNew->mteObjectsIDLen = 2;
            StorageNew->mteObjectsIDWildcard = MTEOBJECTSIDWILDCARD_FALSE;

            StorageNew->mteObjectsEntryStatus = set_value;
            /*
             * XXX: free, zero vars, no longer needed? 
             */
        }


        break;




    case FREE:
        /*
         * XXX: free, zero vars 
         */
        /*
         * Release any resources that have been allocated 
         */
        break;




    case ACTION:
        /*
         * The variable has been stored in set_value for you to
         * use, and you have just been asked to do something with
         * it.  Note that anything done here must be reversable in
         * the UNDO case 
         */


        if (StorageTmp == NULL) {
            /*
             * row creation, so add it 
             */
            if (StorageNew != NULL)
                mteObjectsTable_add(StorageNew);
            /*
             * XXX: ack, and if it is NULL? 
             */
        } else if (set_value != RS_DESTROY) {
            /*
             * set the flag? 
             */
            old_value = StorageTmp->mteObjectsEntryStatus;
            StorageTmp->mteObjectsEntryStatus = *((long *) var_val);
        } else {
            /*
             * destroy...  extract it for now 
             */
            hciptr =
                header_complex_find_entry(mteObjectsTableStorage,
                                          StorageTmp);
            StorageDel =
                header_complex_extract_entry(&mteObjectsTableStorage,
                                             hciptr);
        }
        break;




    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        if (StorageTmp == NULL) {
            /*
             * row creation, so remove it again 
             */
            hciptr =
                header_complex_find_entry(mteObjectsTableStorage,
                                          StorageTmp);
            StorageDel =
                header_complex_extract_entry(&mteObjectsTableStorage,
                                             hciptr);
            /*
             * XXX: free it 
             */
        } else if (StorageDel != NULL) {
            /*
             * row deletion, so add it again 
             */
            mteObjectsTable_add(StorageDel);
        } else {
            StorageTmp->mteObjectsEntryStatus = old_value;
        }
        break;




    case COMMIT:
        /*
         * Things are working well, so it's now safe to make the change
         * permanently.  Make sure that anything done here can't fail! 
         */
        if (StorageDel != NULL) {
            StorageDel = 0;
            /*
             * XXX: free it, its dead 
             */
        } else {
            if (StorageTmp
                && StorageTmp->mteObjectsEntryStatus == RS_CREATEANDGO) {
                StorageTmp->mteObjectsEntryStatus = RS_ACTIVE;
            } else if (StorageTmp &&
                       StorageTmp->mteObjectsEntryStatus ==
                       RS_CREATEANDWAIT) {
                StorageTmp->mteObjectsEntryStatus = RS_NOTINSERVICE;
            }
        }
        break;
    }
    return SNMP_ERR_NOERROR;
}