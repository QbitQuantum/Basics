void shortlog_output(struct shortlog *log)
{
	int i, j;
	struct strbuf sb = STRBUF_INIT;

	if (log->sort_by_number)
		QSORT(log->list.items, log->list.nr,
		      log->summary ? compare_by_counter : compare_by_list);
	for (i = 0; i < log->list.nr; i++) {
		const struct string_list_item *item = &log->list.items[i];
		if (log->summary) {
			fprintf(log->file, "%6d\t%s\n",
				(int)UTIL_TO_INT(item), item->string);
		} else {
			struct string_list *onelines = item->util;
			fprintf(log->file, "%s (%d):\n",
				item->string, onelines->nr);
			for (j = onelines->nr - 1; j >= 0; j--) {
				const char *msg = onelines->items[j].string;

				if (log->wrap_lines) {
					strbuf_reset(&sb);
					add_wrapped_shortlog_msg(&sb, msg, log);
					fwrite(sb.buf, sb.len, 1, log->file);
				}
				else
					fprintf(log->file, "      %s\n", msg);
			}
			putc('\n', log->file);
			onelines->strdup_strings = 1;
			string_list_clear(onelines, 0);
			free(onelines);
		}

		log->list.items[i].util = NULL;
	}

	strbuf_release(&sb);
	log->list.strdup_strings = 1;
	string_list_clear(&log->list, 1);
	clear_mailmap(&log->mailmap);
}