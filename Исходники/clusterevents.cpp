Value ClusterEvents::NotificationSentToAllUsersAPIHandler(const MessageOrigin::Ptr& origin, const Dictionary::Ptr& params)
{
	Endpoint::Ptr endpoint = origin->FromClient->GetEndpoint();

	if (!endpoint) {
		Log(LogNotice, "ClusterEvents")
			<< "Discarding 'sent notification to all users' message from '" << origin->FromClient->GetIdentity() << "': Invalid endpoint origin (client not allowed).";
		return Empty;
	}

	Host::Ptr host = Host::GetByName(params->Get("host"));

	if (!host)
		return Empty;

	Checkable::Ptr checkable;

	if (params->Contains("service"))
		checkable = host->GetServiceByShortName(params->Get("service"));
	else
		checkable = host;

	if (!checkable)
		return Empty;

	if (origin->FromZone && origin->FromZone != Zone::GetLocalZone()) {
		Log(LogNotice, "ClusterEvents")
			<< "Discarding 'sent notification to all users' message for checkable '" << checkable->GetName()
			<< "' from '" << origin->FromClient->GetIdentity() << "': Unauthorized access.";
		return Empty;
	}

	CheckResult::Ptr cr;
	Array::Ptr vperf;

	if (params->Contains("cr")) {
		cr = new CheckResult();
		Dictionary::Ptr vcr = params->Get("cr");

		if (vcr && vcr->Contains("performance_data")) {
			vperf = vcr->Get("performance_data");

			if (vperf)
				vcr->Remove("performance_data");

			Deserialize(cr, vcr, true);
		}
	}

	NotificationType type = static_cast<NotificationType>(static_cast<int>(params->Get("type")));
	String author = params->Get("author");
	String text = params->Get("text");

	Notification::Ptr notification = Notification::GetByName(params->Get("notification"));

	if (!notification)
		return Empty;

	Array::Ptr ausers = params->Get("users");

	if (!ausers)
		return Empty;

	std::set<User::Ptr> users;

	{
		ObjectLock olock(ausers);
		for (const String& auser : ausers) {
			User::Ptr user = User::GetByName(auser);

			if (!user)
				continue;

			users.insert(user);
		}
	}

	notification->SetLastNotification(params->Get("last_notification"));
	notification->SetNextNotification(params->Get("next_notification"));
	notification->SetNotificationNumber(params->Get("notification_number"));
	notification->SetLastProblemNotification(params->Get("last_problem_notification"));
	notification->SetNoMoreNotifications(params->Get("no_more_notifications"));

	ArrayData notifiedProblemUsers;
	for (const User::Ptr& user : users) {
		notifiedProblemUsers.push_back(user->GetName());
	}

	notification->SetNotifiedProblemUsers(new Array(std::move(notifiedProblemUsers)));

	Checkable::OnNotificationSentToAllUsers(notification, checkable, users, type, cr, author, text, origin);

	return Empty;
}