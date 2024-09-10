bool LoadAttributeFileWAV(FILE_INFO *pFileMP3)
{
	CRiffSIF riff;
	wchar_t ext[_MAX_EXT];
	_tsplitpath(GetFullPath(pFileMP3), NULL, NULL, NULL, ext);
    if(_strcmpi(ext, ".wav") == 0){
        if(riff.Load(GetFullPath(pFileMP3),'W','A','V','E') != ERROR_SUCCESS){
            return false;
        }
    }
    else if(_strcmpi(ext, ".avi") == 0){
        if(riff.Load(GetFullPath(pFileMP3),'A','V','I',' ') != ERROR_SUCCESS){
            return false;
        }
	    //ISBJ songname
	    SetTrackNameSI(pFileMP3, riff.GetField('I','S','B','J'));
    }
    else{
        return false;
    }
    //INAM/ISBJ タイトル
    //ISBJ よりも INAM を優先
    SetTrackNameSI(pFileMP3, riff.GetField('I','N','A','M'));
    if(wcslen(GetTrackNameSI(pFileMP3)) == 0){
        SetTrackNameSI(pFileMP3, riff.GetField('I','S','B','J'));
    }
	//IART アーティスト名
	SetArtistNameSI(pFileMP3, riff.GetField('I','A','R','T'));
	//IPRD アルバム名
	SetAlbumNameSI(pFileMP3, riff.GetField('I','P','R','D'));
	//ICMT コメント
	SetCommentSI(pFileMP3, riff.GetField('I','C','M','T'));
	//ICRD 日付
	SetYearSI(pFileMP3, riff.GetField('I','C','R','D'));
	//IGNR ジャンル
	SetGenreSI(pFileMP3, riff.GetField('I','G','N','R'));
	//ICOP 著作権
	SetCopyrightSI(pFileMP3, riff.GetField('I','C','O','P'));
	//IENG エンジニア	
    SetEngineerSI(pFileMP3, riff.GetField('I','E','N','G'));
	//ISRC ソース	
	SetSourceSI(pFileMP3, riff.GetField('I','S','R','C'));
	//ISFT ソフトウェア
	SetSoftwareSI(pFileMP3, riff.GetField('I','S','F','T'));
	//ITRK トラック番号
	SetTrackNumberSI(pFileMP3, riff.GetField('I','T','R','K'));

	extern bool GetValues_mp3infp(FILE_INFO *pFileMP3);
	GetValues_mp3infp(pFileMP3);
    return true;
}