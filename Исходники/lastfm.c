static int
auth (void) {
    lfm_update_auth ();
    if (lfm_sess[0]) {
        return 0;
    }
    if (!lfm_user[0] || !lfm_pass[0]) {
        return -1;
    }
    char req[4096];
    time_t timestamp = time(NULL);
    uint8_t sig[16];
    char passmd5[33];
    char token[100];
    deadbeef->md5 (sig, lfm_pass, strlen (lfm_pass));
    deadbeef->md5_to_str (passmd5, sig);
    snprintf (token, sizeof (token), "%s%d", passmd5, (int)timestamp);
    deadbeef->md5 (sig, token, strlen (token));
    deadbeef->md5_to_str (token, sig);

    deadbeef->conf_lock ();
    const char *scrobbler_url = deadbeef->conf_get_str_fast ("lastfm.scrobbler_url", SCROBBLER_URL_LFM);
#if LFM_TESTMODE
    snprintf (req, sizeof (req), "%s/?hs=true&p=1.2.1&c=tst&v=1.0&u=%s&t=%d&a=%s", scrobbler_url, lfm_user, (int)timestamp, token);
#else
    snprintf (req, sizeof (req), "%s/?hs=true&p=1.2.1&c=%s&v=%d.%d&u=%s&t=%d&a=%s", scrobbler_url, LFM_CLIENTID, plugin.plugin.version_major, plugin.plugin.version_minor, lfm_user, (int)timestamp, token);
#endif
    deadbeef->conf_unlock ();
    // handshake
    int status = curl_req_send (req, NULL);
    if (!status) {
        // check status and extract session id, nowplaying url, submission url
        if (strncmp (lfm_reply, "OK", 2)) {
            uint8_t *p = lfm_reply;
            while (*p && *p >= 0x20) {
                p++;
            }
            *p = 0;
            trace ("scrobbler auth failed, response: %s\n", lfm_reply);
            goto fail;
        }
        uint8_t *p = lfm_reply + 2;
        // skip whitespace
        while (*p && *p < 0x20) {
            p++;
        }
        // get session
        if (!*p) {
            trace ("unrecognized scrobbler reply:\n%s\n", lfm_reply);
            goto fail;
        }
        uint8_t *end = p+1;
        while (*end && *end >= 0x20) {
            end++;
        }
        if (end-p > 32) {
            trace ("scrobbler session id is invalid length. probably plugin needs fixing.\n");
            goto fail;
        }
        strncpy (lfm_sess, p, 32);
        lfm_sess[32] = 0;
        trace ("obtained scrobbler session: %s\n", lfm_sess);
        p = end;
        // skip whitespace
        while (*p && *p < 0x20) {
            p++;
        }
        // get nowplaying url
        if (!*p) {
            trace ("unrecognized scrobbler reply:\n%s\n", lfm_reply);
            goto fail;
        }
        end = p+1;
        while (*end && *end >= 0x20) {
            end++;
        }
        if (end - p > sizeof (lfm_nowplaying_url)-1) {
            trace ("scrobbler nowplaying url is too long %d:\n", (int)(end-p));
            goto fail;
        }
        strncpy (lfm_nowplaying_url, p, end-p);
        lfm_nowplaying_url[end-p] = 0;
        trace ("obtained scrobbler nowplaying url: %s\n", lfm_nowplaying_url);
        p = end;
        // skip whitespace
        while (*p && *p < 0x20) {
            p++;
        }
        // get submission url
        if (!*p) {
            trace ("unrecognized scrobbler reply:\n%s\n", lfm_reply);
            goto fail;
        }
        end = p+1;
        while (*end && *end >= 0x20) {
            end++;
        }
        if (end - p > sizeof (lfm_submission_url)-1) {
            trace ("scrobbler submission url is too long: %d\n", (int)(end-p));
            goto fail;
        }
        strncpy (lfm_submission_url, p, end-p);
        lfm_submission_url[end-p] = 0;
        trace ("obtained scrobbler submission url: %s\n", lfm_submission_url);
        p = end;
    }
    else {
        // send failed, but that doesn't mean session is invalid
        curl_req_cleanup ();
        return -1;
    }

    curl_req_cleanup ();
    return 0;
fail:
    lfm_sess[0] = 0;
    curl_req_cleanup ();
    return -1;
}