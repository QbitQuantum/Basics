bool RosterResponder::handleSetRequest(const Swift::JID& from, const Swift::JID& to, const std::string& id, boost::shared_ptr<Swift::RosterPayload> payload) {
	sendResponse(from, id, boost::shared_ptr<RosterPayload>(new RosterPayload()));

	User *user = m_userManager->getUser(from.toBare().toString());
	if (!user) {
		LOG4CXX_WARN(logger, from.toBare().toString() << ": User is not logged in");
		return true;
	}

	if (payload->getItems().size() == 0) {
		LOG4CXX_WARN(logger, from.toBare().toString() << ": Roster push with no item");
		return true;
	}

	Swift::RosterItemPayload item = payload->getItems()[0];

	if (item.getJID().getNode().empty()) {
		return true;
	}

	Buddy *buddy = user->getRosterManager()->getBuddy(Buddy::JIDToLegacyName(item.getJID()));
	if (buddy) {
		if (item.getSubscription() == Swift::RosterItemPayload::Remove) {
			LOG4CXX_INFO(logger, from.toBare().toString() << ": Removing buddy " << buddy->getName());
			onBuddyRemoved(buddy);

			// send roster push here
			Swift::SetRosterRequest::ref request = Swift::SetRosterRequest::create(payload, user->getJID().toBare(), user->getComponent()->getIQRouter());
			request->send();
		}
		else {
			LOG4CXX_INFO(logger, from.toBare().toString() << ": Updating buddy " << buddy->getName());
			onBuddyUpdated(buddy, item);
		}
	}
	else if (item.getSubscription() != Swift::RosterItemPayload::Remove) {
		// Roster push for this new buddy is sent by RosterManager
		BuddyInfo buddyInfo;
		buddyInfo.id = -1;
		buddyInfo.alias = item.getName();
		buddyInfo.legacyName = Buddy::JIDToLegacyName(item.getJID());
		buddyInfo.subscription = "both";
		buddyInfo.flags = Buddy::buddyFlagsFromJID(item.getJID());
		LOG4CXX_INFO(logger, from.toBare().toString() << ": Adding buddy " << buddyInfo.legacyName);

		buddy = user->getComponent()->getFactory()->createBuddy(user->getRosterManager(), buddyInfo);
		user->getRosterManager()->setBuddy(buddy);
		onBuddyAdded(buddy, item);
	}

	return true;
}