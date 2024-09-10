int
main (int argc, char **argv)
{
	int i ; 
	char *source_dir = NULL ;
	const char *destination_dir = NULL ;
	Bool do_data = False;
	ASDocType target_type = DocType_Source ;
	/* Save our program name - for error messages */
	set_DeadPipe_handler(DeadPipe);
    InitMyApp (CLASS_ASDOCGEN, argc, argv, NULL, asdocgen_usage, 0 );
	LinkAfterStepConfig();
	InitSession();
    for( i = 1 ; i< argc ; ++i)
	{
		LOCAL_DEBUG_OUT( "argv[%d] = \"%s\", original argv[%d] = \"%s\"", i, argv[i]?argv[i]:"(null)", i, MyArgs.saved_argv[i]);	  
		if( argv[i] != NULL  )
		{
			if( (strcmp( argv[i], "-t" ) == 0 || strcmp( argv[i], "--target" ) == 0) && i+1 < argc && argv[i+1] != NULL ) 
			{
				++i ;
				if( mystrcasecmp( argv[i], "plain" ) == 0 || mystrcasecmp( argv[i], "text" ) == 0) 
					target_type = DocType_Plain ; 														   
				else if( mystrcasecmp( argv[i], "html" ) == 0 ) 
					target_type = DocType_HTML ; 														   
				else if( mystrcasecmp( argv[i], "php" ) == 0 ) 
					target_type = DocType_PHP ; 														   
				else if( mystrcasecmp( argv[i], "xml" ) == 0 ) 
					target_type = DocType_XML ; 														   
				else if( mystrcasecmp( argv[i], "nroff" ) == 0 ) 
					target_type = DocType_NROFF ; 														   
				else if( mystrcasecmp( argv[i], "source" ) == 0 ) 
					target_type = DocType_Source ; 														   
				else
					show_error( "unknown target type \"%s\"" );
			}else if( (strcmp( argv[i], "-s" ) == 0 || strcmp( argv[i], "--css" ) == 0) && i+1 < argc && argv[i+1] != NULL ) 
			{
				++i ;				
				HTML_CSS_File = argv[i] ;
			}else if( strcmp( argv[i], "--faq-css" ) == 0 && i+1 < argc && argv[i+1] != NULL ) 
			{
				++i ;				
				FAQ_HTML_CSS_File = argv[i] ;
			}else if( strcmp( argv[i], "--html-data-back" ) == 0 && i+1 < argc && argv[i+1] != NULL ) 
			{
				++i ;				
				if( strcasecmp( argv[i], "none") == 0 ) 
					HTML_DATA_BACKGROUND_File = NULL ;
				else
					HTML_DATA_BACKGROUND_File = argv[i] ;
			}else if( (strcmp( argv[i], "-d" ) == 0 || strcmp( argv[i], "--data" ) == 0) ) 
			{
				do_data = True ;
			}else if( (strcmp( argv[i], "-S" ) == 0 || strcmp( argv[i], "--source" ) == 0) && i+1 < argc && argv[i+1] != NULL ) 
			{
				++i ;				
				source_dir = argv[i] ;
			}else if( (strcmp( argv[i], "-D" ) == 0 || strcmp( argv[i], "--dst" ) == 0) && i+1 < argc && argv[i+1] != NULL ) 
			{
				++i ;				
				destination_dir = argv[i] ;
			}
		}
	}		  
	if( destination_dir == NULL ) 
		destination_dir = do_data?"data":ASDocTypeExtentions[target_type] ;
	if( source_dir == NULL ) 
		source_dir = do_data?"../../afterstep":"source" ;

#if 0

    ConnectAfterStep ( mask_reg, 0);
	
  	SendInfo ( "Nop \"\"", 0);
#endif
	ProcessedSyntaxes = create_ashash( 7, pointer_hash_value, NULL, NULL );
	Glossary = create_ashash( 4096, string_hash_value, string_compare, string_destroy );
	Index = create_ashash( 4096, string_hash_value, string_compare, string_destroy );
	UserLinks = create_ashash( 4096, string_hash_value, string_compare, string_destroy );
	APILinks = create_ashash( 4096, string_hash_value, string_compare, string_destroy );

	Links = UserLinks;

	GlossaryName = UserGlossaryName ; 
	TopicIndexName = UserTopicIndexName ; 

	if( target_type < DocType_Source )
	{	
		time_t curtime;
    	struct tm *loctime;
		
		DocBookVocabulary = create_ashash( 7, casestring_hash_value, casestring_compare, string_destroy_without_data );
		for( i = 1 ; i < DOCBOOK_SUPPORTED_IDS ; ++i )
			add_hash_item( DocBookVocabulary, AS_HASHABLE(SupportedDocBookTagInfo[i].tag), (void*)(SupportedDocBookTagInfo[i].tag_id));
		
		/* Get the current time. */
		curtime = time (NULL);
     	/* Convert it to local time representation. */
		loctime = localtime (&curtime);
		strftime(CurrentDateLong, DATE_SIZE, "%b %e %Y", loctime);
		strftime(CurrentDateShort, DATE_SIZE, "%m/%d/%Y", loctime);
	}
	i = 0 ; 
	LOCAL_DEBUG_OUT( "Starting main action... %s", "" );
	
	if( target_type >= DocType_Source ) /* 1) generate HTML doc structure */
	{
		while( TopLevelSyntaxes[i] )
		{	/* create directory structure for source docs and all the missing files */
			check_syntax_source( source_dir, TopLevelSyntaxes[i], (i >= MODULE_SYNTAX_START) );
			++i ;	
		}
		check_syntax_source( source_dir, NULL, True );
	}else if( do_data )
	{	
		char *env_path1 = NULL, *env_path2 = NULL ;
		ASColorScheme *cs = NULL ;
		
	    if ((dpy = XOpenDisplay (MyArgs.display_name)))
		{
			set_current_X_display (dpy);
			Scr.MyDisplayWidth = DisplayWidth (dpy, Scr.screen);
			Scr.MyDisplayHeight = DisplayHeight (dpy, Scr.screen);

		    Scr.asv = create_asvisual (dpy, Scr.screen, DefaultDepth(dpy,Scr.screen), NULL);
		}else
		{		    
			Scr.asv = create_asvisual(NULL, 0, 32, NULL);
		}
		
		asxml_var_insert("xroot.width", 640);
    	asxml_var_insert("xroot.height", 480);
		
		env_path1 = getenv( "IMAGE_PATH" ) ;
		env_path2 = getenv( "PATH" );
		if( env_path1 == NULL ) 
		{
			env_path1 = env_path2;
			env_path2 = NULL ;
		}
	    Scr.image_manager = create_image_manager( NULL, 2.2, env_path1, env_path2, NULL );
		set_xml_image_manager( Scr.image_manager );
        
		env_path1 = getenv( "FONT_PATH" ) ;
		Scr.font_manager = create_font_manager( dpy, env_path1, NULL );
		set_xml_font_manager( Scr.font_manager );

		/*ReloadASEnvironment( NULL, NULL, NULL, False ); */
		cs = make_default_ascolor_scheme();
		populate_ascs_colors_rgb( cs );
		populate_ascs_colors_xml( cs );
		free( cs );

		TopicIndexName = NULL ;
		
		CurrHtmlBackFile = HTML_DATA_BACKGROUND_File ;
		gen_data_doc( 	source_dir, destination_dir?destination_dir:"data", "",
			  		  	"Installed data files - fonts, images and configuration",
			  			target_type );

		flush_ashash( Glossary );
		flush_ashash( Index );
	}else
	{
		char *api_dest_dir ;
		api_dest_dir = make_file_name( destination_dir, "API" );
		
		GlossaryName = UserGlossaryName ; 
		TopicIndexName = UserTopicIndexName ; 
		Links = UserLinks;

		DocGenerationPass = 2 ;
		while( --DocGenerationPass >= 0 ) 
		{
			gen_code_doc( "../../libAfterImage", destination_dir, 
			  		  	"asimagexml.c", 
			  		  	"AfterImage XML",
			  		  	"XML schema to be used for scripting image manipulation by AfterStep and ascompose",
			  		  	target_type );
		
			/* we need to generate some top level files for afterstep itself : */
			gen_syntax_doc( source_dir, destination_dir, NULL, target_type );
		
			for( i = 0 ; TopLevelSyntaxes[i] ; ++i )
				gen_syntax_doc( source_dir, destination_dir, TopLevelSyntaxes[i], target_type );
			
			if( DocGenerationPass == 0 ) 
			{	
				gen_faq_doc( source_dir, destination_dir, target_type );
				gen_glossary( destination_dir, "Glossary", target_type );
				gen_index( destination_dir, "index", target_type, True );
			}
			flush_ashash( ProcessedSyntaxes );
		}
		flush_ashash( Glossary );
		flush_ashash( Index );
		
		GlossaryName = APIGlossaryName ; 
		TopicIndexName = APITopicIndexName ; 
		Links = APILinks;
		DocGenerationPass = 2 ;
		
		CurrentManType = 3 ;
		
		while( --DocGenerationPass >= 0 ) 
		{
			int s ;
			for( s = 0 ; libAfterImage_Sources[s].src_file != NULL ; ++s ) 
			{	
				gen_code_doc( 	"../../libAfterImage", api_dest_dir, 
			  			  		libAfterImage_Sources[s].src_file, 
			  			  		libAfterImage_Sources[s].descr_short,
			  		  			libAfterImage_Sources[s].descr_long,
			  		  			target_type );
			}
			if( DocGenerationPass == 0 ) 
			{	
				gen_glossary( api_dest_dir, "Glossary", target_type );
				gen_index( api_dest_dir, "index", target_type, False );
			}
			flush_ashash( Glossary );
			flush_ashash( Index );
		}		  


	}		 
	
	if( dpy )   
    	XCloseDisplay (dpy);
    return 0;
}