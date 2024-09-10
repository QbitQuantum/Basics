void cue_edit(TTPtr self, t_symbol *msg, long argc, const t_atom *argv)
{
	WrappedModularInstancePtr	x = (WrappedModularInstancePtr)self;
	TTString			*buffer;
	char				title[MAX_FILENAME_CHARS];
	TTObject            aTextHandler;
	TTHashPtr			allCues;
	TTValue				v, o;
	TTSymbol			name = kTTSymEmpty;
    t_atom				a;
	TTErr				tterr;
	
	// choose object to edit : default the cuelist
	*EXTRA->toEdit = x->wrappedObject;
	EXTRA->cueName = kTTSymEmpty;
	
	if (argc && argv)
    {
		if (atom_gettype(argv) == A_LONG)
        {
            TTUInt32 index = atom_getlong(argv);
			
			// get cues names
			x->wrappedObject.get("names", v);
			
			if (index > 0 && index <= v.size())
				name = v[index-1];
			else
            {
				object_error((t_object*)x, "%d doesn't exist", atom_getlong(argv));
				return;
			}
		}
		else if (atom_gettype(argv) == A_SYM)
			name = TTSymbol(atom_getsym(argv)->s_name);
		
		if (name != kTTSymEmpty)
        {
			// get cue object table
			x->wrappedObject.get("cues", v);
			allCues = TTHashPtr((TTPtr)v[0]);
			
			if (allCues)
            {
				// get cue to edit
				if (!allCues->lookup(name, v))
                {
					// edit a cue
					*EXTRA->toEdit = v[0];
					EXTRA->cueName = name;
				}
				else
                {
					object_error((t_object*)x, "%s doesn't exist", atom_getsym(argv)->s_name);
					return;
				}
			}
		}
	}
	
	// only one editor can be open in the same time
	if (!EXTRA->textEditor) {
		
		EXTRA->textEditor = (t_object*)object_new(_sym_nobox, _sym_jed, x, 0);
		
		buffer = new TTString();
		
		// get the buffer handler
		tterr = x->internals->lookup(kTTSym_TextHandler, o);
		
		if (!tterr) {
			
			aTextHandler = o[0];
			
			critical_enter(0);
			aTextHandler.set(kTTSym_object, *EXTRA->toEdit);
			tterr = aTextHandler.send(kTTSym_Write, (TTPtr)buffer);
			critical_exit(0);
		}
		
		// pass the buffer to the editor
		object_method(EXTRA->textEditor, _sym_settext, buffer->c_str(), _sym_utf_8);
		object_attr_setchar(EXTRA->textEditor, gensym("scratch"), 1);
		
		snprintf(title, MAX_FILENAME_CHARS, "cuelist editor");
		object_attr_setsym(EXTRA->textEditor, _sym_title, gensym(title));
        
        // output a flag
        atom_setsym(&a, gensym("opened"));
        object_obex_dumpout(self, gensym("editor"), 1, &a);
		
		buffer->clear();
		delete buffer;
		buffer = NULL;
	}
    else
    {
        object_attr_setchar(EXTRA->textEditor, gensym("visible"), 1);
    }
}