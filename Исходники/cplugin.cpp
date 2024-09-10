void CPLUGIN::exec_before(const CSAORIInput& in,CSAORIOutput& out)
{
	//----------変数群初期化----------
	script.erase();
	script_option.erase();
	event.erase();
	event_option.erase();
	target.erase();
	marker.erase();
	security_level.erase();

	language.erase();
	map_strpair::const_iterator itr = in.opts.find(L"Language");
	if ( itr != in.opts.end() ) {
		language = itr->second;
	}

	sender.erase();
	itr = in.opts.find(L"Sender");
	if ( itr != in.opts.end() ) {
		sender = itr->second;
	}
	
	//----------ゴーストリスト更新----------
	if ( in.args.size() >= 5 ) {
		if ( wcsicmp(in.id.c_str(),L"OnGhostBoot") == 0 || wcsicmp(in.id.c_str(),L"OnGhostInfoUpdate") == 0 ) {
			string_t path = in.args[4];

			ghost_map_type::iterator itr = ghost_map.find(path);

			SAORI_FUNC::CCriticalSectionLock lock(sstp_thread_lock);

			CGhostInfo *pGI;
			if ( itr != ghost_map.end() ) {
				pGI = &(itr->second);
			}
			else {
				pGI = &(ghost_map[path]);
			}

			pGI->hwnd = reinterpret_cast<void*>(wcstoul(in.args[0].c_str(),NULL,10));
			pGI->name = in.args[1];
			pGI->shell_name = in.args[2];
			pGI->id = in.args[3];
			pGI->path = path;
			if ( in.args.size() >= 6 ) {
				pGI->shell_path = in.args[5];
			}
			else {
				pGI->shell_path.erase();
			}
		}
		else if ( wcsicmp(in.id.c_str(),L"OnGhostExit") == 0 ) {
			string_t path = in.args[4];

			SAORI_FUNC::CCriticalSectionLock lock(sstp_thread_lock);

			ghost_map_type::iterator itr = ghost_map.find(path);
			if ( itr != ghost_map.end() ) {
				ghost_map.erase(itr);
			}
		}
	}
}