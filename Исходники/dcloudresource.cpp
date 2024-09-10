DCloudResource::BatchStatusResult DCloudResource::StartBatchStatus()
{
	ASSERT(status_gahp);

	StringList instance_ids;
	StringList statuses;
	const char *instance_id;
	const char *status;

	int rc = status_gahp->dcloud_status_all( ResourceName(), m_username,
											 m_password, instance_ids,
											 statuses );
	if ( rc == GAHPCLIENT_COMMAND_PENDING ) {
		return BSR_PENDING;
	}
	if ( rc != 0 ) {
		dprintf( D_ALWAYS, "Error attempting a Deltacloud batch status query: %s\n", status_gahp->getErrorString() );
		return BSR_ERROR;
	}

	DCloudJob *next_job;
	List<DCloudJob> my_jobs;
	registeredJobs.Rewind();
	while ( (next_job = (DCloudJob *)registeredJobs.Next()) ) {
		my_jobs.Insert( next_job );
	}

	instance_ids.rewind();
	statuses.rewind();
	while ( (instance_id = instance_ids.next()) &&
			(status = statuses.next()) ) {

		MyString hashname;
		hashname.formatstr( "%s#%s", ResourceName(), instance_id );
		DCloudJob *job = NULL;

		// TODO We can get rid of the hashtable.
		rc = DCloudJob::JobsByInstanceId.lookup(
										HashKey( hashname.Value() ), job );
		if ( rc != 0 ) {
			// Job not found. Probably okay; we might see jobs
			// submitted via other means, or jobs we've abandoned.
			dprintf( D_FULLDEBUG, "Job %s on remote host is unknown. Skipping.\n", hashname.Value() );
			continue;
		}
		ASSERT( job );

		job->StatusUpdate( status );

		my_jobs.Delete( job );
	}

	my_jobs.Rewind();
	while ( (next_job = my_jobs.Next()) ) {
		next_job->StatusUpdate( NULL );
	}

	return BSR_DONE;
}