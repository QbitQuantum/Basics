/** 
 * parse a value into a suitable metadata or sysmd
 * 
 * @param key 
 * @param val 
 * @param metadatum_func
 * @param cb_arg
 * @param metadata 
 * @param sysmdp 
 * 
 * @return 
 */
dpl_status_t
dpl_cdmi_get_metadatum_from_value(const char *key,
                                  dpl_value_t *val,
                                  dpl_metadatum_func_t metadatum_func,
                                  void *cb_arg,
                                  dpl_dict_t *metadata,
                                  dpl_sysmd_t *sysmdp)
{
  dpl_status_t ret, ret2;
  dpl_dict_var_t *var;
  dpl_cdmi_object_id_t obj_id;

  DPRINTF("key=%s val.type=%d\n", key, val->type);

  if (sysmdp)
    {
      if (!strcmp(key, "objectID"))
        {
          if (DPL_VALUE_STRING != val->type)
            {
              ret = DPL_EINVAL;
              goto end;
            }
          
          ret2 = dpl_cdmi_string_to_object_id(dpl_sbuf_get_str(val->string),
                                              &obj_id);
          if (DPL_SUCCESS != ret2)
            {
              ret = ret2;
              goto end;
            }
          
          ret2 = dpl_cdmi_opaque_to_string(&obj_id, sysmdp->id);
          if (DPL_SUCCESS != ret2)
            {
              ret = ret2;
              goto end;
            }
          
          sysmdp->mask |= DPL_SYSMD_MASK_ID;
          
          sysmdp->enterprise_number = obj_id.enterprise_number;
          sysmdp->mask |= DPL_SYSMD_MASK_ENTERPRISE_NUMBER;
        }
      else if (!strcmp(key, "parentID"))
        {
          if (DPL_VALUE_STRING != val->type)
            {
              ret = DPL_EINVAL;
              goto end;
            }

          if (strcmp(dpl_sbuf_get_str(val->string), ""))
            {
              ret2 = dpl_cdmi_string_to_object_id(dpl_sbuf_get_str(val->string), &obj_id);
              if (DPL_SUCCESS != ret2)
                {
                  ret = ret2;
                  goto end;
                }
              
              ret2 = dpl_cdmi_opaque_to_string(&obj_id, sysmdp->parent_id);
              if (DPL_SUCCESS != ret2)
                {
                  ret = ret2;
                  goto end;
                }
              
              sysmdp->mask |= DPL_SYSMD_MASK_PARENT_ID;
            }
        }
      else if (!strcmp(key, "objectType"))
        {
          if (DPL_VALUE_STRING != val->type)
            {
              ret = DPL_EINVAL;
              goto end;
            }
          
          sysmdp->mask |= DPL_SYSMD_MASK_FTYPE;
          sysmdp->ftype = dpl_cdmi_content_type_to_ftype(dpl_sbuf_get_str(val->string));
        }
    }

  if (!strcmp(key, "metadata"))
    {
      //this is the metadata object
      if (DPL_VALUE_SUBDICT != val->type)
        {
          ret = DPL_EINVAL;
          goto end;
        }

      if (sysmdp)
        {
          //some sysmds are stored in metadata
          
          var = dpl_dict_get(val->subdict, "cdmi_mtime");
          if (NULL != var)
            {
              if (DPL_VALUE_STRING != var->val->type)
                {
                  ret = DPL_EINVAL;
                  goto end;
                }
              
              sysmdp->mask |= DPL_SYSMD_MASK_MTIME;
              sysmdp->mtime = dpl_iso8601totime(dpl_sbuf_get_str(var->val->string));
            }
          
          var = dpl_dict_get(val->subdict, "cdmi_atime");
          if (NULL != var)
            {
              if (DPL_VALUE_STRING != var->val->type)
                {
                  ret = DPL_EINVAL;
                  goto end;
                }
              
              sysmdp->mask |= DPL_SYSMD_MASK_ATIME;
              sysmdp->atime = dpl_iso8601totime(dpl_sbuf_get_str(var->val->string));
            }
          
          var = dpl_dict_get(val->subdict, "cdmi_size");
          if (NULL != var)
            {
              if (DPL_VALUE_STRING != var->val->type)
                {
                  ret = DPL_EINVAL;
                  goto end;
                }
              
              sysmdp->mask |= DPL_SYSMD_MASK_SIZE;
              sysmdp->size = strtoull(dpl_sbuf_get_str(var->val->string), NULL, 0);
            }
        }

      if (metadata)
        {
          struct metadata_list_arg arg;
          
          arg.metadatum_func = metadatum_func;
          arg.metadata = metadata;
          arg.cb_arg = cb_arg;

          //iterate metadata object
          ret2 = dpl_dict_iterate(val->subdict, cb_metadata_list, &arg);
          if (DPL_SUCCESS != ret2)
            {
              ret = ret2;
              goto end;
            }
        }
    }
  
  ret = DPL_SUCCESS;
  
 end:

  return ret;
}