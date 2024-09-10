realm_params_t* get_realm(char* name)
{
	if(name && name[0]) {
		lock_realms();
		ur_string_map_value_type value = 0;
		ur_string_map_key_type key = (ur_string_map_key_type)name;
		if (ur_string_map_get(realms, key, &value)) {
			unlock_realms();
			return (realm_params_t*)value;
		} else {
			realm_params_t *ret = (realm_params_t*)turn_malloc(sizeof(realm_params_t));
			ns_bcopy(default_realm_params_ptr,ret,sizeof(realm_params_t));
			STRCPY(ret->options.name,name);
			value = (ur_string_map_value_type)ret;
			ur_string_map_put(realms, key, value);
			ret->status.alloc_counters =  ur_string_map_create(NULL);
			add_to_secrets_list(&realms_list, name);
			unlock_realms();
			return ret;
		}
	}

	return default_realm_params_ptr;
}