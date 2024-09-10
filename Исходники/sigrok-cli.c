static int set_dev_options(struct sr_dev *dev, GHashTable *args)
{
	GHashTableIter iter;
	gpointer key, value;
	int ret, i;
	float tmp_float;
	uint64_t tmp_u64;
	struct sr_rational tmp_rat;
	gboolean tmp_bool;
	gboolean found;

	g_hash_table_iter_init(&iter, args);
	while (g_hash_table_iter_next(&iter, &key, &value)) {
		found = FALSE;
		for (i = 0; sr_hwcap_options[i].hwcap; i++) {
			if (strcmp(sr_hwcap_options[i].shortname, key))
				continue;
			if ((value == NULL) && 
			    (sr_hwcap_options[i].type != SR_T_BOOL)) {
				g_critical("Option '%s' needs a value.", (char *)key);
				return SR_ERR;
			}
			found = TRUE;
			switch (sr_hwcap_options[i].type) {
			case SR_T_UINT64:
				ret = sr_parse_sizestring(value, &tmp_u64);
				if (ret != SR_OK)
					break;
				ret = dev->driver->dev_config_set(dev->driver_index,
					sr_hwcap_options[i].hwcap, &tmp_u64);
				break;
			case SR_T_CHAR:
				ret = dev->driver->dev_config_set(dev->driver_index,
					sr_hwcap_options[i].hwcap, value);
				break;
			case SR_T_BOOL:
				if (!value)
					tmp_bool = TRUE;
				else 
					tmp_bool = sr_parse_boolstring(value);
				ret = dev->driver->dev_config_set(dev->driver_index,
						sr_hwcap_options[i].hwcap, 
						GINT_TO_POINTER(tmp_bool));
				break;
			case SR_T_FLOAT:
				tmp_float = strtof(value, NULL);
				ret = dev->driver->dev_config_set(dev->driver_index,
						sr_hwcap_options[i].hwcap, &tmp_float);
				break;
			case SR_T_RATIONAL_PERIOD:
				if ((ret = sr_parse_period(value, &tmp_rat)) != SR_OK)
					break;
				ret = dev->driver->dev_config_set(dev->driver_index,
						sr_hwcap_options[i].hwcap, &tmp_rat);
				break;
			case SR_T_RATIONAL_VOLT:
				if ((ret = sr_parse_voltage(value, &tmp_rat)) != SR_OK)
					break;
				ret = dev->driver->dev_config_set(dev->driver_index,
						sr_hwcap_options[i].hwcap, &tmp_rat);
				break;
			default:
				ret = SR_ERR;
			}

			if (ret != SR_OK) {
				g_critical("Failed to set device option '%s'.", (char *)key);
				return ret;
			}
			else
				break;
		}
		if (!found) {
			g_critical("Unknown device option '%s'.", (char *) key);
			return SR_ERR;
		}
	}

	return SR_OK;
}