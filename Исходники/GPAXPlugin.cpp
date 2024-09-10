//GPAC player Event Handler. not yet implemented, just dummies here
Bool CGPAXPlugin::EventProc(GF_Event *evt)
{
	char msg[1024];
	if (!m_term) return 0;

    switch (evt->type) {
	case GF_EVENT_MESSAGE:
		if (evt->message.error) {
			sprintf(msg, "(GPAC) %s (%s)", evt->message.message, gf_error_to_string(evt->message.error));
		} else {
			sprintf(msg, "(GPAC) %s", evt->message.message);
		}
		SetStatusText(msg);
        break;
	case GF_EVENT_PROGRESS:
		if (evt->progress.done == evt->progress.total) {
			SetStatusText(NULL);
		} else {
			char *szTitle = "";
			if (evt->progress.progress_type==0) szTitle = "Buffer ";
			else if (evt->progress.progress_type==1) szTitle = "Download ";
			else if (evt->progress.progress_type==2) szTitle = "Import ";
			sprintf(msg, "(GPAC) %s: %02.2f", szTitle, (100.0*evt->progress.done) / evt->progress.total);
			SetStatusText(msg);
		}
		break;
    case GF_EVENT_CONNECT:
        m_bIsConnected = evt->connect.is_connected;
        break;
	/*IGNORE any scene size, just work with the size allocated in the parent doc*/
	case GF_EVENT_SCENE_SIZE:
        gf_term_set_size(m_term, m_width, m_height);
        break;
	/*window has been resized (full-screen plugin), resize*/
	case GF_EVENT_SIZE:
		m_width = evt->size.width;
		m_height = evt->size.height;
        gf_term_set_size(m_term, m_width, m_height);
        break;
	case GF_EVENT_DBLCLICK:
		gf_term_set_option(m_term, GF_OPT_FULLSCREEN, !gf_term_get_option(m_term, GF_OPT_FULLSCREEN));
		break;
	case GF_EVENT_KEYDOWN:
		if ((evt->key.flags  & GF_KEY_MOD_ALT)) {
	    } else {
			switch (evt->key.key_code) {
			case GF_KEY_HOME:
				gf_term_set_option(m_term, GF_OPT_NAVIGATION_TYPE, 1);
				break;
			case GF_KEY_ESCAPE:
				gf_term_set_option(m_term, GF_OPT_FULLSCREEN, !gf_term_get_option(m_term, GF_OPT_FULLSCREEN));
				break;
			}
		}
	    break;
	case GF_EVENT_NAVIGATE_INFO:
		strcpy(msg, evt->navigate.to_url);
		SetStatusText(msg);
		break;
	case GF_EVENT_NAVIGATE:
		if (gf_term_is_supported_url(m_term, evt->navigate.to_url, 1, 1)) {
			gf_term_navigate_to(m_term, evt->navigate.to_url);
			return 1;
		} 
#ifndef _WIN32_WCE
		else if (m_pBrowser) {
			u32 i;
			const char **sz_ptr;
			u16 w_szTar[1024], w_szURL[1024];
			VARIANT target, flags;
			flags.intVal = 0;
			target.bstrVal = L"_SELF";

			for (i=0; i<evt->navigate.param_count; i++) {
				if (!strcmp(evt->navigate.parameters[i], "_parent")) target.bstrVal = L"_PARENT";
				else if (!strcmp(evt->navigate.parameters[i], "_blank")) target.bstrVal = L"_BLANK";
				else if (!strcmp(evt->navigate.parameters[i], "_top")) target.bstrVal = L"_TOP";
				else if (!strcmp(evt->navigate.parameters[i], "_new")) flags.intVal |= navOpenInNewWindow;
				else if (!strnicmp(evt->navigate.parameters[i], "_target=", 8)) {
					sz_ptr = & evt->navigate.parameters[i]+8;
					gf_utf8_mbstowcs(w_szTar, 1024, (const char **)sz_ptr);
					target.bstrVal = (BSTR) w_szTar;
				}
			}
			sz_ptr = & evt->navigate.to_url;
			gf_utf8_mbstowcs(w_szURL, 1024, (const char **)sz_ptr);
			m_pBrowser->Navigate((BSTR) w_szURL, &flags, &target, NULL, NULL);;
			return 1;
		}
#endif
		break;
    }
    return 0;
}