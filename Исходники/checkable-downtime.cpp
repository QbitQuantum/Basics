void Checkable::RemoveDowntime(const String& id, bool cancelled, const MessageOrigin::Ptr& origin)
{
	Checkable::Ptr owner = GetOwnerByDowntimeID(id);

	if (!owner)
		return;

	Dictionary::Ptr downtimes = owner->GetDowntimes();

	Downtime::Ptr downtime = downtimes->Get(id);

	if (!downtime)
		return;

	int legacy_id = downtime->GetLegacyId();

	String config_owner = downtime->GetConfigOwner();

	if (!config_owner.IsEmpty()) {
		Log(LogWarning, "Checkable")
		    << "Cannot remove downtime with ID '" << legacy_id << "'. It is owned by scheduled downtime object '" << config_owner << "'";
		return;
	}

	downtimes->Remove(id);

	{
		boost::mutex::scoped_lock lock(l_DowntimeMutex);
		l_LegacyDowntimesCache.erase(legacy_id);
		l_DowntimesCache.erase(id);
	}

	downtime->SetWasCancelled(cancelled);

	Log(LogNotice, "Checkable")
	    << "Removed downtime with ID '" << downtime->GetLegacyId() << "' from service '" << owner->GetName() << "'.";

	OnDowntimeRemoved(owner, downtime, origin);
}