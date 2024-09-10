static void csv_event(auparse_state_t *au,
		auparse_cb_event_t cb_event_type, void *user_data)
{
	if (cb_event_type != AUPARSE_CB_EVENT_READY)
		return;

	if (csv_header_done == 0) {
		csv_header_done = 1;
		printf( "NODE,EVENT,DATE,TIME,%sSERIAL_NUM,EVENT_KIND,"
			"SESSION,SUBJ_PRIME,SUBJ_SEC,SUBJ_KIND,%sACTION,"
			"RESULT,OBJ_PRIME,OBJ_SEC,%s%sOBJ_KIND,HOW%s\n",
		    extra_time ? "YEAR,MONTH,DAY,WEEKDAY,HOUR,GMT_OFFSET," : "",
			extra_labels ? "SUBJ_LABEL," : "",
			extra_obj2 ? "OBJ2," : "",
			extra_labels ? "OBJ_LABEL," : "",
			extra_keys ? ",KEY" : "");
	}

	char tmp[20];
	const char *item, *type, *evkind, *subj_kind, *action, *str, *how;
	int rc;
	time_t t = auparse_get_time(au);
	struct tm *tv = localtime(&t);

	// NODE
	item = auparse_get_node(au);
	if (item) {
		printf("%s", auparse_interpret_field(au));
		free((void *)item);
	}
	putchar(',');

	// Event
	type = auparse_get_type_name(au);
	if (type)
		printf("%s", type);
	putchar(',');

	// Normalize
	rc = auparse_normalize(au,
			extra_labels ? NORM_OPT_ALL : NORM_OPT_NO_ATTRS);

	//DATE
	if (tv) {
		strftime(tmp, sizeof(tmp), "%x", tv);
		printf("%s", tmp);
	}
	putchar(',');

	// TIME
	if (tv) {
		strftime(tmp, sizeof(tmp), "%T", tv);
		printf("%s", tmp);
	}
	putchar(',');

	if (extra_time) {
		// YEAR
		if (tv) {
			strftime(tmp, sizeof(tmp), "%Y", tv);
			printf("%s", tmp);
		}
		putchar(',');

		// MONTH
		if (tv) {
			strftime(tmp, sizeof(tmp), "%m", tv);
			printf("%s", tmp);
		}
		putchar(',');

		// DAY
		if (tv) {
			strftime(tmp, sizeof(tmp), "%d", tv);
			printf("%s", tmp);
		}
		putchar(',');

		// WEEKDAY
		if (tv) {
			strftime(tmp, sizeof(tmp), "%u", tv);
			printf("%s", tmp);
		}
		putchar(',');

		// HOUR
		if (tv) {
			strftime(tmp, sizeof(tmp), "%k", tv);
			printf("%s", tmp);
		}
		putchar(',');
		if (tv) {
			char sign = tv->tm_gmtoff >= 0 ? '+' : '-';
			unsigned long total = labs(tv->tm_gmtoff);
			unsigned long hour = total/3600;
			unsigned long min = (total - (hour * 3600))%60;
			printf("%c%02lu:%02lu", sign, hour, min);
		}
		putchar(',');
	}

	// SERIAL_NUMBER
	printf("%lu,", auparse_get_serial(au));

	if (rc) {
		fprintf(stderr, "error normalizing %s\n", type);

		// Just dump an empty frame
		printf(",,,,,,,,,%s%s\n", extra_labels ? ",," : "",
			extra_keys ? "," : "");
		return;
	}

	// EVENT_KIND
	evkind = auparse_normalize_get_event_kind(au);
	printf("%s", evkind ? evkind : "unknown");
	putchar(',');

	// SESSION
	rc = auparse_normalize_session(au);
	if (rc == 1)
		printf("%s", auparse_interpret_field(au));
	putchar(',');

	// SUBJ_PRIME
	rc = auparse_normalize_subject_primary(au);
	if (rc == 1) {
		const char *subj = auparse_interpret_field(au);
		if (strcmp(subj, "unset") == 0)
			subj = "system";
		printf("%s", subj);
	}
	putchar(',');

	// SUBJ_SEC
	rc = auparse_normalize_subject_secondary(au);
	if (rc == 1)
		printf("%s", auparse_interpret_field(au));
	putchar(',');

	// SUBJ_KIND
	subj_kind = auparse_normalize_subject_kind(au);
	if (subj_kind)
		printf("%s", subj_kind);
	putchar(',');

	// SUBJ_LABEL
	if (extra_labels) {
		rc = auparse_normalize_subject_first_attribute(au);
		do {
			if (rc == 1) {
				const char *name = auparse_get_field_name(au);
				if (strcmp(name, "subj") == 0) {
					printf("%s",
						auparse_interpret_field(au));
					break;
				}
			}
		} while (auparse_normalize_subject_next_attribute(au) == 1);
		putchar(',');
	}

	// ACTION
	action = auparse_normalize_get_action(au);
	printf("%s", action ? action : "did-unknown");
	putchar(',');

	// RESULT
	rc = auparse_normalize_get_results(au);
	if (rc == 1) {
		int i = 0;
		const char *res[] = { "failed", "success" };
		item = auparse_interpret_field(au);
		if (strcmp(item, "yes") == 0)
			i = 1;
		else if (strncmp(item, "suc", 3) == 0)
			i = 1;
		else if (auparse_get_field_type(au) == AUPARSE_TYPE_SECCOMP &&
				strcmp(item, "allow") == 0)
			i = 1;
		printf("%s", res[i]);
	}
	putchar(',');

	// OBJ_PRIME
	rc = auparse_normalize_object_primary(au);
	if (rc == 1) {
		const char *val;

		if (auparse_get_field_type(au) == AUPARSE_TYPE_ESCAPED_FILE)
			val = auparse_interpret_realpath(au);
		else
			val = auparse_interpret_field(au);
		printf("%s", val);
	}
	putchar(',');

	// OBJ_SEC
	rc = auparse_normalize_object_secondary(au);
	if (rc == 1)
		printf("%s", auparse_interpret_field(au));
	putchar(',');

	// OBJECT 2
	if (extra_obj2) {
		rc = auparse_normalize_object_primary2(au);
		if (rc == 1) {
			const char *val;

			if (auparse_get_field_type(au) ==
						AUPARSE_TYPE_ESCAPED_FILE)
				val = auparse_interpret_realpath(au);
			else
				val = auparse_interpret_field(au);
			printf("%s", val);
		}
		putchar(',');
	}

	// OBJ_LABEL
	if (extra_labels) {
		rc = auparse_normalize_object_first_attribute(au);
		do {
			if (rc == 1) {
				const char *name = auparse_get_field_name(au);
				if (strcmp(name, "obj") == 0) {
					printf("%s",
						auparse_interpret_field(au));
					break;
				}
			}
		} while (auparse_normalize_object_next_attribute(au) == 1);
		putchar(',');
	}

	// OBJ_KIND
	str = auparse_normalize_object_kind(au);
	printf("%s,", str);

	// HOW
	how = auparse_normalize_how(au);
	if (how)
		printf("%s", how);

	// KEY
	if (extra_keys) {
		putchar(','); // This is to close out HOW
		rc = auparse_normalize_key(au);
		if (rc == 1)
			printf("%s", auparse_interpret_field(au));
	}
	printf("\n");
}