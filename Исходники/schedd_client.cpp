void
doContactSchedd()
{
	if (command_queue.IsEmpty()) {
		daemonCore->Reset_Timer( contactScheddTid, contact_schedd_interval ); // Come back in a min
		return;
	}

	dprintf(D_FULLDEBUG,"in doContactSchedd\n");

	SchedDRequest * current_command = NULL;

	int error=FALSE;
	std::string error_msg;
	CondorError errstack;
	bool do_reschedule = false;
	int failure_line_num = 0;
	int failure_errno = 0;

	// Try connecting to schedd
	DCSchedd dc_schedd ( ScheddAddr, ScheddPool );
	if (dc_schedd.error() || !dc_schedd.locate()) {
		sprintf( error_msg, "Error locating schedd %s", ScheddAddr );

		dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );

		// If you can't connect return "Failure" on every job request
		command_queue.Rewind();
		while (command_queue.Next(current_command)) {
			if (current_command->status != SchedDRequest::SDCS_NEW)
				continue;

			if (current_command->command == SchedDRequest::SDC_STATUS_CONSTRAINED) {
				const char * result[] = {
					GAHP_RESULT_FAILURE,
					error_msg.c_str(),
					"0"};
				enqueue_result (current_command->request_id, result, 3);
			} else if (current_command->command == SchedDRequest::SDC_SUBMIT_JOB) {
				const char * result[] = {
									GAHP_RESULT_FAILURE,
									NULL,
									error_msg.c_str() };
				enqueue_result (current_command->request_id, result, 3);
			} else if (current_command->command == SchedDRequest::SDC_UPDATE_LEASE) {
				const char * result[] = {
									GAHP_RESULT_FAILURE,
									error_msg.c_str(),
									NULL };
				enqueue_result (current_command->request_id, result, 3);
			} else {
				const char * result[] = {
									GAHP_RESULT_FAILURE,
									error_msg.c_str() };
				enqueue_result (current_command->request_id, result, 2);
			}

			current_command->status = SchedDRequest::SDCS_COMPLETED;
		}
	}

	
	SchedDRequest::schedd_command_type commands [] = {
		SchedDRequest::SDC_REMOVE_JOB,
		SchedDRequest::SDC_HOLD_JOB,
		SchedDRequest::SDC_RELEASE_JOB };

	const char * command_titles [] = {
		"REMOVE_JOB", "HOLD_JOB", "RELEASE_JOB" };

	// REMOVE
	// HOLD
	// RELEASE
	int i=0;
	while (i<3) {
		
		
		StringList id_list;
		SimpleList <SchedDRequest*> this_batch;

		SchedDRequest::schedd_command_type this_command = commands[i];
		const char * this_action = command_titles[i];
		const char * this_reason = NULL;

		dprintf (D_FULLDEBUG, "Processing %s requests\n", this_action);
		
		error = FALSE;

		// Create a batch of commands with the same command type AND the same reason		
		command_queue.Rewind();
		while (command_queue.Next(current_command)) {
			if (current_command->status != SchedDRequest::SDCS_NEW)
				continue;

			if (current_command->command != this_command)
				continue;

			if ((this_reason != NULL) && (strcmp (current_command->reason, this_reason) != 0))
				continue;

			if (this_reason == NULL)
				this_reason = current_command->reason;
				
			char job_id_buff[30];
			sprintf (job_id_buff, "%d.%d",
				current_command->cluster_id,
				current_command->proc_id);
			id_list.append (job_id_buff);

			this_batch.Append (current_command);
		}

		// If we haven't found any....
		if (id_list.isEmpty()) {
			i++;
			continue;	// ... then try the next command
		}

		// Perform the appropriate command on the current batch
		ClassAd * result_ad= NULL;
		if (this_command == SchedDRequest::SDC_REMOVE_JOB)  {
			errstack.clear();
			result_ad=
				dc_schedd.removeJobs (
					&id_list,
					this_reason,
					&errstack);
		} else if (this_command == SchedDRequest::SDC_HOLD_JOB) {
			errstack.clear();
			result_ad=
				dc_schedd.holdJobs (
					&id_list,
					this_reason,
					NULL,
			 		&errstack);
		} else if (this_command == SchedDRequest::SDC_RELEASE_JOB)  {
			errstack.clear();
			result_ad=
				dc_schedd.releaseJobs (
					&id_list,
					this_reason,
					&errstack);
		} else {
			EXCEPT( "Unexpected command type %d in doContactSchedd",
					this_command );
		}

		// Analyze the result ad
		if (!result_ad) {
			error = TRUE;
			sprintf( error_msg, "Error connecting to schedd %s %s: %s",
					 ScheddAddr, dc_schedd.addr(), errstack.getFullText() );
		}
		else {
			result_ad->dPrint (D_FULLDEBUG);
			if ( this_command == SchedDRequest::SDC_RELEASE_JOB ) {
				do_reschedule = true;
			}
		}

		// Go through the batch again, and create responses for each request
		this_batch.Rewind();
		while (this_batch.Next(current_command)) {
			
			// Check the result
			char job_id_buff[30];
			if (result_ad && (error == FALSE)) {
				sprintf (job_id_buff, "job_%d_%d",
					current_command->cluster_id,
					current_command->proc_id);
				
				int remove_result;
				if (result_ad->LookupInteger (job_id_buff, remove_result)) {
					switch (remove_result) {
						case AR_ERROR:
							error = TRUE;
							error_msg = "General Error";
							break;
						case AR_SUCCESS:
							error = FALSE;
							break;
						case AR_NOT_FOUND:
							error = TRUE;
							error_msg = "Job not found";
							break;
						case AR_BAD_STATUS:
							error = TRUE;
							error_msg = "Bad job status";
							break;
						case AR_ALREADY_DONE:
							error = TRUE;
							error_msg = "Already done";
							break;
						case AR_PERMISSION_DENIED:
							error = TRUE;
							error_msg = "Permission denied";
							break;
						default:
							error = TRUE;
							error_msg = "Unknown Result";
					} // hctiws

				} else {
					error_msg = "Unable to get result";
				} // fi lookup result for job
			} // fi error == FALSE

			if (error) {
				dprintf (D_ALWAYS, "Error (operation: %s) %d.%d: %s\n",
						this_action,
						current_command->cluster_id,
						current_command->proc_id,
						error_msg.c_str());

				const char * result[2];
				result[0] = GAHP_RESULT_FAILURE;
				result[1] = error_msg.c_str();

				enqueue_result (current_command->request_id, result, 2);
			} else {
				dprintf (D_ALWAYS, "Succeess (operation: %s) %d.%d\n",
						this_action,
						current_command->cluster_id,
						current_command->proc_id);

				const char * result[2];
				result[0] = GAHP_RESULT_SUCCESS;
				result[1] = NULL;

				enqueue_result (current_command->request_id, result, 2);
			} // fi error

			// Mark the status
			current_command->status = SchedDRequest::SDCS_COMPLETED;
		} // elihw this_batch

		if ( result_ad ) {
			delete result_ad;
		}
	}

	dprintf (D_FULLDEBUG, "Processing JOB_STAGE_IN requests\n");
	

	// JOB_STAGE_IN
	int MAX_BATCH_SIZE=1; // This should be a config param

	SimpleList <SchedDRequest*> stage_in_batch;
	do {
		stage_in_batch.Clear();

		command_queue.Rewind();
		while (command_queue.Next(current_command)) {

			if (current_command->status != SchedDRequest::SDCS_NEW)
				continue;

			if (current_command->command != SchedDRequest::SDC_JOB_STAGE_IN)
				continue;

			dprintf (D_ALWAYS, "Adding %d.%d to STAGE_IN batch\n", 
					 current_command->cluster_id,
					 current_command->proc_id);

			stage_in_batch.Append (current_command);
			if (stage_in_batch.Number() >= MAX_BATCH_SIZE)
				break;
		}

		if (stage_in_batch.Number() > 0) {
			ClassAd ** array = new ClassAd*[stage_in_batch.Number()];
			i=0;
			stage_in_batch.Rewind();
			while (stage_in_batch.Next(current_command)) {
				array[i++] = current_command->classad;
			}

			error = FALSE;
			errstack.clear();
			if (!dc_schedd.spoolJobFiles( stage_in_batch.Number(),
										  array,
										  &errstack )) {
				error = TRUE;
				sprintf( error_msg, "Error sending files to schedd %s: %s", ScheddAddr, errstack.getFullText() );
				dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
			}
			delete [] array;
  
			stage_in_batch.Rewind();
			while (stage_in_batch.Next(current_command)) {
				current_command->status = SchedDRequest::SDCS_COMPLETED;

				if (error) {
					const char * result[] = {
						GAHP_RESULT_FAILURE,
						error_msg.c_str() };
					enqueue_result (current_command->request_id, result, 2);

				} else {
					const char * result[] = {
						GAHP_RESULT_SUCCESS,
						NULL };
					enqueue_result (current_command->request_id, result, 2);
				}
			} // elihw (command_queue)
		} // fi has STAGE_IN requests
	} while (stage_in_batch.Number() > 0);

	dprintf (D_FULLDEBUG, "Processing JOB_STAGE_OUT requests\n");
	

	// JOB_STAGE_OUT
	SimpleList <SchedDRequest*> stage_out_batch;

	command_queue.Rewind();
	while (command_queue.Next(current_command)) {

		if (current_command->status != SchedDRequest::SDCS_NEW)
			continue;

		if (current_command->command != SchedDRequest::SDC_JOB_STAGE_OUT)
			continue;


		stage_out_batch.Append (current_command);
	}

	if (stage_out_batch.Number() > 0) {
		std::string constraint = "";
		stage_out_batch.Rewind();
		int jobsexpected = stage_out_batch.Number();
		while (stage_out_batch.Next(current_command)) {
			sprintf_cat( constraint, "(ClusterId==%d&&ProcId==%d)||",
									current_command->cluster_id,
									current_command->proc_id );
		}
		constraint += "False";

		error = FALSE;
		errstack.clear();
		int jobssent;
		if (!dc_schedd.receiveJobSandbox( constraint.c_str(),
										  &errstack, &jobssent )) {
			error = TRUE;
			sprintf( error_msg, "Error receiving files from schedd %s: %s",
							   ScheddAddr, errstack.getFullText() );
			dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
		}

		if(error == FALSE && jobssent != jobsexpected) {
			error = TRUE;
			sprintf( error_msg, "Schedd %s didn't send expected files",
					 ScheddAddr );
			dprintf (D_ALWAYS, "Transfered files for %d jobs but got files for %d jobs. (Schedd %s with contraint %s\n", jobsexpected, jobssent, ScheddAddr, constraint.c_str());
		}
  
		stage_out_batch.Rewind();
		while (stage_out_batch.Next(current_command)) {
			current_command->status = SchedDRequest::SDCS_COMPLETED;

			if (error) {
				const char * result[] = {
								GAHP_RESULT_FAILURE,
								error_msg.c_str() };
				enqueue_result (current_command->request_id, result, 2);

			} else {
				const char * result[] = {
										GAHP_RESULT_SUCCESS,
										NULL };
				enqueue_result (current_command->request_id, result, 2);
			}
		} // elihw (command_queue)
	} // fi has STAGE_OUT requests


	dprintf (D_FULLDEBUG, "Processing JOB_REFRESH_PROXY requests\n");

	CondorVersionInfo ver_info(dc_schedd.version());
	bool delegate_credential;
	if ( ver_info.built_since_version(6,7,19) &&
		 param_boolean( "DELEGATE_JOB_GSI_CREDENTIALS", true ) ) {
		delegate_credential = true;
	} else {
		delegate_credential = false;
	}

	// JOB_REFRESH_PROXY
	command_queue.Rewind();
	while (command_queue.Next(current_command)) {

		if (current_command->status != SchedDRequest::SDCS_NEW)
			continue;

		if (current_command->command != SchedDRequest::SDC_JOB_REFRESH_PROXY)
			continue;

		time_t expiration_time = GetDesiredDelegatedJobCredentialExpiration(current_command->classad);
		time_t result_expiration_time = 0;

		bool result;
		errstack.clear();
		if ( delegate_credential ) {
			result = dc_schedd.delegateGSIcredential( 
												current_command->cluster_id,
												current_command->proc_id,
												current_command->proxy_file,
												expiration_time,
												&result_expiration_time,
												&errstack );

				// Currently, we do not propagate the actual resulting
				// expiration time back to the gridmanager.  We
				// probably should.
		} else {
			result = dc_schedd.updateGSIcredential( 
												current_command->cluster_id,
												current_command->proc_id,
												current_command->proxy_file,
												&errstack );
		}

		current_command->status = SchedDRequest::SDCS_COMPLETED;

		if (result == false) {
			sprintf( error_msg, "Error refreshing proxy to schedd %s: %s",
					 ScheddAddr, errstack.getFullText() );
			dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );

			const char * result_to_queue[] = {
				GAHP_RESULT_FAILURE,
				error_msg.c_str() };
			enqueue_result (current_command->request_id, result_to_queue, 2);

		} else {
			const char * result_to_queue[] = {
				GAHP_RESULT_SUCCESS,
				NULL };
			enqueue_result (current_command->request_id, result_to_queue, 2);
		}

	}


	// Now do all the QMGMT transactions
	error = FALSE;

	// Try connecting to the queue
	Qmgr_connection * qmgr_connection;
	
	if ((qmgr_connection = ConnectQ(dc_schedd.addr(), QMGMT_TIMEOUT, false, NULL, NULL, dc_schedd.version() )) == NULL) {
		error = TRUE;
		sprintf( error_msg, "Error connecting to schedd %s", ScheddAddr );
		dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
	} else {
		errno = 0;
		AbortTransaction(); // Just so we can call BeginTransaction() in the loop
		if ( errno == ETIMEDOUT ) {
			failure_line_num = __LINE__;
			failure_errno = errno;
			goto contact_schedd_disconnect;
		}
	}


	dprintf (D_FULLDEBUG, "Processing UPDATE_CONSTRAINED/UDATE_JOB requests\n");
	
	// UPDATE_CONSTRAINED
	// UDATE_JOB
	command_queue.Rewind();
	while (command_queue.Next(current_command)) {
		
		if (current_command->status != SchedDRequest::SDCS_NEW)
			continue;

		if ((current_command->command != SchedDRequest::SDC_UPDATE_CONSTRAINED) &&
			(current_command->command != SchedDRequest::SDC_UPDATE_JOB))
			continue;

		if (qmgr_connection == NULL)
			goto update_report_result;
		
		error = FALSE;
		errno = 0;
		BeginTransaction();
		if ( errno == ETIMEDOUT ) {
			failure_line_num = __LINE__;
			failure_errno = errno;
			goto contact_schedd_disconnect;
		}

		current_command->classad->ResetExpr();
		ExprTree *tree;
		const char *lhstr, *rhstr;
		while( current_command->classad->NextExpr(lhstr, tree) ) {

			rhstr = ExprTreeToString( tree );
			if( !lhstr || !rhstr) {
				sprintf( error_msg, "ERROR: ClassAd problem in Updating by constraint %s",
												 current_command->constraint );
				dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
				error = TRUE;
			} else {
				if (current_command->command == SchedDRequest::SDC_UPDATE_CONSTRAINED) {
					if( SetAttributeByConstraint(current_command->constraint,
												lhstr,
												rhstr) == -1 ) {
						if ( errno == ETIMEDOUT ) {
							failure_line_num = __LINE__;
							failure_errno = errno;
							goto contact_schedd_disconnect;
						}
						sprintf( error_msg, "ERROR: Failed (errno=%d) to SetAttributeByConstraint %s=%s for constraint %s",
									errno, lhstr, rhstr, current_command->constraint );
						dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
						error = TRUE;
					}
				} else if (current_command->command == SchedDRequest::SDC_UPDATE_JOB) {
					if( SetAttribute(current_command->cluster_id,
											current_command->proc_id,
											lhstr,
											rhstr) == -1 ) {
						if ( errno == ETIMEDOUT ) {
							failure_line_num = __LINE__;
							failure_errno = errno;
							goto contact_schedd_disconnect;
						}
						sprintf( error_msg, "ERROR: Failed to SetAttribute() %s=%s for job %d.%d",
										 lhstr, rhstr, current_command->cluster_id,  current_command->proc_id);
						dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
						error = TRUE;
					}
				}
			}

			if (error)
				break;
		} // elihw classad

update_report_result:
		if (error) {
			const char * result[] = {
				GAHP_RESULT_FAILURE,
				error_msg.c_str() };


			//RemoteCommitTransaction();
			enqueue_result (current_command->request_id, result, 2);
			current_command->status = SchedDRequest::SDCS_COMPLETED;
			if ( qmgr_connection != NULL ) {
				errno = 0;
				AbortTransaction();
				if ( errno == ETIMEDOUT ) {
					failure_line_num = __LINE__;
					failure_errno = errno;
					goto contact_schedd_disconnect;
				}
			}
		} else {
			if ( RemoteCommitTransaction() < 0 ) {
				failure_line_num = __LINE__;
				failure_errno = errno;
				goto contact_schedd_disconnect;
			}
			const char * result[] = {
				GAHP_RESULT_SUCCESS,
				NULL };
			enqueue_result (current_command->request_id, result, 2);
			current_command->status = SchedDRequest::SDCS_COMPLETED;
		} // fi

	} // elihw

	
	dprintf (D_FULLDEBUG, "Processing UPDATE_LEASE requests\n");

	// UPDATE_LEASE
	command_queue.Rewind();
	while (command_queue.Next(current_command)) {
		
		error = FALSE;

		if (current_command->status != SchedDRequest::SDCS_NEW)
			continue;

		if (current_command->command != SchedDRequest::SDC_UPDATE_LEASE)
			continue;

		std::string success_job_ids="";
		if (qmgr_connection == NULL) {
			sprintf( error_msg, "Error connecting to schedd %s", ScheddAddr );
			error = TRUE;
		} else {
			error = FALSE;
			errno = 0;
			BeginTransaction();
			if ( errno == ETIMEDOUT ) {
				failure_line_num = __LINE__;
				failure_errno = errno;
				goto contact_schedd_disconnect;
			}
		
			for (i=0; i<current_command->num_jobs; i++) {
			
				time_t time_now = time(NULL);
				int duration = 
					current_command->expirations[i].expiration - time_now;

				dprintf (D_FULLDEBUG, 
						 "Job %d.%d SetTimerAttribute=%d\n",
						 current_command->expirations[i].cluster,
						 current_command->expirations[i].proc,
						 duration);
		
				if (SetTimerAttribute (current_command->expirations[i].cluster,
									   current_command->expirations[i].proc,
									   ATTR_TIMER_REMOVE_CHECK,
									   duration) < 0) {

					if ( errno == ETIMEDOUT ) {
						failure_line_num = __LINE__;
						failure_errno = errno;
						goto contact_schedd_disconnect;
					}
					dprintf (D_ALWAYS, 
							 "Unable to SetTimerAttribute(%d, %d), errno=%d\n",
							 current_command->expirations[i].cluster,
							 current_command->expirations[i].proc,
							 errno);
						 
				} else {
						// Append job id to the result line
					if (success_job_ids.length() > 0)
						success_job_ids += ",";

					sprintf_cat( success_job_ids,
						"%d.%d",
						current_command->expirations[i].cluster,
						current_command->expirations[i].proc);
				}
			} //rof jobs for request
		} // fi error


		if (error) {
			const char * result[] = {
				GAHP_RESULT_FAILURE,
				error_msg.c_str(),
				NULL
			};


			//RemoteCommitTransaction();
			enqueue_result (current_command->request_id, result, 3);
			current_command->status = SchedDRequest::SDCS_COMPLETED;
			if ( qmgr_connection != NULL ) {
				errno = 0;
				AbortTransaction();
				if ( errno == ETIMEDOUT ) {
					failure_line_num = __LINE__;
					failure_errno = errno;
					goto contact_schedd_disconnect;
				}
			}
		} else {
			if ( RemoteCommitTransaction() < 0 ) {
				failure_line_num = __LINE__;
				failure_errno = errno;
				goto contact_schedd_disconnect;
			}
			const char * result[] = {
				GAHP_RESULT_SUCCESS,
				NULL,
				success_job_ids.length()?success_job_ids.c_str():NULL
			};
			enqueue_result (current_command->request_id, result, 3);
			current_command->status = SchedDRequest::SDCS_COMPLETED;
		} // fi

	} // elihw UPDATE_LEASE requests

	dprintf (D_FULLDEBUG, "Processing SUBMIT_JOB requests\n");

	// SUBMIT_JOB
	command_queue.Rewind();
	while (command_queue.Next(current_command)) {

		if (current_command->status != SchedDRequest::SDCS_NEW)
			continue;

		if (current_command->command != SchedDRequest::SDC_SUBMIT_JOB)
			continue;

		int ClusterId = -1;
		int ProcId = -1;

		if (qmgr_connection == NULL) {
			error = TRUE;
			goto submit_report_result;
		}

		errno = 0;
		BeginTransaction();
		if ( errno == ETIMEDOUT ) {
			failure_line_num = __LINE__;
			failure_errno = errno;
			goto contact_schedd_disconnect;
		}
		error = FALSE;

		if ((ClusterId = NewCluster()) >= 0) {
			ProcId = NewProc (ClusterId);
		}
		if ( errno == ETIMEDOUT ) {
			failure_line_num = __LINE__;
			failure_errno = errno;
			goto contact_schedd_disconnect;
		}

		if ( ClusterId < 0 ) {
			error = TRUE;
			error_msg = "Unable to create a new job cluster";
			dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
		} else if ( ProcId < 0 ) {
			error = TRUE;
			error_msg = "Unable to create a new job proc";
			dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
		}
		if ( ClusterId == -2 || ProcId == -2 ) {
			error = TRUE;
			error_msg =
				"Number of submitted jobs would exceed MAX_JOBS_SUBMITTED\n";
			dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
		}


		// Adjust the argument/environment syntax based on the version
		// of the schedd we are talking to.

		if( error == FALSE) {
			CondorVersionInfo version_info(dc_schedd.version());
			ArgList arglist;
			MyString arg_error_msg;
			Env env_obj;
			MyString env_error_msg;

			if(!arglist.AppendArgsFromClassAd(current_command->classad,&arg_error_msg) ||
		   !	arglist.InsertArgsIntoClassAd(current_command->classad,&version_info,&arg_error_msg))
			{
				sprintf( error_msg,
						"ERROR: ClassAd problem in converting arguments to syntax "
						"for schedd (version=%s): %s\n",
						dc_schedd.version() ? dc_schedd.version() : "NULL",
						arg_error_msg.Value());
				dprintf( D_ALWAYS,"%s\n", error_msg.c_str() );
				error = TRUE;
			}	

			if(!env_obj.MergeFrom(current_command->classad,&env_error_msg) ||
			   !env_obj.InsertEnvIntoClassAd(current_command->classad,&env_error_msg,NULL,&version_info))
			{
				sprintf( error_msg,
						"ERROR: Failed to convert environment to target syntax"
						" for schedd (version %s): %s\n",
						dc_schedd.version() ? dc_schedd.version() : "NULL",
						env_error_msg.Value());
				dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
				error = TRUE;
			}
		}

		if( error == FALSE ) {
				// See the comment in the function body of ExpandInputFileList
				// for an explanation of what is going on here.
			MyString transfer_input_error_msg;
			if( !FileTransfer::ExpandInputFileList( current_command->classad, transfer_input_error_msg ) ) {
				dprintf( D_ALWAYS, "%s\n", transfer_input_error_msg.Value() );
				error = TRUE;
			}
		}

		if ( error == FALSE ) {
			current_command->classad->Assign(ATTR_CLUSTER_ID, ClusterId);
			current_command->classad->Assign(ATTR_PROC_ID, ProcId);

			// Special case for the job lease
			int expire_time;
			if ( current_command->classad->LookupInteger( ATTR_TIMER_REMOVE_CHECK, expire_time ) ) {
				if ( SetTimerAttribute( ClusterId, ProcId,
										ATTR_TIMER_REMOVE_CHECK,
										expire_time - time(NULL) ) == -1 ) {
					if ( errno == ETIMEDOUT ) {
						failure_line_num = __LINE__;
						failure_errno = errno;
						goto contact_schedd_disconnect;
					}
					sprintf( error_msg, "ERROR: Failed to SetTimerAttribute %s=%ld for job %d.%d",
							 ATTR_TIMER_REMOVE_CHECK, expire_time - time(NULL), ClusterId, ProcId );
					dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
					error = TRUE;
					goto submit_report_result;
				}
				current_command->classad->Delete( ATTR_TIMER_REMOVE_CHECK );
			}

			// Set all the classad attribute on the remote classad
			current_command->classad->ResetExpr();
			ExprTree *tree;
			const char *lhstr, *rhstr;
			while( current_command->classad->NextExpr(lhstr, tree) ) {

				rhstr = ExprTreeToString( tree );
				if( !lhstr || !rhstr) {
					sprintf( error_msg, "ERROR: ClassAd problem in Updating by constraint %s",
												 current_command->constraint );
					dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
					error = TRUE;
				} else if( SetAttribute (ClusterId, ProcId,
											lhstr,
											rhstr) == -1 ) {
					if ( errno == ETIMEDOUT ) {
						failure_line_num = __LINE__;
						failure_errno = errno;
						goto contact_schedd_disconnect;
					}
					sprintf( error_msg, "ERROR: Failed to SetAttribute %s=%s for job %d.%d",
									 lhstr, rhstr, ClusterId, ProcId );
					dprintf( D_ALWAYS, "%s\n", error_msg.c_str() );
					error = TRUE;
				}

				if (error) break;
			} // elihw classad
		} // fi error==FALSE

submit_report_result:
		char job_id_buff[30];
		sprintf (job_id_buff, "%d.%d", ClusterId, ProcId);

		if (error) {
			const char * result[] = {
								GAHP_RESULT_FAILURE,
								job_id_buff,
								error_msg.c_str() };
			enqueue_result (current_command->request_id, result, 3);
			if ( qmgr_connection != NULL ) {
				errno = 0;
				AbortTransaction();
				if ( errno == ETIMEDOUT ) {
					failure_line_num = __LINE__;
					failure_errno = errno;
					goto contact_schedd_disconnect;
				}
			}
			current_command->status = SchedDRequest::SDCS_COMPLETED;
		} else {
			if ( RemoteCommitTransaction() < 0 ) {
				failure_line_num = __LINE__;
				failure_errno = errno;
				goto contact_schedd_disconnect;
			}
			const char * result[] = {
									GAHP_RESULT_SUCCESS,
									job_id_buff,
									NULL };
			enqueue_result (current_command->request_id, result, 3);
			current_command->status = SchedDRequest::SDCS_COMPLETED;
		}
	} // elihw


	dprintf (D_FULLDEBUG, "Processing STATUS_CONSTRAINED requests\n");
		
	// STATUS_CONSTRAINED
	command_queue.Rewind();
	while (command_queue.Next(current_command)) {

		if (current_command->status != SchedDRequest::SDCS_NEW)
			continue;

		if (current_command->command != SchedDRequest::SDC_STATUS_CONSTRAINED)
			continue;

		if (qmgr_connection != NULL) {
			SimpleList <MyString *> matching_ads;

			error = FALSE;
			
			ClassAd *next_ad;
			ClassAdList adlist;
				// Only use GetAllJobsByConstraint if remote schedd is
				// 6.9.5 or newer.  Previous versions either did not
				// support this call, or they closed the Qmgmt connection
				// as a side-effect of this call.
			if( ver_info.built_since_version(6,9,5) ) {
				dprintf( D_FULLDEBUG, "Calling GetAllJobsByConstraint(%s)\n",
						 current_command->constraint );
					// NOTE: this could be made more efficient if we knew
					// the list of attributes to query.  For lack of that,
					// we just get all attributes.
				GetAllJobsByConstraint( current_command->constraint, "", adlist);
			}
			else {
					// This is the old latency-prone method.
				dprintf( D_FULLDEBUG, "Calling GetNextJobByConstraint(%s)\n",
						 current_command->constraint );
				next_ad = GetNextJobByConstraint( current_command->constraint, 1 );
				while( next_ad != NULL ) {
					adlist.Insert( next_ad );
					next_ad = GetNextJobByConstraint( current_command->constraint, 0 );
				}
			}

				// NOTE: ClassAdList will deallocate the ClassAds in it

			adlist.Rewind();
			while( (next_ad=adlist.Next()) ) {
				MyString * da_buffer = new MyString();	// Use a ptr to avoid excessive copying
				if ( useXMLClassads ) {
					ClassAdXMLUnparser unparser;
					unparser.SetUseCompactSpacing(true);
					unparser.Unparse (next_ad, *da_buffer);
				} else {
					NewClassAdUnparser unparser;
					unparser.SetUseCompactSpacing(true);
					unparser.Unparse (next_ad, *da_buffer);
				}
				matching_ads.Append (da_buffer);
			}
			if ( errno == ETIMEDOUT ) {
				failure_line_num = __LINE__;
				failure_errno = errno;
				goto contact_schedd_disconnect;
			}

			// now output this list of classads into a result
			const char ** result  = new const char* [matching_ads.Length() + 3];

			std::string _ad_count;
			sprintf( _ad_count, "%d", matching_ads.Length() );

			int count=0;
			result[count++] = GAHP_RESULT_SUCCESS;
			result[count++] = NULL;
			result[count++] = _ad_count.c_str();

			MyString *next_string;
			matching_ads.Rewind();
			while (matching_ads.Next(next_string)) {
				result[count++] = next_string->Value();
			}

			enqueue_result (current_command->request_id, result, count);
			current_command->status = SchedDRequest::SDCS_COMPLETED;

			// Cleanup
			matching_ads.Rewind();
			while (matching_ads.Next(next_string)) {
				delete next_string;
			}
			//CommitTransaction();
			delete [] result;
		}
		else {
			const char * result[] = {
				GAHP_RESULT_FAILURE,
				error_msg.c_str(),
				"0" };
			//RemoteCommitTransaction();
			enqueue_result (current_command->request_id, result, 3);
			current_command->status = SchedDRequest::SDCS_COMPLETED;
		}
	}	//elihw

	
 contact_schedd_disconnect:
	if ( qmgr_connection != NULL ) {
		DisconnectQ (qmgr_connection, FALSE);
	}

	if ( failure_line_num ) {
			// We had an error talking to the schedd. Take all of our
			// incomplete commands and mark them as failed.
			// TODO Consider retrying these commands, rather than
			//   immediately marking them as failed.
		if ( failure_errno == ETIMEDOUT ) {
			dprintf( D_ALWAYS, "Timed out talking to schedd at line %d in "
					 "doContactSchedd()\n", failure_line_num );
			sprintf( error_msg, "Timed out talking to schedd" );
		} else {
			dprintf( D_ALWAYS, "Error talking to schedd at line %d in "
					 "doContactSchedd(), errno=%d (%s)\n", failure_line_num,
					 failure_errno, strerror(failure_errno) );
			sprintf( error_msg, "Error talking to schedd" );
		}
		command_queue.Rewind();
		while (command_queue.Next(current_command)) {
			if ( current_command->status != SchedDRequest::SDCS_NEW ) {
				continue;
			}
			switch( current_command->command ) {
			case SchedDRequest::SDC_UPDATE_JOB:
			case SchedDRequest::SDC_UPDATE_CONSTRAINED:
			{
				const char *result[2] = { GAHP_RESULT_FAILURE, error_msg.c_str() };
				enqueue_result (current_command->request_id, result, 2);
				current_command->status = SchedDRequest::SDCS_COMPLETED;
			}
				break;
			case SchedDRequest::SDC_UPDATE_LEASE:
			{
				const char *result[3] = { GAHP_RESULT_FAILURE, error_msg.c_str(), NULL };
				enqueue_result (current_command->request_id, result, 3);
				current_command->status = SchedDRequest::SDCS_COMPLETED;
			}
				break;
			case SchedDRequest::SDC_SUBMIT_JOB:
			{
				const char *result[3] = { GAHP_RESULT_FAILURE, "-1.-1", error_msg.c_str() };
				enqueue_result (current_command->request_id, result, 3);
				current_command->status = SchedDRequest::SDCS_COMPLETED;
			}
				break;
			case SchedDRequest::SDC_STATUS_CONSTRAINED:
			{
				const char *result[3] = { GAHP_RESULT_FAILURE, error_msg.c_str(), "0" };
				enqueue_result (current_command->request_id, result, 3);
				current_command->status = SchedDRequest::SDCS_COMPLETED;
			}
				break;
			default:
					// Do nothing
				;
			}
		}
	}

	if ( do_reschedule ) {
		dc_schedd.reschedule();
	}

		// Write all of our results to our parent.
	flush_results();

	dprintf (D_FULLDEBUG, "Finishing doContactSchedd()\n");

	// Clean up the list
	command_queue.Rewind();
	while (command_queue.Next(current_command)) {
		if (current_command->status == SchedDRequest::SDCS_COMPLETED) {
			command_queue.DeleteCurrent();
			delete current_command;
		}
	}

	// Come back soon..
	// QUESTION: Should this always be a fixed time period?
	daemonCore->Reset_Timer( contactScheddTid, contact_schedd_interval );
}