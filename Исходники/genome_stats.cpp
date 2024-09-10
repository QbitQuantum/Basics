int main( int argc, char* argv[] )
{
  // ---------------------------------------
  //      command-line option parsing
  // ---------------------------------------
  // Initialize command-line option variables with default values
  char* backup_file_name           = NULL;
  char* main_output_name           = NULL;
  char* neutral_region_output_name = NULL;
  bool best_only = false;
  
  // Define allowed options
  const char * options_list = "hf:o:bn:";
  static struct option long_options_list[] =
  {
    { "help", 0, NULL, 'h' },
    { "file", 1, NULL, 'f' },
    { "output", 1, NULL, 'o' },
    { "best", 0, NULL, 'b' },
    { "neutral", 0, NULL, 'n' },
    { 0, 0, 0, 0 }
  };

  // Get actual values of the command-line options
  int option;
  while ( ( option = getopt_long(argc, argv, options_list, long_options_list, NULL) ) != -1 ) 
  {
    switch ( option ) 
    {
    case 'h' :
      print_help( argv[0] );
      exit( EXIT_SUCCESS );
      break;
    case 'f' :
      backup_file_name = new char[strlen(optarg) + 1];
      sprintf( backup_file_name, "%s", optarg );
      break;
    case 'o' :
      main_output_name = new char[strlen(optarg) + 1];
      sprintf( main_output_name, "%s", optarg );
      break;
    case 'n' :
      neutral_region_output_name = new char[strlen(optarg) + 1];
      sprintf( neutral_region_output_name, "%s", optarg );
      break;
    case 'b' :
      best_only = true;
      break;
    }
  }
  
  // -------------------------------
  //          Initialize
  // -------------------------------
  FILE* main_output           = NULL;
  FILE* neutral_region_output = NULL;
  
  if ( backup_file_name == NULL )
  {
    printf("You must specify a backup file. Please use the option -f or --file.\n");
    exit(EXIT_FAILURE);
  }
  if ( main_output_name != NULL )
  {
    main_output = fopen(main_output_name,"w");
    if ( main_output == NULL)
    {
      fprintf( stderr, "Warning: Could not open file %s.\n", main_output_name );
    }
  }
  if ( neutral_region_output_name != NULL )
  {
    neutral_region_output = fopen(neutral_region_output_name,"w");
    if ( neutral_region_output == NULL)
    {
      fprintf( stderr, "Warning: Could not open file %s.\n", neutral_region_output_name );
    }
  }
  fflush( stderr );

  printf( "Reading backup file <%s>... \n", backup_file_name );
  fflush( stdout );

  // Load the simulation from backup
  ae_common::sim = new ae_experiment();
  ae_common::sim->load_backup( backup_file_name, false, NULL );
  printf("done\n");
  delete [] backup_file_name;

  printf( "Computing phenotypes... \n" );
  fflush( stdout );

  // Evaluate the individuals
  ae_common::pop->evaluate_individuals(ae_common::sim->get_env());
  
  int i = 0;
  int nb_indiv = ae_common::pop->get_nb_indivs();

  // --------------------------------
  //         Parse individuals
  // --------------------------------
  if (best_only)
  {
    ae_individual* best = ae_common::pop->get_best();
    if ( main_output != NULL)           { print_genome_info(best, main_output); }
    if ( neutral_region_output != NULL) { print_neutral_regions(best, neutral_region_output); }
  }
  else
  {
    if (ae_common::pop_structure)
    {
      ae_grid_cell*** _pop_grid = ae_common::pop->get_pop_grid();
      for ( int16_t x = 0 ; x < ae_common::grid_x ; x++ )
      {
        for ( int16_t y = 0 ; y < ae_common::grid_y ; y++ )
        {
          ae_individual* indiv = (_pop_grid[x][y]->get_individual());
	  if ( main_output != NULL)           { print_genome_info(indiv, main_output); }
	  if ( neutral_region_output != NULL) { print_neutral_regions(indiv, neutral_region_output); }
          i++;
        }  
      }
    }
    else
    {
      ae_list_node  * indiv_node = ae_common::pop->get_indivs()->get_first();
      ae_individual * indiv      = NULL;

      while( indiv_node != NULL )
      {
        indiv = (ae_individual *) indiv_node->get_obj();
        if ( main_output != NULL)           { print_genome_info(indiv, main_output); }
	if ( neutral_region_output != NULL) { print_neutral_regions(indiv, neutral_region_output); }
        indiv_node = indiv_node->get_next();
	i++;
      }
    }
  }
  
  if ( main_output != NULL ) { fclose(main_output); }
  if ( neutral_region_output != NULL ) { fclose(neutral_region_output); }

  if ( main_output_name != NULL )           { delete [] main_output_name; }
  if ( neutral_region_output_name != NULL ) { delete [] neutral_region_output_name; }
  
  ae_common::clean();
  
  return EXIT_SUCCESS;
}