bool C4MusicSystem::InitForScenario(C4Group & hGroup)
{
	// check if the scenario contains music
	bool fLocalMusic = false;
	StdStrBuf MusicDir;
	if (GrpContainsMusic(hGroup))
	{
		// clear global songs
		ClearSongs();
		fLocalMusic = true;
		// add songs
		MusicDir.Take(Game.ScenarioFile.GetFullName());
		LoadDir(MusicDir.getData());
		// log
		LogF(LoadResStr("IDS_PRC_LOCALMUSIC"), MusicDir.getData());
	}
	// check for music folders in group set
	C4Group *pMusicFolder = NULL;
	while ((pMusicFolder = Game.GroupSet.FindGroup(C4GSCnt_Music, pMusicFolder)))
	{
		if (!fLocalMusic)
		{
			// clear global songs
			ClearSongs();
			fLocalMusic = true;
		}
		// add songs
		MusicDir.Take(pMusicFolder->GetFullName());
		MusicDir.AppendChar(DirectorySeparator);
		MusicDir.Append(C4CFN_Music);
		LoadDir(MusicDir.getData());
		// log
		LogF(LoadResStr("IDS_PRC_LOCALMUSIC"), MusicDir.getData());
	}
	// no music?
	if (!SongCount) return false;
	// set play list
	SetPlayList(0);
	// ok
	return true;
}