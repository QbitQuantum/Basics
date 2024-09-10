void NordugridJob::doEvaluateState()
{
	int old_gm_state;
	bool reevaluate_state = true;
	time_t now = time(NULL);

	bool attr_exists;
	bool attr_dirty;
	int rc;

	daemonCore->Reset_Timer( evaluateStateTid, TIMER_NEVER );

    dprintf(D_ALWAYS,
			"(%d.%d) doEvaluateState called: gmState %s, condorState %d\n",
			procID.cluster,procID.proc,GMStateNames[gmState],condorState);

	if ( gahp ) {
		if ( !resourceStateKnown || resourcePingPending || resourceDown ) {
			gahp->setMode( GahpClient::results_only );
		} else {
			gahp->setMode( GahpClient::normal );
		}
	}

	do {
		reevaluate_state = false;
		old_gm_state = gmState;

		switch ( gmState ) {
		case GM_INIT: {
			// This is the state all jobs start in when the GlobusJob object
			// is first created. Here, we do things that we didn't want to
			// do in the constructor because they could block (the
			// constructor is called while we're connected to the schedd).
			if ( gahp->Startup() == false ) {
				dprintf( D_ALWAYS, "(%d.%d) Error starting GAHP\n",
						 procID.cluster, procID.proc );

				jobAd->Assign( ATTR_HOLD_REASON, "Failed to start GAHP" );
				gmState = GM_HOLD;
				break;
			}
			if ( gahp->Initialize( jobProxy ) == false ) {
				dprintf( D_ALWAYS, "(%d.%d) Error initializing GAHP\n",
						 procID.cluster, procID.proc );

				jobAd->Assign( ATTR_HOLD_REASON,
							   "Failed to initialize GAHP" );
				gmState = GM_HOLD;
				break;
			}

			gahp->setDelegProxy( jobProxy );

			gmState = GM_START;
			} break;
		case GM_START: {
			errorString = "";
			if ( remoteJobId == NULL ) {
				gmState = GM_CLEAR_REQUEST;
			} else {
				submitLogged = true;
				if ( condorState == RUNNING ||
					 condorState == COMPLETED ) {
					executeLogged = true;
				}

				if ( remoteJobState == "" ||
					 remoteJobState == REMOTE_STATE_ACCEPTING ||
					 remoteJobState == REMOTE_STATE_ACCEPTED ||
					 remoteJobState == REMOTE_STATE_PREPARING ) {
					gmState = GM_RECOVER_QUERY;
				} else {
					gmState = GM_SUBMITTED;
				}
			}
			} break;
		case GM_RECOVER_QUERY: {
			if ( condorState == REMOVED || condorState == HELD ) {
				gmState = GM_CANCEL;
			} else {
				if ( m_lastRemoteStatusUpdate > enteredCurrentGmState ) {
					if ( remoteJobState == REMOTE_STATE_ACCEPTING ||
						 remoteJobState == REMOTE_STATE_ACCEPTED ||
						 remoteJobState == REMOTE_STATE_PREPARING ) {
						gmState = GM_STAGE_IN;
					} else {
						gmState = GM_SUBMITTED;
					}
				} else if ( m_currentStatusUnknown ) {
					gmState = GM_CANCEL;
				}
			}
			} break;
		case GM_UNSUBMITTED: {
			if ( condorState == REMOVED ) {
				gmState = GM_DELETE;
			} else if ( condorState == HELD ) {
				gmState = GM_DELETE;
				break;
			} else {
				gmState = GM_SUBMIT;
			}
			} break;
		case GM_SUBMIT: {
			if ( condorState == REMOVED || condorState == HELD ) {
				myResource->CancelSubmit( this );
				gmState = GM_UNSUBMITTED;
				break;
			}
			if ( numSubmitAttempts >= MAX_SUBMIT_ATTEMPTS ) {
//				jobAd->Assign( ATTR_HOLD_REASON,
//							   "Attempts to submit failed" );
				gmState = GM_HOLD;
				break;
			}
			// After a submit, wait at least submitInterval before trying
			// another one.
			if ( now >= lastSubmitAttempt + submitInterval ) {

				char *job_id = NULL;

				// Once RequestSubmit() is called at least once, you must
				// CancelRequest() once you're done with the request call
				if ( myResource->RequestSubmit( this ) == false ) {
					break;
				}

				if ( RSL == NULL ) {
					RSL = buildSubmitRSL();
				}
				if ( RSL == NULL ) {
					gmState = GM_HOLD;
					break;
				}
				rc = gahp->nordugrid_submit( 
										resourceManagerString,
										RSL->c_str(),
										job_id );
				if ( rc == GAHPCLIENT_COMMAND_NOT_SUBMITTED ||
					 rc == GAHPCLIENT_COMMAND_PENDING ) {
					break;
				}

				lastSubmitAttempt = time(NULL);
				numSubmitAttempts++;

				if ( rc == 0 ) {
					ASSERT( job_id != NULL );
					SetRemoteJobId( job_id );
					free( job_id );
					WriteGridSubmitEventToUserLog( jobAd );
					gmState = GM_SUBMIT_SAVE;
				} else {
					errorString = gahp->getErrorString();
					dprintf(D_ALWAYS,"(%d.%d) job submit failed: %s\n",
							procID.cluster, procID.proc,
							errorString.c_str() );
					myResource->CancelSubmit( this );
					gmState = GM_UNSUBMITTED;
				}

			} else {
				unsigned int delay = 0;
				if ( (lastSubmitAttempt + submitInterval) > now ) {
					delay = (lastSubmitAttempt + submitInterval) - now;
				}				
				daemonCore->Reset_Timer( evaluateStateTid, delay );
			}
			} break;
		case GM_SUBMIT_SAVE: {
			if ( condorState == REMOVED || condorState == HELD ) {
				gmState = GM_CANCEL;
			} else {
				jobAd->GetDirtyFlag( ATTR_GRID_JOB_ID, &attr_exists, &attr_dirty );
				if ( attr_exists && attr_dirty ) {
					requestScheddUpdate( this, true );
					break;
				}
				gmState = GM_STAGE_IN;
			}
			} break;
		case GM_STAGE_IN: {
			if ( stageList == NULL ) {
				const char *file;
				stageList = buildStageInList();
				stageList->rewind();
				while ( (file = stageList->next()) ) {
					if ( IsUrl( file ) ) {
						stageList->deleteCurrent();
					}
				}
			}
			rc = gahp->nordugrid_stage_in( resourceManagerString, remoteJobId,
										   *stageList );
			if ( rc == GAHPCLIENT_COMMAND_NOT_SUBMITTED ||
				 rc == GAHPCLIENT_COMMAND_PENDING ) {
				break;
			} else if ( rc != 0 ) {
				errorString = gahp->getErrorString();
				dprintf( D_ALWAYS, "(%d.%d) file stage in failed: %s\n",
						 procID.cluster, procID.proc, errorString.c_str() );
				gmState = GM_CANCEL;
			} else {
				gmState = GM_SUBMITTED;
			}
			} break;
		case GM_SUBMITTED: {
			if ( remoteJobState == REMOTE_STATE_FINISHED ||
				 remoteJobState == REMOTE_STATE_FAILED ||
				 remoteJobState == REMOTE_STATE_KILLED ||
				 remoteJobState == REMOTE_STATE_DELETED ) {
					gmState = GM_EXIT_INFO;
			} else if ( condorState == REMOVED || condorState == HELD ) {
				gmState = GM_CANCEL;
			} else {
				if ( lastProbeTime < enteredCurrentGmState ) {
					lastProbeTime = enteredCurrentGmState;
				}
				if ( probeNow ) {
					lastProbeTime = 0;
					probeNow = false;
				}
/*
				int probe_interval = myResource->GetJobPollInterval();
				if ( now >= lastProbeTime + probe_interval ) {
					gmState = GM_PROBE_JOB;
					break;
				}
				unsigned int delay = 0;
				if ( (lastProbeTime + probe_interval) > now ) {
					delay = (lastProbeTime + probe_interval) - now;
				}				
				daemonCore->Reset_Timer( evaluateStateTid, delay );
*/
			}
			} break;
		case GM_PROBE_JOB: {
			if ( condorState == REMOVED || condorState == HELD ) {
				gmState = GM_CANCEL;
			} else {
				char *new_status = NULL;
				rc = gahp->nordugrid_status( resourceManagerString,
											 remoteJobId, new_status );
				if ( rc == GAHPCLIENT_COMMAND_NOT_SUBMITTED ||
					 rc == GAHPCLIENT_COMMAND_PENDING ) {
					break;
				} else if ( rc != 0 ) {
					// What to do about failure?
					errorString = gahp->getErrorString();
					dprintf( D_ALWAYS, "(%d.%d) job probe failed: %s\n",
							 procID.cluster, procID.proc,
							 errorString.c_str() );
				} else {
					if ( new_status ) {
						remoteJobState = new_status;
					} else {
						remoteJobState = "";
					}
					SetRemoteJobStatus( new_status );
				}
				if ( new_status ) {
					free( new_status );
				}
				lastProbeTime = now;
				gmState = GM_SUBMITTED;
			}
			} break;
		case GM_EXIT_INFO: {
			std::string filter;
			StringList reply;
			formatstr( filter, "nordugrid-job-globalid=gsiftp://%s:2811/jobs/%s",
							resourceManagerString, remoteJobId );

			rc = gahp->nordugrid_ldap_query( resourceManagerString, "mds-vo-name=local,o=grid", filter.c_str(), "nordugrid-job-usedcputime,nordugrid-job-usedwalltime,nordugrid-job-exitcode", reply );
			if ( rc == GAHPCLIENT_COMMAND_NOT_SUBMITTED ||
				 rc == GAHPCLIENT_COMMAND_PENDING ) {
				break;
			} else if ( rc != 0 ) {
				errorString = gahp->getErrorString();
				dprintf( D_ALWAYS, "(%d.%d) exit info gathering failed: %s\n",
						 procID.cluster, procID.proc, errorString.c_str() );
				gmState = GM_CANCEL;
			} else {
				int exit_code = -1;
				int wallclock = -1;
				int cpu = -1;
				const char *entry;
				reply.rewind();
				while ( (entry = reply.next()) ) {
					if ( !strncmp( entry, "nordugrid-job-usedcputime: ", 27 ) ) {
						entry = strchr( entry, ' ' ) + 1;
						cpu = atoi( entry );
					} else if ( !strncmp( entry, "nordugrid-job-usedwalltime: ", 28 ) ) {
						entry = strchr( entry, ' ' ) + 1;
						wallclock = atoi( entry );
					} else if ( !strncmp( entry, "nordugrid-job-exitcode: ", 24 ) ) {
						entry = strchr( entry, ' ' ) + 1;
						exit_code = atoi( entry );
					}
				}
				if ( exit_code < 0 || wallclock < 0 || cpu < 0 ) {
					dprintf( D_ALWAYS, "(%d.%d) exit info missing\n",
							 procID.cluster, procID.proc );
					gmState = GM_CANCEL;
					break;
				}
				if ( exit_code > 128 ) {
					jobAd->Assign( ATTR_ON_EXIT_BY_SIGNAL, true );
					jobAd->Assign( ATTR_ON_EXIT_SIGNAL, exit_code - 128 );
				} else {
					jobAd->Assign( ATTR_ON_EXIT_BY_SIGNAL, false );
					jobAd->Assign( ATTR_ON_EXIT_CODE, exit_code );
				}
				jobAd->Assign( ATTR_JOB_REMOTE_WALL_CLOCK, wallclock * 60 );
				jobAd->Assign( ATTR_JOB_REMOTE_USER_CPU, cpu * 60 );
				gmState = GM_STAGE_OUT;
			}
			} break;
		case GM_STAGE_OUT: {
			if ( stageList == NULL ) {
				stageList = buildStageOutList();
			}
			if ( stageLocalList == NULL ) {
				const char *file;
				stageLocalList = buildStageOutLocalList( stageList );
				stageList->rewind();
				stageLocalList->rewind();
				while ( (file = stageLocalList->next()) ) {
					ASSERT( stageList->next() );
					if ( IsUrl( file ) ) {
						stageList->deleteCurrent();
						stageLocalList->deleteCurrent();
				}
				}
			}
			rc = gahp->nordugrid_stage_out2( resourceManagerString,
											 remoteJobId,
											 *stageList, *stageLocalList );
			if ( rc == GAHPCLIENT_COMMAND_NOT_SUBMITTED ||
				 rc == GAHPCLIENT_COMMAND_PENDING ) {
				break;
			} else if ( rc != 0 ) {
				errorString = gahp->getErrorString();
				dprintf( D_ALWAYS, "(%d.%d) file stage out failed: %s\n",
						 procID.cluster, procID.proc, errorString.c_str() );
				gmState = GM_CANCEL;
			} else {
				gmState = GM_DONE_SAVE;
			}
			} break;
		case GM_DONE_SAVE: {
			if ( condorState != HELD && condorState != REMOVED ) {
				JobTerminated();
				if ( condorState == COMPLETED ) {
					jobAd->GetDirtyFlag( ATTR_JOB_STATUS, &attr_exists, &attr_dirty );
					if ( attr_exists && attr_dirty ) {
						requestScheddUpdate( this, true );
						break;
					}
				}
			}
			gmState = GM_DONE_COMMIT;
			} break;
		case GM_DONE_COMMIT: {
			rc = gahp->nordugrid_cancel( resourceManagerString, remoteJobId );
			if ( rc == GAHPCLIENT_COMMAND_NOT_SUBMITTED ||
				 rc == GAHPCLIENT_COMMAND_PENDING ) {
				break;
			} else if ( rc != 0 ) {
				errorString = gahp->getErrorString();
				dprintf( D_ALWAYS, "(%d.%d) job cleanup failed: %s\n",
						 procID.cluster, procID.proc, errorString.c_str() );
				gmState = GM_HOLD;
				break;
			}
			myResource->CancelSubmit( this );
			if ( condorState == COMPLETED || condorState == REMOVED ) {
				gmState = GM_DELETE;
			} else {
				// Clear the contact string here because it may not get
				// cleared in GM_CLEAR_REQUEST (it might go to GM_HOLD first).
				if ( remoteJobId != NULL ) {
					SetRemoteJobId( NULL );
				}
				gmState = GM_CLEAR_REQUEST;
			}
			} break;
		case GM_CANCEL: {
			rc = gahp->nordugrid_cancel( resourceManagerString, remoteJobId );
			if ( rc == GAHPCLIENT_COMMAND_NOT_SUBMITTED ||
				 rc == GAHPCLIENT_COMMAND_PENDING ) {
				break;
			} else if ( rc == 0 ) {
				gmState = GM_FAILED;
			} else {
				// What to do about a failed cancel?
				errorString = gahp->getErrorString();
				dprintf( D_ALWAYS, "(%d.%d) job cancel failed: %s\n",
						 procID.cluster, procID.proc, errorString.c_str() );
				gmState = GM_FAILED;
			}
			} break;
		case GM_FAILED: {
			myResource->CancelSubmit( this );
			SetRemoteJobId( NULL );

			if ( condorState == REMOVED ) {
				gmState = GM_DELETE;
			} else {
				gmState = GM_CLEAR_REQUEST;
			}
			} break;
		case GM_DELETE: {
			// The job has completed or been removed. Delete it from the
			// schedd.
			DoneWithJob();
			// This object will be deleted when the update occurs
			} break;
		case GM_CLEAR_REQUEST: {
			// Remove all knowledge of any previous or present job
			// submission, in both the gridmanager and the schedd.

			// If we are doing a rematch, we are simply waiting around
			// for the schedd to be updated and subsequently this globus job
			// object to be destroyed.  So there is nothing to do.
			if ( wantRematch ) {
				break;
			}

			// For now, put problem jobs on hold instead of
			// forgetting about current submission and trying again.
			// TODO: Let our action here be dictated by the user preference
			// expressed in the job ad.
			if ( remoteJobId != NULL
				     && condorState != REMOVED 
					 && wantResubmit == 0 
					 && doResubmit == 0 ) {
				gmState = GM_HOLD;
				break;
			}
			// Only allow a rematch *if* we are also going to perform a resubmit
			if ( wantResubmit || doResubmit ) {
				jobAd->EvalBool(ATTR_REMATCH_CHECK,NULL,wantRematch);
			}
			if ( wantResubmit ) {
				wantResubmit = 0;
				dprintf(D_ALWAYS,
						"(%d.%d) Resubmitting to Globus because %s==TRUE\n",
						procID.cluster, procID.proc, ATTR_GLOBUS_RESUBMIT_CHECK );
			}
			if ( doResubmit ) {
				doResubmit = 0;
				dprintf(D_ALWAYS,
					"(%d.%d) Resubmitting to Globus (last submit failed)\n",
						procID.cluster, procID.proc );
			}
			errorString = "";
			if ( remoteJobId != NULL ) {
				SetRemoteJobId( NULL );
			}
			JobIdle();
			if ( submitLogged ) {
				JobEvicted();
				if ( !evictLogged ) {
					WriteEvictEventToUserLog( jobAd );
					evictLogged = true;
				}
			}
			myResource->CancelSubmit( this );
			
			if ( wantRematch ) {
				dprintf(D_ALWAYS,
						"(%d.%d) Requesting schedd to rematch job because %s==TRUE\n",
						procID.cluster, procID.proc, ATTR_REMATCH_CHECK );

				// Set ad attributes so the schedd finds a new match.
				int dummy;
				if ( jobAd->LookupBool( ATTR_JOB_MATCHED, dummy ) != 0 ) {
					jobAd->Assign( ATTR_JOB_MATCHED, false );
					jobAd->Assign( ATTR_CURRENT_HOSTS, 0 );
				}

				// If we are rematching, we need to forget about this job
				// cuz we wanna pull a fresh new job ad, with a fresh new match,
				// from the all-singing schedd.
				gmState = GM_DELETE;
				break;
			}
			
			// If there are no updates to be done when we first enter this
			// state, requestScheddUpdate will return done immediately
			// and not waste time with a needless connection to the
			// schedd. If updates need to be made, they won't show up in
			// schedd_actions after the first pass through this state
			// because we modified our local variables the first time
			// through. However, since we registered update events the
			// first time, requestScheddUpdate won't return done until
			// they've been committed to the schedd.
			const char *name;
			ExprTree *expr;
			jobAd->ResetExpr();
			if ( jobAd->NextDirtyExpr(name, expr) ) {
				requestScheddUpdate( this, true );
				break;
			}
			if ( remoteJobState != "" ) {
				remoteJobState = "";
				SetRemoteJobStatus( NULL );
			}
			submitLogged = false;
			executeLogged = false;
			submitFailedLogged = false;
			terminateLogged = false;
			abortLogged = false;
			evictLogged = false;
			gmState = GM_UNSUBMITTED;
			} break;
		case GM_HOLD: {
			// Put the job on hold in the schedd.
			// TODO: what happens if we learn here that the job is removed?
			// If the condor state is already HELD, then someone already
			// HELD it, so don't update anything else.
			if ( condorState != HELD ) {

				// Set the hold reason as best we can
				// TODO: set the hold reason in a more robust way.
				char holdReason[1024];
				holdReason[0] = '\0';
				holdReason[sizeof(holdReason)-1] = '\0';
				jobAd->LookupString( ATTR_HOLD_REASON, holdReason,
									 sizeof(holdReason) );
				if ( holdReason[0] == '\0' && errorString != "" ) {
					strncpy( holdReason, errorString.c_str(),
							 sizeof(holdReason) - 1 );
				}
				if ( holdReason[0] == '\0' ) {
					strncpy( holdReason, "Unspecified gridmanager error",
							 sizeof(holdReason) - 1 );
				}

				JobHeld( holdReason );
			}
			gmState = GM_DELETE;
			} break;
		default:
			EXCEPT( "(%d.%d) Unknown gmState %d!", procID.cluster,procID.proc,
					gmState );
		}

		if ( gmState != old_gm_state ) {
			reevaluate_state = true;
			dprintf(D_FULLDEBUG, "(%d.%d) gm state change: %s -> %s\n",
					procID.cluster, procID.proc, GMStateNames[old_gm_state],
					GMStateNames[gmState]);
			enteredCurrentGmState = time(NULL);

			// If we were calling a gahp call that used RSL, we're done
			// with it now, so free it.
			if ( RSL ) {
				delete RSL;
				RSL = NULL;
			}
			if ( stageList ) {
				delete stageList;
				stageList = NULL;
			}
			if ( stageLocalList ) {
				delete stageLocalList;
				stageLocalList = NULL;
			}
		}

	} while ( reevaluate_state );
}