void model_preset_dowrite(TTPtr self, t_symbol *msg, long argc, t_atom *argv)
{
	WrappedModularInstancePtr	x = (WrappedModularInstancePtr)self;
	char 			filename[MAX_FILENAME_CHARS];
	TTSymbol		fullpath;
	TTValue			o, v, none;
	TTObject        aTextHandler;
	TTErr			tterr;

	// stop filewatcher
	if (EXTRA->filewatcher)
		filewatcher_stop(EXTRA->filewatcher);

	if (EXTRA->presetManager->valid()) {

		// Default TEXT File Name
		snprintf(filename, MAX_FILENAME_CHARS, "%s.%s.presets.txt", x->patcherClass.c_str(), x->patcherContext.c_str());
		fullpath = jamoma_file_write((t_object*)x, argc, argv, filename);
		v.append(fullpath);

		tterr = x->internals->lookup(kTTSym_TextHandler, o);

		if (!tterr) {
			aTextHandler = o[0];

			aTextHandler.set(kTTSym_object, *EXTRA->presetManager);

			critical_enter(0);
			tterr = aTextHandler.send(kTTSym_Write, v, none);
			critical_exit(0);

			if (!tterr)
				object_obex_dumpout(self, _sym_write, argc, argv);
			else
				object_obex_dumpout(self, _sym_error, 0, NULL);
		}
	}

	// start filewatcher
	if (EXTRA->filewatcher)
		filewatcher_start(EXTRA->filewatcher);
}