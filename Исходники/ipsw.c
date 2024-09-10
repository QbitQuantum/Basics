int ipsw_get_latest_fw(plist_t version_data, const char* product, char** fwurl, unsigned char* sha1buf)
{
	*fwurl = NULL;
	if (sha1buf != NULL) {
		memset(sha1buf, '\0', 20);
	}

	plist_t n1 = plist_dict_get_item(version_data, "MobileDeviceSoftwareVersionsByVersion");
	if (!n1) {
		error("%s: ERROR: Can't find MobileDeviceSoftwareVersionsByVersion dict in version data\n", __func__);
		return -1;
	}

	plist_dict_iter iter = NULL;
	plist_dict_new_iter(n1, &iter);
	if (!iter) {
		error("%s: ERROR: Can't get dict iter\n", __func__);
		return -1;
	}
	char* key = NULL;
	long long unsigned int major = 0;
	plist_t val = NULL;
	do {
		plist_dict_next_item(n1, iter, &key, &val);
		if (key) {
			plist_t pr = plist_access_path(n1, 3, key, "MobileDeviceSoftwareVersions", product);
			if (pr) {
				long long unsigned int v = strtoull(key, NULL, 10);
				if (v > major)
					major = v;
			}
			free(key);
		}
	} while (val);
	free(iter);

	if (major == 0) {
		error("%s: ERROR: Can't find major version?!\n", __func__);
		return -1;
	}

	char majstr[32]; // should be enough for a uint64_t value
	sprintf(majstr, FMT_qu, (long long unsigned int)major);
	n1 = plist_access_path(version_data, 7, "MobileDeviceSoftwareVersionsByVersion", majstr, "MobileDeviceSoftwareVersions", product, "Unknown", "Universal", "Restore");
	if (!n1) {
		error("%s: ERROR: Can't get Unknown/Universal/Restore node?!\n", __func__);
		return -1;
	}

	plist_t n2 = plist_dict_get_item(n1, "BuildVersion");
	if (!n2 || (plist_get_node_type(n2) != PLIST_STRING)) {
		error("%s: ERROR: Can't get build version node?!\n", __func__);
		return -1;
	}

	char* strval = NULL;
	plist_get_string_val(n2, &strval);

	n1 = plist_access_path(version_data, 5, "MobileDeviceSoftwareVersionsByVersion", majstr, "MobileDeviceSoftwareVersions", product, strval);
	if (!n1) {
		error("%s: ERROR: Can't get MobileDeviceSoftwareVersions/%s node?!\n", __func__, strval);
		free(strval);
		return -1;
	}
	free(strval);

	strval = NULL;
	n2 = plist_dict_get_item(n1, "SameAs");
	if (n2) {
		plist_get_string_val(n2, &strval);
	}
	if (strval) {
		n1 = plist_access_path(version_data, 5, "MobileDeviceSoftwareVersionsByVersion", majstr, "MobileDeviceSoftwareVersions", product, strval);
		free(strval);
		strval = NULL;
		if (!n1 || (plist_dict_get_size(n1) == 0)) {
			error("%s: ERROR: Can't get MobileDeviceSoftwareVersions/%s dict\n", __func__, product);
			return -1;
		}
	}

	n2 = plist_access_path(n1, 2, "Update", "BuildVersion");
	if (n2) {
		strval = NULL;
		plist_get_string_val(n2, &strval);
		if (strval) {
			n1 = plist_access_path(version_data, 5, "MobileDeviceSoftwareVersionsByVersion", majstr, "MobileDeviceSoftwareVersions", product, strval);
			free(strval);
			strval = NULL;
		}
	}

	n2 = plist_access_path(n1, 2, "Restore", "FirmwareURL");
	if (!n2 || (plist_get_node_type(n2) != PLIST_STRING)) {
		error("%s: ERROR: Can't get FirmwareURL node\n", __func__);
		return -1;
	}

	plist_get_string_val(n2, fwurl);

	if (sha1buf != NULL) {
		n2 = plist_access_path(n1, 2, "Restore", "FirmwareSHA1");
		if (n2 && plist_get_node_type(n2) == PLIST_STRING) {
			strval = NULL;
			plist_get_string_val(n2, &strval);
			if (strval) {
				if (strlen(strval) == 40) {
					int i;
					int v;
					for (i = 0; i < 40; i+=2) {
						v = 0;
						sscanf(strval+i, "%02x", &v);
						sha1buf[i/2] = (unsigned char)v;
					}
				}
				free(strval);
			}
		}
	}

	return 0;
}