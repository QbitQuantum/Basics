static int privacy_exec (struct cw_channel *chan, int argc, char **argv)
{
	char phone[30];
	struct localuser *u;
	struct cw_config *cfg;
	char *s;
	int res=0;
	int retries;
	int maxretries = 3;
	int minlength = 10;
	int x;

	LOCAL_USER_ADD (u);

	if (!cw_strlen_zero(chan->cid.cid_num)) {
		if (option_verbose > 2)
			cw_verbose (VERBOSE_PREFIX_3 "CallerID Present: Skipping\n");
		pbx_builtin_setvar_helper(chan, "PRIVACYMGRSTATUS", "SUCCESS");
	} else {
		/*Answer the channel if it is not already*/
		if (chan->_state != CW_STATE_UP) {
			res = cw_answer(chan);
			if (res) {
				pbx_builtin_setvar_helper(chan, "PRIVACYMGRSTATUS", "FAIL");
				LOCAL_USER_REMOVE(u);
				return 0;
			}
		}
		/*Read in the config file*/
		cfg = cw_config_load(PRIV_CONFIG);
		
		
		/*Play unidentified call*/
		res = cw_safe_sleep(chan, 1000);
		if (!res)
			res = cw_streamfile(chan, "privacy-unident", chan->language);
		if (!res)
			res = cw_waitstream(chan, "");

        if (cfg && (s = cw_variable_retrieve(cfg, "general", "maxretries"))) {
                if (sscanf(s, "%d", &x) == 1) {
                        maxretries = x;
                } else {
                        cw_log(LOG_WARNING, "Invalid max retries argument\n");
                }
        }
        if (cfg && (s = cw_variable_retrieve(cfg, "general", "minlength"))) {
                if (sscanf(s, "%d", &x) == 1) {
                        minlength = x;
                } else {
                        cw_log(LOG_WARNING, "Invalid min length argument\n");
                }
        }
			
		/*Ask for 10 digit number, give 3 attempts*/
		for (retries = 0; retries < maxretries; retries++) {
			if (!res ) 
				res = cw_app_getdata(chan, "privacy-prompt", phone, sizeof(phone), 0);

			if (res < 0)
				break;

			/*Make sure we get at least our minimum of digits*/
			if (strlen(phone) >= minlength ) 
				break;
			else {
				res = cw_streamfile(chan, "privacy-incorrect", chan->language);
				if (!res)
					res = cw_waitstream(chan, "");
			}
		}
		
		/*Got a number, play sounds and send them on their way*/
		if ((retries < maxretries) && res == 1 ) {
			res = cw_streamfile(chan, "privacy-thankyou", chan->language);
			if (!res)
				res = cw_waitstream(chan, "");
			cw_set_callerid (chan, phone, "Privacy Manager", NULL);
			if (option_verbose > 2)
				cw_verbose (VERBOSE_PREFIX_3 "Changed Caller*ID to %s\n",phone);
			pbx_builtin_setvar_helper(chan, "PRIVACYMGRSTATUS", "SUCCESS");
		} else {
			/* Flag Failure  */
			pbx_builtin_setvar_helper(chan, "PRIVACYMGRSTATUS", "FAIL");
		}
		if (cfg) 
			cw_config_destroy(cfg);
	}

  LOCAL_USER_REMOVE (u);
  return 0;
}