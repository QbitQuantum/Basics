void DCU_initialize()
{
	if (DCU_STATE(DCU_INITIALIZED))
	{
		return;
	}

	if (DCU_STATE(DCU_MUTEX_INITED))
	{
		DCU_MutexScopedLock lock(DCU_mutex);
		if (DCU_STATE(DCU_INITIALIZED))
		{
			return;
		}
		else
		{
			fprintf(DCU_FALLBACK_STREAM, "DynamicCheckUp Concurrency error.\n");
			_exit(1);
		}
	}

	if (pthread_mutex_init(&DCU_mutex, 0) < 0)
	{
		fprintf(DCU_FALLBACK_STREAM, "DynamicCheckUp unable to initialize mutex\n");
		_exit(1);
	}
	else
	{
		DCU_SET_FLAG(DCU_MUTEX_INITED);
	}


	{
		DCU_MutexScopedLock lock(DCU_mutex);

		memory_space = create_mspace(0, 0);
		DCU_SET_FLAG(DCU_INITIALIZED);

		//
		// init backtrace so it wont recursively call malloc
		//
		DCU_Pointer stack[DCU_STACK_TRACE_SIZE];
		backtrace(stack, DCU_STACK_TRACE_SIZE);

		//
		// Init Tracing data
		//

		DCU_stream = DCU_FALLBACK_STREAM;
		memset(DCU_memory_stats, 0, sizeof(DCU_MemoryStats) * DCU_DYNAMIC_OPERATION_TYPES);
		memset(&DCU_memory_stats_new, 0, sizeof(DCU_MemoryStats));
		memset(&DCU_memory_stats_new_array, 0, sizeof(DCU_MemoryStats));
		memset(&DCU_memory_stats_c, 0, sizeof(DCU_MemoryStats));
		memset(DCU_null_stack, 0, sizeof(DCU_null_stack));

		//
		// Operations HashTable
		//
		DCU_memory = (DCU_OperationInfo**) DCU_malloc( DCU_HASH_TABLE_SIZE * sizeof(DCU_OperationInfo*) );
		memset(DCU_memory, 0, DCU_HASH_TABLE_SIZE * sizeof(DCU_OperationInfo*));

		//
		// Problems Linked-List
		//
		DCU_problems = 0;

		//
		// Open Log File
		//
		DCU_stream = fopen(DCU_OUTPUT_FILE, "w");
		if (DCU_stream < 0)
		{
			fprintf(DCU_FALLBACK_STREAM, "DynamicCheckUp: Unable to open %s: %m\n", DCU_OUTPUT_FILE);
			DCU_stream = DCU_FALLBACK_STREAM;
		}
		else
		{
			int flags = fcntl(fileno(DCU_stream), F_GETFD, 0);
			if (flags >= 0)
			{
				flags |= FD_CLOEXEC;
				fcntl(fileno(DCU_stream), F_SETFD, flags);
			}

			setvbuf(DCU_stream, stream_trace_buffer, _IOFBF, DCU_STREAM_BUFFER_SIZE);
		}

		DCU_SET_FLAG(DCU_TRACING);
	}

	DCU_write("DynamicCheckUp Started\n");
}