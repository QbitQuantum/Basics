void ReplayProvider::OnFileSystemChange(wxFileSystemWatcherEvent& event)
{
	wxLogDebug(event.ToString());
	if (!event.GetPath().GetExt().IsSameAs("replay", false))
		return;

	if (event.GetChangeType() & wxFSW_EVENT_CREATE)
	{
		Replay* existingReplay = FindReplay(event.GetPath().GetFullPath());
		if (existingReplay) // Replay is already in list
			return;

		// Give rocket league some time to write the file
		wxMilliSleep(500);

		// Add new file
		Replay::Ptr ri(new Replay(event.GetPath().GetFullPath()));
		replay.push_back(ri);

		if (wxConfig::Get()->ReadBool("AutoUpload", false))
		{
			TransferManager::Get().Upload(ri);
		}

		wxCommandEvent evt(wxEVT_REPLAY_ADDED);
		evt.SetInt(replay.size() - 1);
		evt.SetEventObject(this);
		GetRoot()->ProcessEvent(evt);
	}
	else if (event.GetChangeType() & wxFSW_EVENT_DELETE)
	{
		// Find replay and remove it
		size_t index = 0;
		wxString changePath = event.GetPath().GetFullPath();

		for (auto replayIT = replay.begin(); replayIT != replay.end(); ++replayIT, ++index)
		{
			if ((*replayIT)->GetFileName().IsSameAs(changePath, false))
			{
				replay.erase(replayIT);
				break;
			}
		}

		wxCommandEvent evt(wxEVT_REPLAY_REMOVED);
		evt.SetInt(index);
		evt.SetEventObject(this);
		GetRoot()->ProcessEvent(evt);
	}
	else if (event.GetChangeType() & wxFSW_EVENT_RENAME)
	{
		wxString changePath = event.GetPath().GetFullPath();

		// Find replay and update filename
		for (auto replayIT = replay.begin(); replayIT != replay.end(); ++replayIT)
		{
			if ((*replayIT)->GetFileName().IsSameAs(changePath, false))
			{
				(*replayIT)->SetFileName(event.GetNewPath().GetFullPath());
				break;
			}
		}
	}

	event.Skip();
}