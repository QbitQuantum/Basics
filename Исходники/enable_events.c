/*
 * Compare list of exclusions against an event name.
 * Return a list of legal exclusion names.
 * Produce an error or a warning about others (depending on the situation)
 */
static
int check_exclusion_subsets(const char *event_name,
		const char *exclusions,
		int *exclusion_count_ptr,
		char ***exclusion_list_ptr)
{
	const char *excluder_ptr;
	const char *event_ptr;
	const char *next_excluder;
	int excluder_length;
	int exclusion_count = 0;
	char **exclusion_list = NULL;
	int ret = CMD_SUCCESS;

	if (event_name[strlen(event_name) - 1] != '*') {
		ERR("Event %s: Excluders can only be used with wildcarded events", event_name);
		goto error;
	}

	next_excluder = exclusions;
	while (*next_excluder != 0) {
		event_ptr = event_name;
		excluder_ptr = next_excluder;
		excluder_length = strcspn(next_excluder, ",");

		/* Scan both the excluder and the event letter by letter */
		while (1) {
			char e, x;

			e = *event_ptr;
			x = *excluder_ptr;

			if (x == '*') {
				/* Event is a subset of the excluder */
				ERR("Event %s: %.*s excludes all events from %s",
						event_name,
						excluder_length,
						next_excluder,
						event_name);
				goto error;
			}
			if (e == '*') {
				char *string;
				char **new_exclusion_list;

				/* Excluder is a proper subset of event */
				string = lttng_strndup(next_excluder, excluder_length);
				if (!string) {
					PERROR("lttng_strndup error");
					goto error;
				}
				new_exclusion_list = realloc(exclusion_list,
					sizeof(char *) * (exclusion_count + 1));
				if (!new_exclusion_list) {
					PERROR("realloc");
					free(string);
					goto error;
				}
				exclusion_list = new_exclusion_list;
				exclusion_count++;
				exclusion_list[exclusion_count - 1] = string;
				break;
			}
			if (x != e) {
				/* Excluder and event sets have no common elements */
				WARN("Event %s: %.*s does not exclude any events from %s",
						event_name,
						excluder_length,
						next_excluder,
						event_name);
				break;
			}
			excluder_ptr++;
			event_ptr++;
		}
		/* next excluder */
		next_excluder += excluder_length;
		if (*next_excluder == ',') {
			next_excluder++;
		}
	}
	goto end;
error:
	while (exclusion_count--) {
		free(exclusion_list[exclusion_count]);
	}
	if (exclusion_list != NULL) {
		free(exclusion_list);
	}
	exclusion_list = NULL;
	exclusion_count = 0;
	ret = CMD_ERROR;
end:
	*exclusion_count_ptr = exclusion_count;
	*exclusion_list_ptr = exclusion_list;
	return ret;
}