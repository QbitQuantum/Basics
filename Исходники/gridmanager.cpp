void
doContactSchedd()
{
	int rc;
	Qmgr_connection *schedd;
	BaseJob *curr_job;
	ClassAd *next_ad;
	char expr_buf[12000];
	bool schedd_updates_complete = false;
	bool schedd_deletes_complete = false;
	bool add_remove_jobs_complete = false;
	bool update_jobs_complete = false;
	bool commit_transaction = true;
	int failure_line_num = 0;
	bool send_reschedule = false;
	std::string error_str = "";
	StringList dirty_job_ids;
	char *job_id_str;
	PROC_ID job_id;
	CondorError errstack;

	dprintf(D_FULLDEBUG,"in doContactSchedd()\n");

	initJobExprs();

	contactScheddTid = TIMER_UNSET;

	// vacateJobs
	/////////////////////////////////////////////////////
	if ( pendingScheddVacates.getNumElements() != 0 ) {
		std::string buff;
		StringList job_ids;
		VacateRequest curr_request;

		int result;
		ClassAd* rval;

		pendingScheddVacates.startIterations();
		while ( pendingScheddVacates.iterate( curr_request ) != 0 ) {
			formatstr( buff, "%d.%d", curr_request.job->procID.cluster,
						  curr_request.job->procID.proc );
			job_ids.append( buff.c_str() );
		}

		char *tmp = job_ids.print_to_string();
		if ( tmp ) {
			dprintf( D_FULLDEBUG, "Calling vacateJobs on %s\n", tmp );
			free(tmp);
			tmp = NULL;
		}

		rval = ScheddObj->vacateJobs( &job_ids, VACATE_FAST, &errstack );
		if ( rval == NULL ) {
			formatstr( error_str, "vacateJobs returned NULL, CondorError: %s!",
							   errstack.getFullText().c_str() );
			goto contact_schedd_failure;
		} else {
			pendingScheddVacates.startIterations();
			while ( pendingScheddVacates.iterate( curr_request ) != 0 ) {
				formatstr( buff, "job_%d_%d", curr_request.job->procID.cluster,
							  curr_request.job->procID.proc );
				if ( !rval->LookupInteger( buff.c_str(), result ) ) {
					dprintf( D_FULLDEBUG, "vacateJobs returned malformed ad\n" );
					EXCEPT( "vacateJobs returned malformed ad" );
				} else {
					dprintf( D_FULLDEBUG, "   %d.%d vacate result: %d\n",
							 curr_request.job->procID.cluster,
							 curr_request.job->procID.proc,result);
					pendingScheddVacates.remove( curr_request.job->procID );
					curr_request.result = (action_result_t)result;
					curr_request.job->SetEvaluateState();
					completedScheddVacates.insert( curr_request.job->procID,
												   curr_request );
				}
			}
			delete rval;
		}
	}


	schedd = ConnectQ( ScheddAddr, QMGMT_TIMEOUT, false, NULL, myUserName, CondorVersion() );
	if ( !schedd ) {
		error_str = "Failed to connect to schedd!";
		goto contact_schedd_failure;
	}


	// CheckLeases
	/////////////////////////////////////////////////////
	if ( checkLeasesSignaled ) {

		dprintf( D_FULLDEBUG, "querying for renewed leases\n" );

		// Grab the lease attributes of all the jobs in our global hashtable.

		BaseJob::JobsByProcId.startIterations();

		while ( BaseJob::JobsByProcId.iterate( curr_job ) != 0 ) {
			int new_expiration;

			rc = GetAttributeInt( curr_job->procID.cluster,
								  curr_job->procID.proc,
								  ATTR_TIMER_REMOVE_CHECK,
								  &new_expiration );
			if ( rc < 0 ) {
				if ( errno == ETIMEDOUT ) {
					failure_line_num = __LINE__;
					commit_transaction = false;
					goto contact_schedd_disconnect;
				} else {
						// This job doesn't have doesn't have a lease from
						// the submitter. Skip it.
					continue;
				}
			}
			curr_job->UpdateJobLeaseReceived( new_expiration );
		}

		checkLeasesSignaled = false;
	}	// end of handling check leases


	// AddJobs
	/////////////////////////////////////////////////////
	if ( addJobsSignaled || firstScheddContact ) {
		int num_ads = 0;

		dprintf( D_FULLDEBUG, "querying for new jobs\n" );

		// Make sure we grab all Globus Universe jobs (except held ones
		// that we previously indicated we were done with)
		// when we first start up in case we're recovering from a
		// shutdown/meltdown.
		// Otherwise, grab all jobs that are unheld and aren't marked as
		// currently being managed and aren't marked as not matched.
		// If JobManaged is undefined, equate it with false.
		// If Matched is undefined, equate it with true.
		// NOTE: Schedds from Condor 6.6 and earlier don't include
		//   "(Universe==9)" in the constraint they give to the gridmanager,
		//   so this gridmanager will pull down non-globus-universe ads,
		//   although it won't use them. This is inefficient but not
		//   incorrect behavior.
		if ( firstScheddContact ) {
			// Grab all jobs for us to manage. This expression is a
			// derivative of the expression below for new jobs. We add
			// "|| Managed =?= TRUE" to also get jobs our previous
			// incarnation was in the middle of managing when it died
			// (if it died unexpectedly). With the new term, the
			// "&& Managed =!= TRUE" from the new jobs expression becomes
			// superfluous (by boolean logic), so we drop it.
			sprintf( expr_buf,
					 "%s && %s && ((%s && %s) || %s)",
					 expr_schedd_job_constraint.c_str(), 
					 expr_not_completely_done.c_str(),
					 expr_matched_or_undef.c_str(),
					 expr_not_held.c_str(),
					 expr_managed.c_str()
					 );
		} else {
			// Grab new jobs for us to manage
			sprintf( expr_buf,
					 "%s && %s && %s && %s && %s",
					 expr_schedd_job_constraint.c_str(), 
					 expr_not_completely_done.c_str(),
					 expr_matched_or_undef.c_str(),
					 expr_not_held.c_str(),
					 expr_not_managed.c_str()
					 );
		}
		dprintf( D_FULLDEBUG,"Using constraint %s\n",expr_buf);
		next_ad = GetNextJobByConstraint( expr_buf, 1 );
		while ( next_ad != NULL ) {
			PROC_ID procID;
			BaseJob *old_job;
			int job_is_matched = 1;		// default to true if not in ClassAd

			next_ad->LookupInteger( ATTR_CLUSTER_ID, procID.cluster );
			next_ad->LookupInteger( ATTR_PROC_ID, procID.proc );
			bool job_is_managed = jobExternallyManaged(next_ad);
			next_ad->LookupBool(ATTR_JOB_MATCHED,job_is_matched);

			if ( BaseJob::JobsByProcId.lookup( procID, old_job ) != 0 ) {

				JobType *job_type = NULL;
				BaseJob *new_job = NULL;

				// job had better be either managed or matched! (or both)
				ASSERT( job_is_managed || job_is_matched );

				if ( MustExpandJobAd( next_ad ) ) {
					// Get the expanded ClassAd from the schedd, which
					// has the GridResource filled in with info from
					// the matched ad.
					delete next_ad;
					next_ad = NULL;
					next_ad = GetJobAd(procID.cluster,procID.proc);
					if ( next_ad == NULL && errno == ETIMEDOUT ) {
						failure_line_num = __LINE__;
						commit_transaction = false;
						goto contact_schedd_disconnect;
					}
					if ( next_ad == NULL ) {
						// We may get here if it was not possible to expand
						// one of the $$() expressions.  We don't want to
						// roll back the transaction and blow away the
						// hold that the schedd just put on the job, so
						// simply skip over this ad.
						dprintf(D_ALWAYS,"Failed to get expanded job ClassAd from Schedd for %d.%d.  errno=%d\n",procID.cluster,procID.proc,errno);
						goto contact_schedd_next_add_job;
					}
				}

				// Search our job types for one that'll handle this job
				jobTypes.Rewind();
				while ( jobTypes.Next( job_type ) ) {
					if ( job_type->AdMatchFunc( next_ad ) ) {

						// Found one!
						dprintf( D_FULLDEBUG, "Using job type %s for job %d.%d\n",
								 job_type->Name, procID.cluster, procID.proc );
						break;
					}
				}

				if ( job_type != NULL ) {
					new_job = job_type->CreateFunc( next_ad );
				} else {
					dprintf( D_ALWAYS, "No handlers for job %d.%d\n",
							 procID.cluster, procID.proc );
					new_job = new BaseJob( next_ad );
				}

				ASSERT(new_job);
				new_job->SetEvaluateState();
				dprintf(D_ALWAYS,"Found job %d.%d --- inserting\n",
						new_job->procID.cluster,new_job->procID.proc);
				num_ads++;

				if ( !job_is_managed ) {
					rc = tSetAttributeString( new_job->procID.cluster,
									   new_job->procID.proc,
									   ATTR_JOB_MANAGED,
									   MANAGED_EXTERNAL);
					if ( rc < 0 ) {
						failure_line_num = __LINE__;
						commit_transaction = false;
						goto contact_schedd_disconnect;
					}
				}

			} else {

				// We already know about this job, skip
				// But also set Managed=true on the schedd so that it won't
				// keep signalling us about it
				delete next_ad;
				rc = tSetAttributeString( procID.cluster, procID.proc,
								   ATTR_JOB_MANAGED, MANAGED_EXTERNAL );
				if ( rc < 0 ) {
					failure_line_num = __LINE__;
					commit_transaction = false;
					goto contact_schedd_disconnect;
				}

			}

contact_schedd_next_add_job:
			next_ad = GetNextJobByConstraint( expr_buf, 0 );
		}	// end of while next_ad
		if ( errno == ETIMEDOUT ) {
			failure_line_num = __LINE__;
			commit_transaction = false;
			goto contact_schedd_disconnect;
		}

		dprintf(D_FULLDEBUG,"Fetched %d new job ads from schedd\n",num_ads);
	}	// end of handling add jobs


	// RemoveJobs
	/////////////////////////////////////////////////////

	// We always want to perform this check. Otherwise, we may overwrite a
	// REMOVED/HELD/COMPLETED status with something else below.
	{
		int num_ads = 0;

		dprintf( D_FULLDEBUG, "querying for removed/held jobs\n" );

		// Grab jobs marked as REMOVED/COMPLETED or marked as HELD that we
		// haven't previously indicated that we're done with (by setting
		// JobManaged to "Schedd".
		sprintf( expr_buf, "(%s) && (%s) && (%s == %d || %s == %d || (%s == %d && %s =?= \"%s\"))",
				 ScheddJobConstraint, expr_not_completely_done.c_str(),
				 ATTR_JOB_STATUS, REMOVED,
				 ATTR_JOB_STATUS, COMPLETED, ATTR_JOB_STATUS, HELD,
				 ATTR_JOB_MANAGED, MANAGED_EXTERNAL );

		dprintf( D_FULLDEBUG,"Using constraint %s\n",expr_buf);
		next_ad = GetNextJobByConstraint( expr_buf, 1 );
		while ( next_ad != NULL ) {
			PROC_ID procID;
			BaseJob *next_job;
			int curr_status;

			next_ad->LookupInteger( ATTR_CLUSTER_ID, procID.cluster );
			next_ad->LookupInteger( ATTR_PROC_ID, procID.proc );
			next_ad->LookupInteger( ATTR_JOB_STATUS, curr_status );

			if ( BaseJob::JobsByProcId.lookup( procID, next_job ) == 0 ) {
				// Should probably skip jobs we already have marked as
				// held or removed

				next_job->JobAdUpdateFromSchedd( next_ad, true );
				num_ads++;

			} else if ( curr_status == REMOVED ) {

				// If we don't know about the job, act like we got an
				// ADD_JOBS signal from the schedd the next time we
				// connect, so that we'll create a Job object for it
				// and decide how it needs to be handled.
				// TODO The AddJobs and RemoveJobs queries shoule be
				//   combined into a single query.
				dprintf( D_ALWAYS, 
						 "Don't know about removed job %d.%d. "
						 "Will treat it as a new job to manage\n",
						 procID.cluster, procID.proc );
				addJobsSignaled = true;

			} else {

				dprintf( D_ALWAYS, "Don't know about held/completed job %d.%d. "
						 "Ignoring it\n",
						 procID.cluster, procID.proc );

			}

			delete next_ad;
			next_ad = GetNextJobByConstraint( expr_buf, 0 );
		}
		if ( errno == ETIMEDOUT ) {
			failure_line_num = __LINE__;
			commit_transaction = false;
			goto contact_schedd_disconnect;
		}

		dprintf(D_FULLDEBUG,"Fetched %d job ads from schedd\n",num_ads);
	}

	if ( RemoteCommitTransaction() < 0 ) {
		failure_line_num = __LINE__;
		commit_transaction = false;
		goto contact_schedd_disconnect;
	}

	add_remove_jobs_complete = true;


	// Retrieve dirty attributes
	/////////////////////////////////////////////////////
	if ( updateJobsSignaled ) {
		dprintf( D_FULLDEBUG, "querying for jobs with attribute updates\n" );

		sprintf( expr_buf, "%s && %s && %s && %s",
				 expr_schedd_job_constraint.c_str(), 
				 expr_not_completely_done.c_str(),
				 expr_not_held.c_str(),
				 expr_managed.c_str()
				 );
		dprintf( D_FULLDEBUG,"Using constraint %s\n",expr_buf);
		next_ad = GetNextDirtyJobByConstraint( expr_buf, 1 );
		while ( next_ad != NULL ) {
			ClassAd updates;
			char str[PROC_ID_STR_BUFLEN];
			next_ad->LookupInteger( ATTR_CLUSTER_ID, job_id.cluster );
			next_ad->LookupInteger( ATTR_PROC_ID, job_id.proc );
			if ( GetDirtyAttributes( job_id.cluster, job_id.proc, &updates ) < 0 ) {
				dprintf( D_ALWAYS, "Failed to retrieve dirty attributes for job %d.%d\n", job_id.cluster, job_id.proc );
				failure_line_num = __LINE__;
				delete next_ad;
				goto contact_schedd_disconnect;
		        }
			else {
				dprintf (D_FULLDEBUG, "Retrieved updated attributes for job %d.%d\n", job_id.cluster, job_id.proc);
				dPrintAd(D_JOB, updates);
			}
			if ( BaseJob::JobsByProcId.lookup( job_id, curr_job ) == 0 ) {
				curr_job->JobAdUpdateFromSchedd( &updates, false );
				ProcIdToStr( job_id, str );
				dirty_job_ids.append( str );
			}
			else {
				dprintf( D_ALWAYS, "Don't know about updated job %d.%d. "
						 "Ignoring it\n",
						 job_id.cluster, job_id.proc );
			}
			delete next_ad;
			next_ad = GetNextDirtyJobByConstraint( expr_buf, 0 );
		}
	}
	update_jobs_complete = true;

//	if ( BeginTransaction() < 0 ) {
	errno = 0;
	BeginTransaction();
	if ( errno == ETIMEDOUT ) {
		failure_line_num = __LINE__;
		commit_transaction = false;
		goto contact_schedd_disconnect;
	}


	// requestJobStatus
	/////////////////////////////////////////////////////
	if ( pendingJobStatus.getNumElements() != 0 ) {
		JobStatusRequest curr_request;

		pendingJobStatus.startIterations();
		while ( pendingJobStatus.iterate( curr_request ) != 0 ) {

			int status;

			rc = GetAttributeInt( curr_request.job_id.cluster,
								  curr_request.job_id.proc,
								  ATTR_JOB_STATUS, &status );
			if ( rc < 0 ) {
				if ( errno == ETIMEDOUT ) {
					failure_line_num = __LINE__;
					commit_transaction = false;
					goto contact_schedd_disconnect;
				} else {
						// The job is not in the schedd's job queue. This
						// probably means that the user did a condor_rm -f,
						// so return a job status of REMOVED.
					status = REMOVED;
				}
			}
				// return status
			dprintf( D_FULLDEBUG, "%d.%d job status: %d\n",
					 curr_request.job_id.cluster,
					 curr_request.job_id.proc, status );
			pendingJobStatus.remove( curr_request.job_id );
			curr_request.job_status = status;
			daemonCore->Reset_Timer( curr_request.tid, 0 );
			completedJobStatus.insert( curr_request.job_id,
									   curr_request );
		}

	}


	// Update existing jobs
	/////////////////////////////////////////////////////
	ScheddUpdateRequest *curr_request;
	pendingScheddUpdates.startIterations();

	while ( pendingScheddUpdates.iterate( curr_request ) != 0 ) {

		curr_job = curr_request->m_job;
		dprintf(D_FULLDEBUG,"Updating classad values for %d.%d:\n",
				curr_job->procID.cluster, curr_job->procID.proc);
		const char *attr_name;
		const char *attr_value;
		ExprTree *expr;
		bool fake_job_in_queue = false;
		curr_job->jobAd->ResetExpr();
		while ( curr_job->jobAd->NextDirtyExpr(attr_name, expr) == true &&
				fake_job_in_queue == false ) {
			attr_value = ExprTreeToString( expr );

			dprintf(D_FULLDEBUG,"   %s = %s\n",attr_name,attr_value);
			rc = SetAttribute( curr_job->procID.cluster,
							   curr_job->procID.proc,
							   attr_name,
							   attr_value);
			if ( rc < 0 ) {
				if ( errno == ETIMEDOUT ) {
					failure_line_num = __LINE__;
					commit_transaction = false;
					goto contact_schedd_disconnect;
				} else {
						// The job is not in the schedd's job queue. This
						// probably means that the user did a condor_rm -f,
						// so pretend that all updates for the job succeed.
						// Otherwise, we'll never make forward progress on
						// the job.
						// TODO We should also fake a job status of REMOVED
						//   to the job, so it can do what cleanup it can.
					fake_job_in_queue = true;
					break;
				}
			}
		}

	}

	if ( RemoteCommitTransaction() < 0 ) {
		failure_line_num = __LINE__;
		commit_transaction = false;
		goto contact_schedd_disconnect;
	}

	schedd_updates_complete = true;


	// Delete existing jobs
	/////////////////////////////////////////////////////
	errno = 0;
	BeginTransaction();
	if ( errno == ETIMEDOUT ) {
		failure_line_num = __LINE__;
		commit_transaction = false;
		goto contact_schedd_disconnect;
	}

	pendingScheddUpdates.startIterations();

	while ( pendingScheddUpdates.iterate( curr_request ) != 0 ) {

		curr_job = curr_request->m_job;
		if ( curr_job->deleteFromSchedd ) {
			dprintf(D_FULLDEBUG,"Deleting job %d.%d from schedd\n",
					curr_job->procID.cluster, curr_job->procID.proc);
			rc = DestroyProc(curr_job->procID.cluster,
							 curr_job->procID.proc);
				// NOENT means the job doesn't exist.  Good enough for us.
			if ( rc < 0 && rc != DESTROYPROC_ENOENT) {
				failure_line_num = __LINE__;
				commit_transaction = false;
				goto contact_schedd_disconnect;
			}
		}

	}

	if ( RemoteCommitTransaction() < 0 ) {
		failure_line_num = __LINE__;
		commit_transaction = false;
		goto contact_schedd_disconnect;
	}

	schedd_deletes_complete = true;


 contact_schedd_disconnect:
	DisconnectQ( schedd, commit_transaction );

	if ( add_remove_jobs_complete == true ) {
		firstScheddContact = false;
		addJobsSignaled = false;
	} else {
		formatstr( error_str, "Schedd connection error during Add/RemoveJobs at line %d!", failure_line_num );
		goto contact_schedd_failure;
	}

	if ( update_jobs_complete == true ) {
		updateJobsSignaled = false;
	} else {
		formatstr( error_str, "Schedd connection error during dirty attribute update at line %d!", failure_line_num );
		goto contact_schedd_failure;
	}

	if ( schedd_updates_complete == false ) {
		formatstr( error_str, "Schedd connection error during updates at line %d!", failure_line_num );
		goto contact_schedd_failure;
	}

	// Clear dirty bits for all jobs updated
	if ( !dirty_job_ids.isEmpty() ) {
		ClassAd *rval;
		dprintf( D_FULLDEBUG, "Calling clearDirtyAttrs on %d jobs\n",
				 dirty_job_ids.number() );
		dirty_job_ids.rewind();
		rval = ScheddObj->clearDirtyAttrs( &dirty_job_ids, &errstack );
		if ( rval == NULL ) {
			dprintf(D_ALWAYS, "Failed to notify schedd to clear dirty attributes.  CondorError: %s\n", errstack.getFullText().c_str() );
		}
		delete rval;
	}

	// Wake up jobs that had schedd updates pending and delete job
	// objects that wanted to be deleted
	pendingScheddUpdates.startIterations();

	while ( pendingScheddUpdates.iterate( curr_request ) != 0 ) {

		curr_job = curr_request->m_job;
		curr_job->jobAd->ClearAllDirtyFlags();

		if ( curr_job->deleteFromGridmanager ) {

				// If the Job object wants to delete the job from the
				// schedd but we failed to do so, don't delete the job
				// object yet; wait until we successfully delete the job
				// from the schedd.
			if ( curr_job->deleteFromSchedd == true &&
				 schedd_deletes_complete == false ) {
				continue;
			}

				// If wantRematch is set, send a reschedule now
			if ( curr_job->wantRematch ) {
				send_reschedule = true;
			}
			pendingScheddUpdates.remove( curr_job->procID );
			pendingScheddVacates.remove( curr_job->procID );
			pendingJobStatus.remove( curr_job->procID );
			completedJobStatus.remove( curr_job->procID );
			completedScheddVacates.remove( curr_job->procID );
			delete curr_job;

		} else {
			pendingScheddUpdates.remove( curr_job->procID );

			if ( curr_request->m_notify ) {
				curr_job->SetEvaluateState();
			}
		}

		delete curr_request;
	}

	// Poke objects that wanted to be notified when a schedd update completed
	// successfully (possibly minus deletes)
	int timer_id;
	scheddUpdateNotifications.Rewind();
	while ( scheddUpdateNotifications.Next( timer_id ) ) {
		daemonCore->Reset_Timer( timer_id, 0 );
	}
	scheddUpdateNotifications.Clear();

	if ( send_reschedule == true ) {
		ScheddObj->reschedule();
	}

	// Check if we have any jobs left to manage. If not, exit.
	if ( BaseJob::JobsByProcId.getNumElements() == 0 ) {
		dprintf( D_ALWAYS, "No jobs left, shutting down\n" );
		daemonCore->Send_Signal( daemonCore->getpid(), SIGTERM );
	}

	lastContactSchedd = time(NULL);

	if ( schedd_deletes_complete == false ) {
		error_str = "Problem using DestroyProc to delete jobs!";
		goto contact_schedd_failure;
	}

	scheddFailureCount = 0;

	// For each job that had dirty attributes, re-evaluate the policy
	dirty_job_ids.rewind();
	while ( (job_id_str = dirty_job_ids.next()) != NULL ) {
		StrToProcIdFixMe(job_id_str, job_id);
		if ( BaseJob::JobsByProcId.lookup( job_id, curr_job ) == 0 ) {
			curr_job->EvalPeriodicJobExpr();
		}
	}

dprintf(D_FULLDEBUG,"leaving doContactSchedd()\n");
	return;

 contact_schedd_failure:
	scheddFailureCount++;
	if ( error_str == "" ) {
		error_str = "Failure in doContactSchedd";
	}
	if ( scheddFailureCount >= maxScheddFailures ) {
		dprintf( D_ALWAYS, "%s\n", error_str.c_str() );
		EXCEPT( "Too many failures connecting to schedd!" );
	}
	dprintf( D_ALWAYS, "%s Will retry\n", error_str.c_str() );
	lastContactSchedd = time(NULL);
	RequestContactSchedd();
	return;
}