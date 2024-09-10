/**
 * json_events - Read JSON event file from disk and call event callback.
 * @fn: File name to read or NULL for default.
 * @func: Callback to call for each event
 * @data: Abstract pointer to pass to func.
 *
 * The callback gets the data pointer, the event name, the event 
 * in perf format and a description passed.
 *
 * Call func with each event in the json file 
 * Return: -1 on failure, otherwise 0.
 */
int json_events(const char *fn,
	  int (*func)(void *data, char *name, char *event, char *desc),
	  void *data)
{
	int err = -EIO;
	size_t size;
	jsmntok_t *tokens, *tok;
	int i, j, len;
	char *map;

	if (!fn)
		fn = json_default_name();
	tokens = parse_json(fn, &map, &size, &len);
	if (!tokens)
		return -EIO;
	EXPECT(tokens->type == JSMN_ARRAY, tokens, "expected top level array");
	tok = tokens + 1;
	for (i = 0; i < tokens->size; i++) {
		char *event = NULL, *desc = NULL, *name = NULL;
		struct msrmap *msr = NULL;
		jsmntok_t *msrval = NULL;
		jsmntok_t *precise = NULL;
		jsmntok_t *obj = tok++;

		EXPECT(obj->type == JSMN_OBJECT, obj, "expected object");
		for (j = 0; j < obj->size; j += 2) {
			jsmntok_t *field, *val;
			int nz;

			field = tok + j;
			EXPECT(field->type == JSMN_STRING, tok + j,
			       "Expected field name");
			val = tok + j + 1;
			EXPECT(val->type == JSMN_STRING, tok + j + 1,
			       "Expected string value");

			nz = !json_streq(map, val, "0");
			if (match_field(map, field, nz, &event, val)) {
				/* ok */
			} else if (json_streq(map, field, "EventName")) {
				addfield(map, &name, "", "", val);
			} else if (json_streq(map, field, "BriefDescription")) {
				addfield(map, &desc, "", "", val);
				fixdesc(desc);
			} else if (json_streq(map, field, "PEBS") && nz &&
				   !strstr(desc, "(Precise Event)")) {
				precise = val;
			} else if (json_streq(map, field, "MSRIndex") && nz) {
				msr = lookup_msr(map, val);
			} else if (json_streq(map, field, "MSRValue")) {
				msrval = val;
			} else if (json_streq(map, field, "Errata") &&
				   !json_streq(map, val, "null")) {
				addfield(map, &desc, ". ",
					" Spec update: ", val);
			} else if (json_streq(map, field, "Data_LA") && nz) {
				addfield(map, &desc, ". ",
					" Supports address when precise",
					NULL);
			}
			/* ignore unknown fields */
		}
		if (precise) {
			if (json_streq(map, precise, "2"))
				addfield(map, &desc, " ", "(Must be precise)",
						NULL);
			else
				addfield(map, &desc, " ",
						"(Precise event)", NULL);
		}
		if (msr != NULL)
			addfield(map, &event, ",", msr->pname, msrval);
		fixname(name);
		err = func(data, name, event, desc);
		free(event);
		free(desc);
		free(name);
		if (err)
			break;
		tok += j;
	}
	EXPECT(tok - tokens == len, tok, "unexpected objects at end");
	err = 0;
out_free:
	free_json(map, size, tokens);
	return err;
}