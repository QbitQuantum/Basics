/*---------------------------------------------------------
	実行
---------------------------------------------------------*/
void CSaoriIMM::exec(const CSAORIInput& in,CSAORIOutput& out)
{
	out.result_code = SAORIRESULT_BAD_REQUEST;
	if ( in.args.size() < 1 ) { return; }

	DWORD flag = SND_ASYNC;
	std::string filepath;

	if ( wcsnicmp(in.args[0].c_str(),L"list",4) == 0 ) {
		UpdateWindowList();

		if ( m_list.size() == 0 ) {
			out.result_code = SAORIRESULT_NO_CONTENT;
			return;
		}

		out.result_code = SAORIRESULT_OK;

		string_t txt;

		size_t n = m_list.size();
		string_t title;

		for ( size_t i = 0 ; i < n ; ++i ) {
			title = SAORI_FUNC::MultiByteToUnicode(m_list[i].title.c_str());
			out.values.push_back(title);
			txt += title;
			txt += L"\1";
		}

		if ( txt.size() ) {
			txt.erase(txt.size()-1,1);
		}
		out.result = txt;
	}
	else if ( wcsnicmp(in.args[0].c_str(),L"send",4) == 0 ) {
		if ( in.args.size() < 2 ) {
			return;
		}

		const char_t *send_to = NULL;
		if ( in.args.size() >= 3 ) {
			send_to = in.args[2].c_str();
		}
		SendTo(out,in.args[1].c_str(),send_to);
	}
	else if ( wcsnicmp(in.args[0].c_str(),L"focus",5) == 0 ) {
		if ( in.args.size() < 2 ) {
			return;
		}

		const char_t *send_to = NULL;
		if ( in.args.size() >= 3 ) {
			send_to = in.args[1].c_str();
		}
		SendTo(out,L"$TTPC_FOCUS",send_to);
	}
}