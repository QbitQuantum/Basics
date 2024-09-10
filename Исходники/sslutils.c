int np_net_ssl_check_cert(int days_till_exp_warn, int days_till_exp_crit){
#  ifdef USE_OPENSSL
	X509 *certificate=NULL;
	X509_NAME *subj=NULL;
	char timestamp[50] = "";
	char cn[MAX_CN_LENGTH]= "";
	char *tz;
	
	int cnlen =-1;
	int status=STATE_UNKNOWN;

	ASN1_STRING *tm;
	int offset;
	struct tm stamp;
	float time_left;
	int days_left;
	int time_remaining;
	time_t tm_t;

	certificate=SSL_get_peer_certificate(s);
	if (!certificate) {
		printf("%s\n",_("CRITICAL - Cannot retrieve server certificate."));
		return STATE_CRITICAL;
	}

	/* Extract CN from certificate subject */
	subj=X509_get_subject_name(certificate);

	if (!subj) {
		printf("%s\n",_("CRITICAL - Cannot retrieve certificate subject."));
		return STATE_CRITICAL;
	}
	cnlen = X509_NAME_get_text_by_NID(subj, NID_commonName, cn, sizeof(cn));
	if (cnlen == -1)
		strcpy(cn, _("Unknown CN"));

	/* Retrieve timestamp of certificate */
	tm = X509_get_notAfter(certificate);

	/* Generate tm structure to process timestamp */
	if (tm->type == V_ASN1_UTCTIME) {
		if (tm->length < 10) {
			printf("%s\n", _("CRITICAL - Wrong time format in certificate."));
			return STATE_CRITICAL;
		} else {
			stamp.tm_year = (tm->data[0] - '0') * 10 + (tm->data[1] - '0');
			if (stamp.tm_year < 50)
				stamp.tm_year += 100;
			offset = 0;
		}
	} else {
		if (tm->length < 12) {
			printf("%s\n", _("CRITICAL - Wrong time format in certificate."));
			return STATE_CRITICAL;
		} else {
			stamp.tm_year =
				(tm->data[0] - '0') * 1000 + (tm->data[1] - '0') * 100 +
				(tm->data[2] - '0') * 10 + (tm->data[3] - '0');
			stamp.tm_year -= 1900;
			offset = 2;
		}
	}
	stamp.tm_mon =
		(tm->data[2 + offset] - '0') * 10 + (tm->data[3 + offset] - '0') - 1;
	stamp.tm_mday =
		(tm->data[4 + offset] - '0') * 10 + (tm->data[5 + offset] - '0');
	stamp.tm_hour =
		(tm->data[6 + offset] - '0') * 10 + (tm->data[7 + offset] - '0');
	stamp.tm_min =
		(tm->data[8 + offset] - '0') * 10 + (tm->data[9 + offset] - '0');
	stamp.tm_sec =
		(tm->data[10 + offset] - '0') * 10 + (tm->data[11 + offset] - '0');
	stamp.tm_isdst = -1;

	tm_t = timegm(&stamp);
	time_left = difftime(tm_t, time(NULL));
	days_left = time_left / 86400;
	tz = getenv("TZ");
	setenv("TZ", "GMT", 1);
	tzset();
	strftime(timestamp, 50, "%c %z", localtime(&tm_t));
	if (tz)
		setenv("TZ", tz, 1);
	else
		unsetenv("TZ");
	tzset();

	if (days_left > 0 && days_left <= days_till_exp_warn) {
		printf (_("%s - Certificate '%s' expires in %d day(s) (%s).\n"), (days_left>days_till_exp_crit)?"WARNING":"CRITICAL", cn, days_left, timestamp);
		if (days_left > days_till_exp_crit)
			status = STATE_WARNING;
		else
			status = STATE_CRITICAL;
	} else if (days_left == 0 && time_left > 0) {
		if (time_left >= 3600)
			time_remaining = (int) time_left / 3600;
		else
			time_remaining = (int) time_left / 60;

		printf (_("%s - Certificate '%s' expires in %u %s (%s)\n"),
			(days_left>days_till_exp_crit) ? "WARNING" : "CRITICAL", cn, time_remaining,
			time_left >= 3600 ? "hours" : "minutes", timestamp);

		if ( days_left > days_till_exp_crit)
			status = STATE_WARNING;
		else
			status = STATE_CRITICAL;
	} else if (time_left < 0) {
		printf(_("CRITICAL - Certificate '%s' expired on %s.\n"), cn, timestamp);
		status=STATE_CRITICAL;
	} else if (days_left == 0) {
		printf (_("%s - Certificate '%s' just expired (%s).\n"), (days_left>days_till_exp_crit)?"WARNING":"CRITICAL", cn, timestamp);
		if (days_left > days_till_exp_crit)
			status = STATE_WARNING;
		else
			status = STATE_CRITICAL;
	} else {
		printf(_("OK - Certificate '%s' will expire on %s.\n"), cn, timestamp);
		status = STATE_OK;
	}
	X509_free(certificate);
	return status;
#  else /* ifndef USE_OPENSSL */
	printf("%s\n", _("WARNING - Plugin does not support checking certificates."));
	return STATE_WARNING;
#  endif /* USE_OPENSSL */
}