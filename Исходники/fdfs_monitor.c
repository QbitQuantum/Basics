int main(int argc, char *argv[])
{
	char *conf_filename;
	int result;
	char *op_type;
	char *tracker_server;
	int arg_index;
	char *group_name;

	if (argc < 2)
	{
		usage(argv);
		return 1;
	}

	tracker_server = NULL;
	conf_filename = argv[1];
	arg_index = 2;

	if (arg_index >= argc)
	{
		op_type = "list";
	}
	else
	{
		int len;

		len = strlen(argv[arg_index]); 
		if (len >= 2 && strncmp(argv[arg_index], "-h", 2) == 0)
		{
			if (len == 2)
			{
				arg_index++;
				if (arg_index >= argc)
				{
					usage(argv);
					return 1;
				}

				tracker_server = argv[arg_index++];
			}
			else
			{
				tracker_server = argv[arg_index] + 2;
				arg_index++;
			}

			if (arg_index < argc)
			{
				op_type = argv[arg_index++];
			}
			else
			{
				op_type = "list";
			}
		}
		else
		{
			op_type = argv[arg_index++];
		}
	}

	log_init();
	g_log_context.log_level = LOG_DEBUG;
	ignore_signal_pipe();

	if ((result=fdfs_client_init(conf_filename)) != 0)
	{
		return result;
	}
	load_log_level_ex(conf_filename);

	if (tracker_server == NULL)
	{
		if (g_tracker_group.server_count > 1)
		{
			srand(time(NULL));
			rand();  //discard the first
			g_tracker_group.server_index = (int)( \
				(g_tracker_group.server_count * (double)rand()) \
				/ (double)RAND_MAX);
		}
	}
	else
	{
		int i;
		char ip_addr[IP_ADDRESS_SIZE];

		*ip_addr = '\0';
		if (getIpaddrByName(tracker_server, ip_addr, sizeof(ip_addr)) \
			 == INADDR_NONE)
		{
			printf("resolve ip address of tracker server: %s " \
				"fail!\n", tracker_server);
			return 2;
		}

		for (i=0; i<g_tracker_group.server_count; i++)
		{
			if (strcmp(g_tracker_group.servers[i].ip_addr, \
					ip_addr) == 0)
			{
				g_tracker_group.server_index = i;
				break;
			}
		}

		if (i == g_tracker_group.server_count)
		{
			printf("tracker server: %s not exists!\n", tracker_server);
			return 2;
		}
	}

	printf("server_count=%d, server_index=%d\n", g_tracker_group.server_count, g_tracker_group.server_index);

	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}
	printf("\ntracker server is %s:%d\n\n", pTrackerServer->ip_addr, pTrackerServer->port);

	if (arg_index < argc)
	{
		group_name = argv[arg_index++];
	}
	else
	{
		group_name = NULL;
	}

	if (strcmp(op_type, "list") == 0)
	{
		if (group_name == NULL)
		{
			result = list_all_groups(NULL);
		}
		else
		{
			result = list_all_groups(group_name);
		}
	}
	else if (strcmp(op_type, "delete") == 0)
	{
		char *storage_id;
		if (arg_index >= argc)
		{
			usage(argv);
			return 1;
		}

		storage_id = argv[arg_index++];

		if ((result=tracker_delete_storage(&g_tracker_group, \
				group_name, storage_id)) == 0)
		{
			printf("delete storage server %s::%s success\n", \
				group_name, storage_id);
		}
		else
		{
			printf("delete storage server %s::%s fail, " \
				"error no: %d, error info: %s\n", \
				group_name, storage_id, \
				result, STRERROR(result));
		}
	}
	else if (strcmp(op_type, "set_trunk_server") == 0)
	{
		char *storage_id;
		char new_trunk_server_id[FDFS_STORAGE_ID_MAX_SIZE];

		if (group_name == NULL)
		{
			usage(argv);
			return 1;
		}
		if (arg_index >= argc)
		{
			storage_id = "";
		}
		else
		{
			storage_id = argv[arg_index++];
		}

		if ((result=tracker_set_trunk_server(&g_tracker_group, \
			group_name, storage_id, new_trunk_server_id)) == 0)
		{
			printf("set trunk server %s::%s success, " \
				"new trunk server: %s\n", group_name, \
				storage_id, new_trunk_server_id);
		}
		else
		{
			printf("set trunk server %s::%s fail, " \
				"error no: %d, error info: %s\n", \
				group_name, storage_id, \
				result, STRERROR(result));
		}
	}
	else
	{
		printf("Invalid command %s\n\n", op_type);
		usage(argv);
	}

	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();
	return 0;
}