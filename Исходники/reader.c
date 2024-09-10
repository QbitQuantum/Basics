static GPtrArray *
read_ip6_addresses (GKeyFile *file,
                    const char *setting_name,
                    const char *key)
{
	GPtrArray *addresses;
	struct in6_addr addr, gw;
	guint32 prefix;
	int i = 0;

	addresses = g_ptr_array_sized_new (3);

	/* Look for individual addresses */
	while (i++ < 1000) {
		char *tmp, *key_name, *str_prefix, *str_gw;
		int ret;
		GValueArray *values;
		GByteArray *address;
		GByteArray *gateway;
		GValue value = { 0 };

		key_name = g_strdup_printf ("%s%d", key, i);
		tmp = g_key_file_get_string (file, setting_name, key_name, NULL);
		g_free (key_name);

		if (!tmp)
			break; /* all done */

		/* convert the string array into IPv6 addresses */
		values = g_value_array_new (2); /* NMIP6Address has 2 items */

		/* Split the address and prefix */
		str_prefix = split_prefix (tmp);

		/* address */
		ret = inet_pton (AF_INET6, tmp, &addr);
		if (ret <= 0) {
			g_warning ("%s: ignoring invalid IPv6 %s element '%s'", __func__, key_name, tmp);
			g_value_array_free (values);
			goto next;
		}

		address = g_byte_array_new ();
		g_byte_array_append (address, (guint8 *) addr.s6_addr, 16);
		g_value_init (&value, DBUS_TYPE_G_UCHAR_ARRAY);
		g_value_take_boxed (&value, address);
		g_value_array_append (values, &value);
		g_value_unset (&value);

		/* prefix */
		prefix = 0;
		if (str_prefix) {
			if (!get_one_int (str_prefix, 128, key_name, &prefix)) {
				g_value_array_free (values);
				goto next;
			}
		} else {
			/* Missing prefix defaults to /64 */
			prefix = 64;
		}

		g_value_init (&value, G_TYPE_UINT);
		g_value_set_uint (&value, prefix);
		g_value_array_append (values, &value);
		g_value_unset (&value);

		/* Gateway (optional) */
		str_gw = split_gw (str_prefix);
		if (str_gw) {
			ret = inet_pton (AF_INET6, str_gw, &gw);
			if (ret <= 0) {
				g_warning ("%s: ignoring invalid IPv6 %s gateway '%s'", __func__, key_name, tmp);
				g_value_array_free (values);
				goto next;
			}

			if (!IN6_IS_ADDR_UNSPECIFIED (&gw)) {
				gateway = g_byte_array_new ();
				g_byte_array_append (gateway, (guint8 *) gw.s6_addr, 16);
				g_value_init (&value, DBUS_TYPE_G_UCHAR_ARRAY);
				g_value_take_boxed (&value, gateway);
				g_value_array_append (values, &value);
				g_value_unset (&value);
			}
		}

		g_ptr_array_add (addresses, values);

next:
		g_free (tmp);
	}

	if (addresses->len < 1) {
		g_ptr_array_free (addresses, TRUE);
		addresses = NULL;
	}

	return addresses;
}