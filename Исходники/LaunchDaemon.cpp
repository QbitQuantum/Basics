void
LaunchDaemon::_AddJob(Target* target, bool service, BMessage& message)
{
	BString name = message.GetString("name");
	if (name.IsEmpty()) {
		// Invalid job description
		return;
	}
	name.ToLower();

	Job* job = FindJob(name);
	if (job == NULL) {
		job = new (std::nothrow) Job(name);
		if (job == NULL)
			return;

		job->SetService(service);
		job->SetCreateDefaultPort(service);
		job->SetTarget(target);
	}

	if (message.HasBool("disabled"))
		job->SetEnabled(!message.GetBool("disabled", !job->IsEnabled()));

	if (message.HasBool("legacy"))
		job->SetCreateDefaultPort(!message.GetBool("legacy", !service));

	_SetCondition(job, message);
	_SetEvent(job, message);
	_SetEnvironment(job, message);

	BMessage portMessage;
	for (int32 index = 0;
			message.FindMessage("port", index, &portMessage) == B_OK; index++) {
		job->AddPort(portMessage);
	}

	if (message.HasString("launch")) {
		job->Arguments().MakeEmpty();

		const char* argument;
		for (int32 index = 0; message.FindString("launch", index, &argument)
				== B_OK; index++) {
			job->AddArgument(argument);
		}
	}

	const char* requirement;
	for (int32 index = 0;
			message.FindString("requires", index, &requirement) == B_OK;
			index++) {
		job->AddRequirement(requirement);
	}
	if (fInitTarget != NULL)
		job->AddRequirement(fInitTarget->Name());

	fJobs.insert(std::make_pair(job->Title(), job));
}