int tagwrite(const string fname,  struct fennec_audiotag *wtag)
{	

	HRESULT               hres;
	IWMHeaderInfo*        wminfo;
	WORD                  wmistream = 0;
	BOOL                  sdef = 1;
	IWMMetadataEditor    *pEdit = 0;
	IWMHeaderInfo        *pInfo = 0;
	int                   twrote = 1;

	if(!wtag)return 0;

	CoInitialize(0);

	hres = WMCreateEditor(&pEdit);
	hres = pEdit->Open(fname);

	pEdit->QueryInterface(IID_IWMHeaderInfo, (VOID **)(&wminfo));


	if(wtag->tag_title.tsize         ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMTitle          ,wtag->tag_title.tdata         ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMTitle          , 0); }

	if(wtag->tag_album.tsize         ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMAlbumTitle     ,wtag->tag_album.tdata         ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMAlbumTitle     , 0); }

	if(wtag->tag_artist.tsize        ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMAuthor         ,wtag->tag_artist.tdata        ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMAuthor         , 0); }
	
	if(wtag->tag_origartist.tsize    ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMOriginalArtist ,wtag->tag_origartist.tdata    ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMOriginalArtist , 0); }
	
	if(wtag->tag_composer.tsize      ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMComposer       ,wtag->tag_composer.tdata      ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMComposer       , 0); }
	
	if(wtag->tag_lyricist.tsize      ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMLyrics         ,wtag->tag_lyricist.tdata      ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMWriter         , 0); }
 
	/* band: not used */
	
	if(wtag->tag_copyright.tsize     ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMCopyright      ,wtag->tag_copyright.tdata     ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMCopyright      , 0); }
	
	if(wtag->tag_publish.tsize       ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMPublisher      ,wtag->tag_publish.tdata       ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMPublisher      , 0); }
	
	if(wtag->tag_encodedby.tsize     ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMEncodedBy      ,wtag->tag_encodedby.tdata     ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMEncodedBy      , 0); }
	
	if(wtag->tag_genre.tsize         ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMGenre          ,wtag->tag_genre.tdata         ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMGenre          , 0); }
	
	if(wtag->tag_year.tsize          ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMYear           ,wtag->tag_year.tdata          ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMYear           , 0); }
	
	if(wtag->tag_url.tsize           ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMUserWebURL     ,wtag->tag_url.tdata           ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMUserWebURL     , 0); }
	
	if(wtag->tag_offiartisturl.tsize ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMAuthorURL      ,wtag->tag_offiartisturl.tdata ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMAuthorURL      , 0); }
	
	if(wtag->tag_comments.tsize      ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMDescription    ,wtag->tag_comments.tdata      ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMDescription    , 0); }
	
	if(wtag->tag_lyric.tsize         ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMLyrics         ,wtag->tag_lyric.tdata         ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMLyrics         , 0); }

	if(wtag->tag_bpm.tsize           ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMBeatsPerMinute ,wtag->tag_bpm.tdata           ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMBeatsPerMinute , 0); }

	if(wtag->tag_tracknum.tsize      ){ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMTrack          ,wtag->tag_tracknum.tdata      ); }
	else{ twrote = WM_SetTagString(wminfo, &wmistream, g_wszWMTrack          , 0); }

	if(!twrote)
	{
		MessageBox(0, uni("Couldn't set tag(s), if you're setting tags on currently playing media, try stopping it."), uni("Error on tagging"), MB_ICONQUESTION);
	}

	pEdit->Flush();
	pEdit->Close();
	wminfo->Release();
	pEdit->Release();

	return 1;
}