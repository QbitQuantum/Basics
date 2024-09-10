void jamoma_init(void)
{
    short		outvol = 0;
    t_fourcc	outtype, filetype = 'TEXT';
    char        name[MAX_PATH_CHARS], fullname[MAX_PATH_CHARS];
    
	if (!initialized) {
        
		t_object	*max = SymbolGen("max")->s_thing;
        TTString    JamomaConfigurationFilePath;
		t_atom		a[4];
		TTValue		v, out;
        TTErr       err;

		if (maxversion() < 1798)
        {
			error("Jamoma  %s  |  build %s can't run under Max version ealier than 7.0.6", JAMOMA_MAX_VERSION, JAMOMA_MAX_REV);
            return;
        }
        
		// Initialize the Modular library
        TTModularInit();
        
#ifdef TTSCORE_IMPORT
        // Initialize the Score framework
        TTScoreInit();
#endif
        
        // Prepare a symbol for Max application
        kTTSym_Max = TTSymbol("Max");
        
        // Create an application manager
        MaxApplicationManager = TTObject("ApplicationManager");
        
        // Create a local application called "Max" and get it back
        err = MaxApplicationManager.send("ApplicationInstantiateLocal", kTTSym_Max, out);
        
        if (err) {
            TTLogError("Error : can't create Jamoma application \n");
            return;
        }
        else
            MaxApplication = out[0];

        // check if the JamomaConfiguration.xml file exists
        strncpy_zero(name, "JamomaConfiguration.xml", MAX_PATH_CHARS);
        if (locatefile_extended(name, &outvol, &outtype, &filetype, 1))
            return error("Jamoma not loaded : can't find %s", name);
        
        path_topathname(outvol, name, fullname);


        // MaxApplication have to read JamomaConfiguration.xml
        TTObject anXmlHandler(kTTSym_XmlHandler);
        anXmlHandler.set(kTTSym_object, MaxApplication);
        std::string path = fullname;
        #if ( __APPLE__ )
        // remove drive name prefix
        size_t pos = path.find(":/");
        path = path.substr(pos+1);
       	v = TTSymbol(path);
        #else
        v = TTSymbol(fullname);
		#endif
        anXmlHandler.send(kTTSym_Read, v, out);

		// Initialize common symbols
		common_symbols_init();
		jamomaSymbolsInit();
		
		// Initialize common regex
		ttRegexForJmod = new TTRegex("(jmod.)");
		ttRegexForJcom = new TTRegex("(j\\.)");
		ttRegexForModel = new TTRegex("(.model)");
		ttRegexForModule = new TTRegex("(.module)");
		ttRegexForView = new TTRegex("(.view)");
		ttRegexForMaxpat = new TTRegex("(.maxpat)");
		ttRegexForMaxhelp = new TTRegex("(.maxhelp)");
		ttRegexForBracket = new TTRegex("\\[(\\d|\\d\\d|\\d\\d\\d)\\]");	// parse until 999
		
		ModelPatcherFormat = new TTString("%s.model.maxpat");
		ModelPresetFormat = new TTString("%s.model.presets.txt");
		ViewPresetFormat = new TTString("%s.view.presets.txt");
		HelpPatcherFormat = new TTString("%s.model");
		RefpageFormat = new TTString("%s.model");
		DocumentationFormat = new TTString("%s.model.html");
		
		// Create Required Global Instances
		hash_modules = (t_hashtab*)hashtab_new(0);
		// TODO: Use quittask_install() to set up a destructor for this to free it before Max exits

		// Add Jamoma Key Commands
		
		// J -- Jamoma: a new object box with "j." in it
		atom_setsym(a+0, SymbolGen("k"));
		atom_setsym(a+1, SymbolGen("patcher"));
		atom_setsym(a+2, SymbolGen("inserttextobj"));
		atom_setsym(a+3, SymbolGen("j."));
		object_method_typed(max, SymbolGen("definecommand"), 4, a, NULL);
				
//		// M -- Module: a new object box with ".model" in it
//		atom_setsym(a+0, SymbolGen("M"));
//		atom_setsym(a+1, SymbolGen("patcher"));
//		atom_setsym(a+2, SymbolGen("inserttextobj"));
//		atom_setsym(a+3, SymbolGen(".model"));
//		object_method_typed(max, SymbolGen("definecommand"), 4, a, NULL);
//        
		
//		// B -- BPatcher: a new module in a bpatcher
//		object_method_parse(max, SymbolGen("definecommand"), (char*)"B patcher inserttextobj \"bpatcher @name .module @args myModule\"", NULL);		

//		// D -- Demo: a new module in a bpatcher, but with the args reverse which is handy for super-fast demos when you don't care about the OSC name
//		object_method_parse(max, SymbolGen("definecommand"), (char*)"D patcher inserttextobj \"bpatcher @name .module\"", NULL);		

//		// X -- Continuous Mapper module
//		object_method_parse(max, SymbolGen("definecommand"), (char*)"X patcher insertobj bpatcher @name mapper.module.maxpat @args mapper", NULL);
				
		// now the jamoma object
		{
			t_symbol *jamomaSymbol = SymbolGen("jamoma");
		
			jamoma_object_initclass();
			jamomaSymbol->s_thing = jamoma_object_new();
		}
		
		post("Jamoma  %s  |  build %s", JAMOMA_MAX_VERSION, JAMOMA_MAX_REV );

		initialized = true;
	}
}