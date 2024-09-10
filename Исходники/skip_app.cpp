void http::skip_application::do_action(http::request_message& msg)
{
	message_headers const& hdrs = msg.headers();
	//! провер¤ем, что это не запрос от winamp-a
	http::buffer_t fld(&winamp_fld[0], sizeof(winamp_fld) - 1);
	http::vector_ptr val = hdrs.get(fld);
	skipped_ = val.get() != 0;
	//! провер¤ем, что запрос не есть тунелированное потоковое видиео
	//! Real Time Streaming Protocol (RTSP) RFC2326
	if(!skipped_)
	{
		vector_ptr const& subtype = msg.media_subtype();
		char *media_sub_type = _strlwr(&(*subtype)[0]);
		skipped_ = (_stricmp(media_sub_type, qtplayer_stream) == 0 ||
					_stricmp(media_sub_type, vvtk_tunnel) == 0);
	}
}