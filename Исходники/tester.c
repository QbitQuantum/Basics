int main(int argc, char *argv[])
{
#ifndef PRT_PLAT_WINUSER
    init_ros("test_motion_planner", &argc, argv);
#endif
    if (!ParseCommandLine(argc, argv))
    {
        PrintUsage();
        return 1;
    }

    const char* motion_planner_delta_s = getenv("MOTION_PLANNER_DELTA");
    if(motion_planner_delta_s) {
        Delta = atoi(motion_planner_delta_s);
        printf("Using MOTION_PLANNER_DELTA = %d\n", Delta);
    }

    printf("Press any key to start simulation\n");
    getchar();

	PRT_DBG_START_MEM_BALANCED_REGION
	{
		PRT_PROCESS *process;
		PRT_GUID processGuid;
		PRT_VALUE *payload;

		//Initialize the workspace
		WORKSPACE_INFO = ParseWorkspaceConfig(workspaceConfig);

#ifdef USE_DIJKSTRA_PRECOMPUTATION
        WS_LocationsList ends;
        ends.size = WORKSPACE_INFO->starts.size + WORKSPACE_INFO->ends.size;
        ends.locations = malloc(sizeof(WS_Coord) * ends.size);
        int count = 0;
        for(int i=0; i < WORKSPACE_INFO->starts.size; i++) {
            ends.locations[count++] = WORKSPACE_INFO->starts.locations[i];
        }
        for(int i=0; i < WORKSPACE_INFO->ends.size; i++) {
            ends.locations[count++] = WORKSPACE_INFO->ends.locations[i];
        }
        PreComputeObstacleDistanceH(WORKSPACE_INFO->dimension, WORKSPACE_INFO->obstacles, ends);
#endif

		processGuid.data1 = 1;
		processGuid.data2 = 0;
		processGuid.data3 = 0;
		processGuid.data4 = 0;
		process = PrtStartProcess(processGuid, &P_GEND_PROGRAM, ErrorHandler, Log);
        if (cooperative)
        {
            PrtSetSchedulingPolicy(process, PRT_SCHEDULINGPOLICY_COOPERATIVE);
        }
		if (parg == NULL)
		{
			payload = PrtMkNullValue();
		}
		else
		{
			int i = atoi(parg);
			payload = PrtMkIntValue(i);
		}

		PrtUpdateAssertFn(MyAssert);

		PrtMkMachine(process, P_MACHINE_Main, payload);

        if (cooperative)
        {
            // test some multithreading across state machines.
#if defined(PRT_PLAT_WINUSER)
			HANDLE* threadsArr = (HANDLE*)PrtMalloc(threads*sizeof(HANDLE));
            for (int i = 0; i < threads; i++)
            {
                DWORD threadId;
                threadsArr[i] = CreateThread(NULL, 16000, (LPTHREAD_START_ROUTINE)RunToIdle, process, 0, &threadId);
            }
			WaitForMultipleObjects(threads, threadsArr, TRUE, INFINITE);
			PrtFree(threadsArr);
#elif defined(PRT_PLAT_LINUXUSER)
typedef void *(*start_routine) (void *);
            pthread_t tid[threads];
            for (int i = 0; i < threads; i++)
            {
                pthread_create(&tid[i], NULL, (start_routine)RunToIdle, (void*)process);
            }
            for (int i = 0; i < threads; i++)
            {
                pthread_join(tid[i], NULL);
            }
#else
#error Invalid Platform
#endif
        }
		PrtFreeValue(payload);
		PrtStopProcess(process);
	}
	PRT_DBG_END_MEM_BALANCED_REGION

	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
}