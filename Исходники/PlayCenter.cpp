void CPlayCenter::UpdateCurrentPlayingSong(spSongInfoT spSong)
{
	ASSERT(spSong);
	if(m_spPlayList.size()==0||m_spSongListMap.size()==0) return ;
	
	if(m_spPlayList.find(m_iCurPlayingListIndex)==m_spPlayList.end()) return ;
	auto iter = m_spSongListMap.find(m_iCurPlayingListIndex);
	if (iter != m_spSongListMap.end())
	{
		songsArrayT& songs = iter->second;
		if(songs.size()>0)
		{
			int iIndex = 0;
			for (songsArrayIterT iter=songs.begin();iter!=songs.end();++iter)
			{
				if(iter->GetLocalId()==m_iCurPlayingSongIndex)
				{
					songs[iIndex].SetAblumName(spSong->GetAlbumName());
					songs[iIndex].SetAlbumId(spSong->GetAlbumId());
					songs[iIndex].SetAddTime(spSong->GetAddTime());
					songs[iIndex].SetArtistId(spSong->GetArtistId());
					songs[iIndex].SetArtistName(spSong->GetArtistName());
					songs[iIndex].SetAudioLength(spSong->GetAudioLength());
					songs[iIndex].SetCoverLocalPath(spSong->GetCoverLocalPath());
					songs[iIndex].SetCoverUrl(spSong->GetCoverUrl());
					songs[iIndex].SetEnable(spSong->IsEnable());
					songs[iIndex].SetFileExt(spSong->GetFileExt());
					songs[iIndex].SetFileSize(spSong->GetFileSize());
					songs[iIndex].SetFileStartPos(spSong->GetFileStartPos());
					songs[iIndex].SetFileType(spSong->GetFileType());
					songs[iIndex].SetFlag(spSong->GetFlag());
					songs[iIndex].SetLastModifyTime(spSong->GetLastModifyTime());
					songs[iIndex].SetLastPlayTime(spSong->GetLastPlayTime());
					songs[iIndex].SetListenFileUrl(spSong->GetListenFileUrl());
					songs[iIndex].SetLocal(spSong->IsLocal());
					songs[iIndex].SetLocalId(spSong->GetLocalId());
					songs[iIndex].SetLocalPath(spSong->GetLocalPath());
					songs[iIndex].SetLrcLocalPath(spSong->GetLrcLocalPath());
					songs[iIndex].SetLrcUrl(spSong->GetLrcUrl());
					songs[iIndex].SetMD5(spSong->GetMD5());
					songs[iIndex].SetPlayCount(spSong->GetPlayCount());
					songs[iIndex].SetRealArtistName(spSong->GetRealArtistName());
					songs[iIndex].SetResourceID(spSong->GetResourceId());
					songs[iIndex].SetSongId(spSong->GetSongId());
					songs[iIndex].SetSongName(spSong->GetSongName());
					songs[iIndex].SetTag(spSong->GetTag());
					break;
				}
				iIndex ++;
			}
		}
	}
}