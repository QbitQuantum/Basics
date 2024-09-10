static void
finch_sound_play_file(const char *filename)
{
	const char *method;
#ifdef USE_GSTREAMER
	float volume;
	char *uri;
	GstElement *sink = NULL;
	GstElement *play = NULL;
	GstBus *bus = NULL;
#endif
	if (purple_prefs_get_bool(make_pref("/mute")))
		return;

	method = purple_prefs_get_string(make_pref("/method"));

	if (!strcmp(method, "nosound")) {
		return;
	} else if (!strcmp(method, "beep")) {
		beep();
		return;
	}

	if (!g_file_test(filename, G_FILE_TEST_EXISTS)) {
		purple_debug_error("gntsound", "sound file (%s) does not exist.\n", filename);
		return;
	}

#ifndef _WIN32
	if (!strcmp(method, "custom")) {
		const char *sound_cmd;
		char *command;
		char *esc_filename;
		GError *error = NULL;

		sound_cmd = purple_prefs_get_path(make_pref("/command"));

		if (!sound_cmd || *sound_cmd == '\0') {
			purple_debug_error("gntsound",
					 "'Command' sound method has been chosen, "
					 "but no command has been set.");
			return;
		}

		esc_filename = g_shell_quote(filename);

		if (strstr(sound_cmd, "%s"))
			command = purple_strreplace(sound_cmd, "%s", esc_filename);
		else
			command = g_strdup_printf("%s %s", sound_cmd, esc_filename);

		if (!g_spawn_command_line_async(command, &error)) {
			purple_debug_error("gntsound", "sound command could not be launched: %s\n", error->message);
			g_error_free(error);
		}

		g_free(esc_filename);
		g_free(command);
		return;
	}
#ifdef USE_GSTREAMER
	if (gst_init_failed)  /* Perhaps do beep instead? */
		return;
	volume = (float)(CLAMP(purple_prefs_get_int(make_pref("/volume")), 0, 100)) / 50;
	if (!strcmp(method, "automatic")) {
		if (purple_running_gnome()) {
			sink = gst_element_factory_make("gconfaudiosink", "sink");
		}
		if (!sink)
			sink = gst_element_factory_make("autoaudiosink", "sink");
		if (!sink) {
			purple_debug_error("sound", "Unable to create GStreamer audiosink.\n");
			return;
		}
	} else if (!strcmp(method, "esd")) {
		sink = gst_element_factory_make("esdsink", "sink");
		if (!sink) {
			purple_debug_error("sound", "Unable to create GStreamer audiosink.\n");
			return;
		}
	} else if (!strcmp(method, "alsa")) {
		sink = gst_element_factory_make("alsasink", "sink");
		if (!sink) {
			purple_debug_error("sound", "Unable to create GStreamer audiosink.\n");
			return;
		}
	} else {
		purple_debug_error("sound", "Unknown sound method '%s'\n", method);
		return;
	}

	play = gst_element_factory_make("playbin", "play");

	if (play == NULL) {
		return;
	}

	uri = g_strdup_printf("file://%s", filename);

	g_object_set(G_OBJECT(play), "uri", uri,
		                     "volume", volume,
		                     "audio-sink", sink, NULL);

	bus = gst_pipeline_get_bus(GST_PIPELINE(play));
	gst_bus_add_watch(bus, bus_call, play);

	gst_element_set_state(play, GST_STATE_PLAYING);

	gst_object_unref(bus);
	g_free(uri);

#else /* USE_GSTREAMER */
	beep();
	return;
#endif /* USE_GSTREAMER */
#else /* _WIN32 */
	purple_debug_info("sound", "Playing %s\n", filename);

	{
		wchar_t *wc_filename = g_utf8_to_utf16(filename,
				-1, NULL, NULL, NULL);
		if (!PlaySoundW(wc_filename, NULL, SND_ASYNC | SND_FILENAME))
			purple_debug(PURPLE_DEBUG_ERROR, "sound", "Error playing sound.\n");
		g_free(wc_filename);
	}
#endif /* _WIN32 */
}