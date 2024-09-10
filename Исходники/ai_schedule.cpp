bool CAI_SchedulesManager::LoadSchedulesFromBuffer( const char *prefix, char *pStartFile, CAI_ClassScheduleIdSpace *pIdSpace )
{
	char token[1024];
	char save_token[1024];
	const char *pfile = engine->ParseFile(pStartFile, token, sizeof( token ) );

	while (!stricmp("Schedule",token))
	{
		pfile = engine->ParseFile(pfile, token, sizeof( token ) );

		// -----------------------------
		// Check for duplicate schedule
		// -----------------------------
		if (GetScheduleByName(token))
		{
			DevMsg("ERROR: file contains a schedule (%s) that has already been defined!\n",token);
			DevMsg("       Aborting schedule load.\n");
			Assert(0);
			return false;
		}

		int scheduleID = CAI_BaseNPC::GetScheduleID(token);
		if (scheduleID == -1)
		{
			DevMsg( "ERROR: LoadSchd (%s): Unknown schedule type (%s)\n", prefix, token);
			// FIXME: .sch's not being in code/perforce makes it hard to share branches between developers
			// for now, just stop processing this entities schedules if one is found that isn't in the schedule registry
			break;
			// return false;
		}

		CAI_Schedule *new_schedule = CreateSchedule(token,scheduleID);

		pfile = engine->ParseFile(pfile, token, sizeof( token ) );
		if (stricmp(token,"Tasks"))
		{
			DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting 'Tasks' keyword.\n",prefix,new_schedule->GetName());
			Assert(0);
			return false;
		}

		// ==========================
		// Now read in the tasks
		// ==========================
		// Store in temp array until number of tasks is known
		Task_t tempTask[50];
		int	   taskNum = 0;

		pfile = engine->ParseFile(pfile, token, sizeof( token ) );
		while ((token[0] != '\0') && (stricmp("Interrupts", token)))
		{
			// Convert generic ID to sub-class specific enum
			int taskID = CAI_BaseNPC::GetTaskID(token);
			tempTask[taskNum].iTask = (pIdSpace) ? pIdSpace->TaskGlobalToLocal(taskID) : AI_RemapFromGlobal( taskID );
			
			// If not a valid condition, send a warning message
			if (tempTask[taskNum].iTask == -1)
			{
				DevMsg( "ERROR: LoadSchd (%s): (%s) Unknown task %s!\n", prefix,new_schedule->GetName(), token);
				Assert(0);
				return false;
			}

			Assert( AI_IdIsLocal( tempTask[taskNum].iTask ) );

			// Read in the task argument
			pfile = engine->ParseFile(pfile, token, sizeof( token ) );

			if (!stricmp("Activity",token))
			{
				// Skip the ";", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'ACTIVITY.\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the activity and make sure its valid
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				tempTask[taskNum].flTaskData = CAI_BaseNPC::GetActivityID(token);
				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Unknown activity %s!\n", prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if (!stricmp("Task",token))
			{
				// Skip the ";", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'ACTIVITY.\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the activity and make sure its valid
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );

				// Convert generic ID to sub-class specific enum
				int taskID = CAI_BaseNPC::GetTaskID(token);
				tempTask[taskNum].flTaskData = (pIdSpace) ? pIdSpace->TaskGlobalToLocal(taskID) : AI_RemapFromGlobal( taskID );

				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Unknown task %s!\n", prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if (!stricmp("Schedule",token))
			{
				// Skip the ";", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'ACTIVITY.\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the schedule and make sure its valid
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );

				// Convert generic ID to sub-class specific enum
				int schedID = CAI_BaseNPC::GetScheduleID(token);
				tempTask[taskNum].flTaskData = (pIdSpace) ? pIdSpace->ScheduleGlobalToLocal(schedID) : AI_RemapFromGlobal( schedID );

				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd %d (%s): (%s) Unknown shedule %s!\n", __LINE__, prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if (!stricmp("State",token))
			{
				// Skip the ";", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'STATE.\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the activity and make sure its valid
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				tempTask[taskNum].flTaskData = CAI_SchedulesManager::GetStateID(token);
				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd %d (%s): (%s) Unknown shedule %s!\n", __LINE__, prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if (!stricmp("Memory",token))
			{

				// Skip the ";", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'STATE.\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the activity and make sure its valid
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				tempTask[taskNum].flTaskData = CAI_SchedulesManager::GetMemoryID(token);
				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd %d (%s): (%s) Unknown shedule %s!\n", __LINE__, prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if (!stricmp("Path",token))
			{
				// Skip the ";", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'PATH.\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the activity and make sure its valid
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				tempTask[taskNum].flTaskData = CAI_SchedulesManager::GetPathID( token );
				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Unknown path type %s!\n", prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if (!stricmp("Goal",token))
			{
				// Skip the ";", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'GOAL.\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the activity and make sure its valid
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				tempTask[taskNum].flTaskData = CAI_SchedulesManager::GetGoalID( token );
				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Unknown goal type  %s!\n", prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if ( !stricmp( "HintFlags",token ) )
			{
				// Skip the ":", but make sure it's present
				pfile = engine->ParseFile(pfile, token, sizeof( token ) );
				if (stricmp(token,":"))
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Malformed AI Schedule.  Expecting ':' after type 'HINTFLAG'\n",prefix,new_schedule->GetName());
					Assert(0);
					return false;
				}

				// Load the flags and make sure they are valid
				pfile = engine->ParseFile( pfile, token, sizeof( token ) );
				tempTask[taskNum].flTaskData = CAI_HintManager::GetFlags( token );
				if (tempTask[taskNum].flTaskData == -1)
				{
					DevMsg( "ERROR: LoadSchd (%s): (%s) Unknown hint flag type  %s!\n", prefix,new_schedule->GetName(), token);
					Assert(0);
					return false;
				}
			}
			else if (!stricmp("Interrupts",token) || !strnicmp("TASK_",token,5) )
			{
				// a parse error.  Interrupts is the next section, TASK_ is probably the next task, missing task argument?
				Warning( "ERROR: LoadSchd (%s): (%s) Bad syntax at task #%d (wasn't expecting %s)\n", prefix, new_schedule->GetName(), taskNum, token);
				Assert(0);
				return false;
			}
			else
			{
				tempTask[taskNum].flTaskData = atof(token);
			}
			taskNum++;

			// Read the next token
			Q_strncpy(save_token,token,sizeof(save_token));
			pfile = engine->ParseFile(pfile, token, sizeof( token ) );

			// Check for malformed task argument type
			if (!stricmp(token,":"))
			{
				DevMsg( "ERROR: LoadSchd (%s): Schedule (%s),\n        Task (%s), has a malformed AI Task Argument = (%s)\n",
						prefix,new_schedule->GetName(),taskID,save_token);
				Assert(0);
				return false;
			}
		}

		// Now copy the tasks into the new schedule
		new_schedule->m_iNumTasks = taskNum;
		new_schedule->m_pTaskList = new Task_t[taskNum];
		for (int i=0;i<taskNum;i++)
		{
			new_schedule->m_pTaskList[i].iTask		= tempTask[i].iTask;
			new_schedule->m_pTaskList[i].flTaskData = tempTask[i].flTaskData;

			Assert( AI_IdIsLocal( new_schedule->m_pTaskList[i].iTask ) );
		}

		// ==========================
		// Now read in the interrupts
		// ==========================
		pfile = engine->ParseFile(pfile, token, sizeof( token ) );
		while ((token[0] != '\0') && (stricmp("Schedule", token)))
		{
			// Convert generic ID to sub-class specific enum
			int condID = CAI_BaseNPC::GetConditionID(token);

			// If not a valid condition, send a warning message
			if (condID == -1)
			{
				DevMsg( "ERROR: LoadSchd (%s): Schedule (%s), Unknown condition %s!\n", prefix,new_schedule->GetName(),token);
				Assert(0);
			}

			// Otherwise, add to this schedules list of conditions
			else
			{
				int interrupt = AI_RemapFromGlobal(condID);
				Assert( AI_IdIsGlobal( condID ) && interrupt >= 0 && interrupt < MAX_CONDITIONS );
				new_schedule->m_InterruptMask.Set(interrupt);
			}

			// Read the next token
			pfile = engine->ParseFile(pfile, token, sizeof( token ) );
		}
	}
	return true;
}