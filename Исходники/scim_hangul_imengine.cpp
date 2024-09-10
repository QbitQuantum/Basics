bool
HangulInstance::process_key_event (const KeyEvent& rawkey)
{
    SCIM_DEBUG_IMENGINE(1) << "process_key_event.\n";

    KeyEvent key = rawkey.map_to_layout(SCIM_KEYBOARD_Default);

    m_prev_key = key;

    if (use_ascii_mode() && !is_hangul_mode()) {
	if (is_hangul_key(key)) {
	    toggle_hangul_mode();
	    return true;
	}

	return false;
    }

    /* ignore key release. */
    if (key.is_key_release ())
        return false;

    /* mode change */
    if (use_ascii_mode() && is_hangul_key(key)) {
	toggle_hangul_mode();
	return true;
    }

    /* hanja mode */
    if (is_hanja_mode_key (key)) {
	toggle_hanja_mode();
    }

    /* toggle candidate table */
    if (is_hanja_key (key)) {
	if (is_hanja_mode()) {
	    update_candidates ();
	} else {
	    if (m_lookup_table.number_of_candidates ())
		delete_candidates ();
	    else
		update_candidates ();
	}

        return true;
    }

    /* ignore shift keys */
    if (key.code == SCIM_KEY_Shift_L || key.code == SCIM_KEY_Shift_R)
        return false;

    /* flush on modifier-on keys */
    if (key.is_control_down() || key.is_alt_down()) {
	flush ();
        return false;
    }

    /* candidate keys */
    if (m_lookup_table.number_of_candidates ()) {
        if (candidate_key_event(key))
	    return true;
    }

    /* change to ascii mode on ESCAPE key, for vi users.
     * We should process this key after processing candidate keys,
     * or input mode will be changed to non-hangul mode when the user presses
     * escape key to close candidate window. */
    if (use_ascii_mode() && !is_hanja_mode()) {
	if (key.code == SCIM_KEY_Escape) {
	    toggle_hangul_mode();
	}
    }

    /* backspace */
    if (is_backspace_key(key)) {
        bool ret = hangul_ic_backspace(m_hic);
        if (ret) {
	    hangul_update_preedit_string ();
	} else if (m_preedit.length() > 0) {
	    ret = true;
	    m_preedit.erase(m_preedit.length() - 1, 1);
	    hangul_update_preedit_string();
	} else {
	    if (m_surrounding_text.length() > 0) {
		m_surrounding_text.erase(m_surrounding_text.length() - 1, 1);
		if (m_surrounding_text.empty()) {
		    delete_candidates();
		    return ret;
		}
	    }
	}

	if (is_hanja_mode() && m_lookup_table.number_of_candidates()) {
	    update_candidates();
	}

        return ret;
    }

    if (key.code >= SCIM_KEY_exclam && key.code <= SCIM_KEY_asciitilde) {
	/* main hangul composing process */
	int ascii = key.get_ascii_code();
	if (key.is_caps_lock_down()) {
	    if (isupper(ascii))
		ascii = tolower(ascii);
	    else if (islower(ascii))
		ascii = toupper(ascii);
	}

	bool ret = hangul_ic_process(m_hic, ascii);

	WideString wstr;
	wstr = get_commit_string ();
	if (wstr.length ()) {
	    /* Before commit, we set preedit string to null to work arround
	     * some buggy IM implementation, ex) Qt, Evolution */
	    hide_preedit_string ();
	    if (is_hanja_mode() || m_factory->m_commit_by_word) {
		m_preedit += wstr;
	    } else {
		commit_string(wstr);
	    }
	}

	if (is_hanja_mode() || m_factory->m_commit_by_word) {
	    if (hangul_ic_is_empty(m_hic)) {
		flush();
	    }
	}

	hangul_update_preedit_string ();

	if (is_hanja_mode()) {
	    update_candidates();
	}

	return ret;
    }

    flush();
    return false;
}