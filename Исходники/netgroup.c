static NET_API_STATUS test_netgroupsetusers(const char *hostname,
					    const char *groupname,
					    uint32_t level,
					    size_t num_entries,
					    const char **names)
{
	NET_API_STATUS status;
	uint8_t *buffer = NULL;
	int i = 0;
	size_t buf_size = 0;

	struct GROUP_USERS_INFO_0 *g0 = NULL;
	struct GROUP_USERS_INFO_1 *g1 = NULL;

	printf("testing NetGroupSetUsers level %d\n", level);

	switch (level) {
		case 0:
			buf_size = sizeof(struct GROUP_USERS_INFO_0) * num_entries;

			status = NetApiBufferAllocate(buf_size, (void **)&g0);
			if (status) {
				goto out;
			}

			for (i=0; i<num_entries; i++) {
				g0[i].grui0_name = names[i];
			}

			buffer = (uint8_t *)g0;
			break;
		case 1:
			buf_size = sizeof(struct GROUP_USERS_INFO_1) * num_entries;

			status = NetApiBufferAllocate(buf_size, (void **)&g1);
			if (status) {
				goto out;
			}

			for (i=0; i<num_entries; i++) {
				g1[i].grui1_name = names[i];
			}

			buffer = (uint8_t *)g1;
			break;
		default:
			break;
	}

	/* NetGroupSetUsers */

	status = NetGroupSetUsers(hostname,
				  groupname,
				  level,
				  buffer,
				  num_entries);
	if (status) {
		goto out;
	}

 out:
	NetApiBufferFree(buffer);
	return status;
}