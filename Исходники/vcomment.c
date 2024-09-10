int write_ogg_tag(const string fname, struct fennec_audiotag *wtag)
{
	vcedit_state   *state;
	vorbis_comment *vc;
	param_t	       *param;
	FILE           *tfile;
	FILE           *of;
	string          outname;

	struct fennec_audiotag_item *ct;

	if(!fname || !wtag)return -3;

	setlocale(LC_ALL, "");

	/* initialize the cmdline interface */
	param = new_param();
	
	tfile = _wfsopen(fname, uni("r+b"), _SH_DENYRW);

	if(!tfile)
	{
		MessageBox(0, uni("Access denied, please stop playback and try again (you don't need to close this window)."), uni("Tag Editing"), MB_ICONINFORMATION);
		return -1;
	}

	state = vcedit_new_state();
	
	if(vcedit_open(state, tfile) < 0)
	{
		fclose(tfile);
		free_param(param);
		vcedit_clear(state);
		return -2;
	}
	
	vc = vcedit_comments(state);

	ct = &wtag->tag_title;         if(ct->tsize)local_addcomment(vc, "TITLE",             ct->tdata); else local_addcomment(vc, "TITLE",              uni("") );
	ct = &wtag->tag_album;         if(ct->tsize)local_addcomment(vc, "ALBUM",             ct->tdata); else local_addcomment(vc, "ALBUM",              uni("") );
	ct = &wtag->tag_artist;        if(ct->tsize)local_addcomment(vc, "ARTIST",            ct->tdata); else local_addcomment(vc, "ARTIST",             uni("") );
	ct = &wtag->tag_origartist;    if(ct->tsize)local_addcomment(vc, "ORIGINALARTIST",    ct->tdata); else local_addcomment(vc, "ORIGINALARTIST",     uni("") );
	ct = &wtag->tag_composer;      if(ct->tsize)local_addcomment(vc, "COMPOSER",          ct->tdata); else local_addcomment(vc, "COMPOSER",           uni("") );
	ct = &wtag->tag_lyricist;      if(ct->tsize)local_addcomment(vc, "LYRICIST",          ct->tdata); else local_addcomment(vc, "LYRICIST",           uni("") );
	ct = &wtag->tag_band;          if(ct->tsize)local_addcomment(vc, "BANDNAME",          ct->tdata); else local_addcomment(vc, "BANDNAME",           uni("") );
	ct = &wtag->tag_copyright;     if(ct->tsize)local_addcomment(vc, "COPYRIGHT",         ct->tdata); else local_addcomment(vc, "COPYRIGHT",          uni("") );
	ct = &wtag->tag_publish;       if(ct->tsize)local_addcomment(vc, "PUBLISHER",         ct->tdata); else local_addcomment(vc, "PUBLISHER",          uni("") );
	ct = &wtag->tag_encodedby;     if(ct->tsize)local_addcomment(vc, "ENCODEDBY",         ct->tdata); else local_addcomment(vc, "ENCODEDBY",          uni("") );
	ct = &wtag->tag_genre;         if(ct->tsize)local_addcomment(vc, "GENRE",             ct->tdata); else local_addcomment(vc, "GENRE",              uni("") );
	ct = &wtag->tag_year;          if(ct->tsize)local_addcomment(vc, "YEAR",              ct->tdata); else local_addcomment(vc, "YEAR",               uni("") );
	ct = &wtag->tag_url;           if(ct->tsize)local_addcomment(vc, "URL",               ct->tdata); else local_addcomment(vc, "URL",                uni("") );
	ct = &wtag->tag_offiartisturl; if(ct->tsize)local_addcomment(vc, "OFFICIALARTISTURL", ct->tdata); else local_addcomment(vc, "OFFICIALARTISTURL",  uni("") );
	ct = &wtag->tag_comments;      if(ct->tsize)local_addcomment(vc, "COMMENT",           ct->tdata); else local_addcomment(vc, "COMMENT",            uni("") );
	ct = &wtag->tag_lyric;         if(ct->tsize)local_addcomment(vc, "LYRIC",             ct->tdata); else local_addcomment(vc, "LYRIC",              uni("") );
	ct = &wtag->tag_bpm;           if(ct->tsize)local_addcomment(vc, "BPM",               ct->tdata); else local_addcomment(vc, "BPM",                uni("") );
	ct = &wtag->tag_tracknum;      if(ct->tsize)local_addcomment(vc, "TRACKNUMBER",       ct->tdata); else local_addcomment(vc, "TRACKNUMBER",        uni("") );

	outname = (string) malloc(str_size(fname) + (5 * sizeof(letter)));

	str_cpy(outname, fname);
	str_cat(outname, uni(".tmp"));

	of = _wfopen(outname, uni("wb"));

	if(vcedit_write(state, of) < 0)
	{
		fclose(of);
		fclose(tfile);
		free_param(param);
		vcedit_clear(state);
		free(outname);
		return 1;
	}

	fclose(of);
	
	/* done */

	vcedit_clear(state);
	fclose(tfile);
	free_param(param);


	_wremove(fname);
	sys_sleep(0);
	_wrename(outname, fname);
		
	free(outname);
	return 0;
}