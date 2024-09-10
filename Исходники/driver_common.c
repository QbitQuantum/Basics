struct wowlan_triggers *
wpa_get_wowlan_triggers(const char *wowlan_triggers,
			const struct wpa_driver_capa *capa)
{
	struct wowlan_triggers *triggers;
	char *start, *end, *buf;
	int last;

	if (!wowlan_triggers)
		return NULL;

	buf = os_strdup(wowlan_triggers);
	if (buf == NULL)
		return NULL;

	triggers = os_zalloc(sizeof(*triggers));
	if (triggers == NULL)
		goto out;

#define CHECK_TRIGGER(trigger) \
	wpa_check_wowlan_trigger(start, #trigger,			\
				  capa->wowlan_triggers.trigger,	\
				  &triggers->trigger)

	start = buf;
	while (*start != '\0') {
		while (isblank((unsigned char) *start))
			start++;
		if (*start == '\0')
			break;
		end = start;
		while (!isblank((unsigned char) *end) && *end != '\0')
			end++;
		last = *end == '\0';
		*end = '\0';

		if (!CHECK_TRIGGER(any) &&
		    !CHECK_TRIGGER(disconnect) &&
		    !CHECK_TRIGGER(magic_pkt) &&
		    !CHECK_TRIGGER(gtk_rekey_failure) &&
		    !CHECK_TRIGGER(eap_identity_req) &&
		    !CHECK_TRIGGER(four_way_handshake) &&
		    !CHECK_TRIGGER(rfkill_release)) {
			wpa_printf(MSG_DEBUG,
				   "Unknown/unsupported wowlan trigger '%s'",
				   start);
			os_free(triggers);
			triggers = NULL;
			goto out;
		}

		if (last)
			break;
		start = end + 1;
	}
#undef CHECK_TRIGGER

out:
	os_free(buf);
	return triggers;
}