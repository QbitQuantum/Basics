void RVExtension(char *output, int outputSize, const char *function)
{
	char *stopstring;
	size_t funlen;

	if (output == NULL || outputSize <= 0 || function == NULL) return;
	funlen = strnlen(function, FUNCTIONSIZE + 2);	// "<n>:<OCCx string>"
	if (funlen == 0) return;
	if (funlen == FUNCTIONSIZE + 2) return;

	*output = '\0';

	//asmlog(LOG_INFO, "RVExtension(%p, %d, \"%s\")", output, outputSize, function);
	if (!isdigit(*function)) {
		do {
			// Get version
			if (strncasecmp(function, "version", sizeof("version")) == 0) {
				snprintf(output, outputSize, "%s", ASM_VERSION); // return the RV extension version
				break;
			}
			// (Debug) Get instance id
			if (strncasecmp(function, "id", sizeof("id")) == 0) {
				snprintf(output, outputSize, "%zd", InstanceID);
				break;
			}
		} while (0);
		output[outputSize - 1] = '\0';
		return;
	} else {
		// function is supposed to be <digit>:<data>
		if (function[1] != ':' || funlen < 3) {
			return;
		}
	}

	if (!FileMap) {
	   asmlog(LOG_ERR, "no FileMap");
	   return;
	}

	switch (*function) {
		case '0': // FPS update
			if (ArmaServerInfo != NULL) {
					unsigned FPS,FPSMIN;

					FPS = strtol(&function[2], &stopstring, 10);
					FPSMIN = strtol(&stopstring[1], &stopstring, 10);
					ArmaServerInfo->SERVER_FPS    =	FPS;
					ArmaServerInfo->SERVER_FPSMIN =	FPSMIN;
					ArmaServerInfo->TICK_COUNT    = gettickcount();

					asmlog(LOG_DEBUG, "0: FPS update");
			}
			break;

		case '1': // CPS update
			if (ArmaServerInfo != NULL) {
					struct timespec PCE;
					double tnsec;
					unsigned conditionNo;

					clock_gettime(CLOCK_MONOTONIC, &PCE);
					tnsec = (double)((1000000000 * PCE.tv_sec + PCE.tv_nsec) - (1000000000 * PCS.tv_sec + PCS.tv_nsec))/(double)(1000000000 * PCF.tv_sec + PCF.tv_nsec);
					conditionNo = strtol(&function[2], &stopstring, 10);
					ArmaServerInfo->FSM_CE_FREQ = floor(conditionNo * 1000 / tnsec + 0.5);

					PCS = PCE;
					asmlog(LOG_DEBUG, "1: CPS update");
			}
			break;

		case '2': // GEN update
			if (ArmaServerInfo != NULL) {
				unsigned players, ail, air;
				FILE* f = NULL;
				long rss = 0L;

				players = strtol(&function[2],   &stopstring, 10);
				ail		= strtol(&stopstring[1], &stopstring, 10);
				air		= strtol(&stopstring[1], &stopstring, 10);
				ArmaServerInfo->PLAYER_COUNT = players;
				ArmaServerInfo->AI_LOC_COUNT = ail;
				ArmaServerInfo->AI_REM_COUNT = air;

				// ASMdll.dll for Windows gets the "Commit Charge" value here,
				// the total memory that the memory manager has committed
				// for a running process. (unit: bytes)
				if ((f = fopen("/proc/self/statm", "r")) != NULL) {
					// The second number in statm is the size of the in-memory
					// working set (RSS). TODO: is this the value we want?
					if (fscanf(f, "%*s%8ld", &rss) != 1) {
						rss = 0L;
					}
					fclose(f);
				}
				ArmaServerInfo->MEM = rss * pagesize;
				asmlog(LOG_DEBUG, "2: GEN update");
			}
			break;

		case '3': // MISSION update
			if (ArmaServerInfo != NULL) {
				memset(ArmaServerInfo->MISSION, 0, SMALSTRINGSIZE);
				strncpy(ArmaServerInfo->MISSION, &function[2], SMALSTRINGSIZE);
				ArmaServerInfo->MISSION[SMALSTRINGSIZE-1] = 0;
				asmlog(LOG_DEBUG, "3: MISSION update");
			}
			break;

		case '4': // OBJ_COUNT_0 update
			if (ArmaServerInfo != NULL) {
				unsigned obj;
				obj = strtol(&function[2], &stopstring, 10);
				ArmaServerInfo->OBJ_COUNT_0 = obj;
				asmlog(LOG_DEBUG, "4: OBJ_COUNT_0 update");
			}
			break;

		case '5': // OBJ_COUNT_1 update
			if (ArmaServerInfo != NULL) {
				unsigned obj;
				obj = strtol(&function[2], &stopstring, 10);
				ArmaServerInfo->OBJ_COUNT_1 = obj;
				asmlog(LOG_DEBUG, "5: OBJ_COUNT_1 update");
			}
			break;

		case '6': // OBJ_COUNT_2 update
			if (ArmaServerInfo != NULL) {
				unsigned obj;
				obj = strtol(&function[2], &stopstring, 10);
				ArmaServerInfo->OBJ_COUNT_2 = obj;
				asmlog(LOG_DEBUG, "6: OBJ_COUNT_2 update");
			}
			break;

		case '9': // init
			if (ArmaServerInfo == NULL) {
				if (enableProfilePrefixSlotSelection > 0 && isdigit(function[2])) {
					asmlog(LOG_DEBUG, "selecting slot based on profileName...");
					// Select the instance based on the leading digit in the server's profile name
					errno = 0;
					InstanceID = strtol(&function[2], &stopstring, 10);
					if (errno == 0 && InstanceID < MAX_ARMA_INSTANCES) {
						ArmaServerInfo = (struct ARMA_SERVER_INFO*)((unsigned char *)FileMap + (InstanceID * pagesize));
					}
				} else {
					asmlog(LOG_DEBUG, "finding available slot");
					// Find a free server info slot or re-use one if it hasn't been updated in the last 10 seconds
					uint32_t DeadTimeout = gettickcount() - 10000;
					for (InstanceID = 0 ; InstanceID < MAX_ARMA_INSTANCES ; InstanceID++) {
						ArmaServerInfo = (struct ARMA_SERVER_INFO*)((unsigned char *)FileMap + (InstanceID * pagesize));
						if ((ArmaServerInfo->PID == 0) || (ArmaServerInfo->TICK_COUNT < DeadTimeout)) break;
					}
				}
				if (ArmaServerInfo != NULL && InstanceID < MAX_ARMA_INSTANCES) {
					ArmaServerInfo->MEM = 0;
					ArmaServerInfo->TICK_COUNT = gettickcount();
					ArmaServerInfo->PID = getpid();
					memset(ArmaServerInfo->PROFILE, 0, sizeof(ArmaServerInfo->PROFILE));
					strncpy(ArmaServerInfo->PROFILE, &function[2], sizeof(ArmaServerInfo->PROFILE));
					ArmaServerInfo->PROFILE[sizeof(ArmaServerInfo->PROFILE) - 1] = '\0';
					asmlog(LOG_INFO, "init successful, pid %zd, using slot %d", ArmaServerInfo->PID, InstanceID);
					snprintf(output, outputSize, "_ASM_OPT=[%s,%s,%s,\"%s\",\"%s\",\"%s\"];", OCI0, OCI1, OCI2, OCC0, OCC1, OCC2);
				} else {
					ArmaServerInfo = NULL;
					asmlog(LOG_ERR, "init failed - no available slots.");
					snprintf(output, outputSize, "_ASM_OPT=[0,0,0,\"\",\"\",\"\"];");
				}
				output[outputSize - 1] = '\0';
			} else {
				ArmaServerInfo->MEM = 0;
			}
			break;

		default: // 7,8 are not implemented
			return;
	}
	if (ArmaServerInfo != NULL) {
		if (msync(ArmaServerInfo, pagesize, MS_ASYNC|MS_INVALIDATE) != 0) {
			asmlog(LOG_ERR, "msync(): %s", strerror(errno));
		}
	}
	return;
}