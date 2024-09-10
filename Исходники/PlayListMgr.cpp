void PlayListMgr::AddSongToList(spSongInfoT spSong,unsigned int u_listId)
{
	ASSERT(spSong);
	CSongInfo songInfo;
	songInfo.SetAblumName(spSong->GetAlbumName());
	songInfo.SetAddTime(spSong->GetAddTime());
	songInfo.SetAlbumId(spSong->GetAlbumId());
	songInfo.SetArtistId(spSong->GetArtistId());
	songInfo.SetArtistName(spSong->GetArtistName());
	songInfo.SetAudioLength(spSong->GetAudioLength());
	songInfo.SetCoverLocalPath(spSong->GetCoverLocalPath());
	songInfo.SetCoverUrl(spSong->GetCoverUrl());
	songInfo.SetEnable(spSong->IsEnable());
	songInfo.SetFileExt(spSong->GetFileExt());
	songInfo.SetFileSize(spSong->GetFileSize());
	songInfo.SetFileStartPos(spSong->GetFileStartPos());
	songInfo.SetFileType(spSong->GetFileType());
	songInfo.SetFlag(spSong->GetFlag());
	songInfo.SetLastModifyTime(spSong->GetLastModifyTime());
	songInfo.SetLastPlayTime(spSong->GetLastPlayTime());
	songInfo.SetListenFileUrl(spSong->GetListenFileUrl());
	songInfo.SetLocal(spSong->IsLocal());
	songInfo.SetLocalId(spSong->GetLocalId());
	songInfo.SetLocalPath(spSong->GetLocalPath());
	songInfo.SetLrcLocalPath(spSong->GetLrcLocalPath());
	songInfo.SetLrcUrl(spSong->GetLrcUrl());
	songInfo.SetMD5(spSong->GetMD5());
	songInfo.SetPlayCount(spSong->GetPlayCount());
	songInfo.SetRealArtistName(spSong->GetRealArtistName());
	songInfo.SetResourceID(spSong->GetResourceId());
	songInfo.SetSongId(spSong->GetSongId());
	songInfo.SetSongName(spSong->GetSongName());
	songInfo.SetTag(spSong->GetTag());

	AddSongToList(songInfo,u_listId);
}