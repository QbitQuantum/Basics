int main(int argc, char* argv[])
{

    get_arguments (argc, argv);

    // figure out which chromosomes I want
    for (int i=0; i < num_chroms; i++)
    {
        chromosome[i] = 0;
    }
    char *token;
    //char locus_coord[] = "locus_coord.txt";
    
    token = strtok(chrom_string,",");
    while (token != NULL)
    {
        int index = atoi(token) - 1;
        chromosome[index] = 1;
        token = strtok(NULL,",");
    }

    // the max_dist is per kb, so adjust it so that it depends on the resolution
    max_dist = max_dist * bp_per_locus / 1000.0;
    // same for min_dist
    min_dist = min_dist * bp_per_locus / 1000.0;

    // Create a new instance of your nlp
    GENOME *mygenome = new GENOME(bp_per_locus, min_dist, max_dist,
                                  interactions_filename, chromosome, add_rDNA,
                                  rDNA_interactions_filename, use_weights,
                                  unseen_interactions_filename,
                                  frequencies_distances_filename,
                                  structure_filename);

    // If a temporary pdb file exists, upload it and initialize the problem
    // there

    char temp_filename[1000];
    sprintf(temp_filename, "%s.temp.txt", output_pdb);
    FILE* file = fopen(temp_filename, "r");
    if(file == 0){
      printf("No temporary file - starting optimization from scratch\n");
    }else{
      fclose(file);
      mygenome->read_txt_input(temp_filename);
    }

    if (strcmp (input_txt, "") != 0)
    {
        printf ("Reading the txt input\n");
        mygenome->read_txt_input(input_txt);
        mygenome->print_pdb_genome(output_pdb);
        if(strcmp(locus_coord,"") != 0){
            mygenome->print_1D_3D_genome(locus_coord);
        }
        return 1;
    }
    else if (strcmp (output_binary_diffusion, "") != 0)
    {
        mygenome->save_adjacency_matrix_for_diffusion(
                output_binary_diffusion,
                diffusion_operation_type);
        return 1;
    }
    else if (strcmp (output_cplex_input, "") != 0)
    // just write the .lp file for cplex
    {
        SmartPtr<genome_ipopt_nlp> mynlp = new genome_ipopt_nlp(
                                                  mygenome, min_clash_dist,
                                                  min_clash_dist_inter,
                                                  output_pdb, sphere_radius,
                                                  use_weights, bp_per_locus,
                                                  rDNA_frequency_normalizer,
                                                  weight_of_inter,
                                                  weight_unseen, true,
                                                  alpha, beta, locus_coord);
        mynlp->write_cplex_input (output_cplex_input);
        return 1;
    }
    else if (strcmp (input_cplex_output, "") != 0)
    // read the file in .sol format (cplex output) and write a pdb file
    {
        mygenome->read_cplex_output(input_cplex_output);
        mygenome->print_pdb_genome(output_pdb);
        if(strcmp (locus_coord,"") != 0){
            mygenome->print_1D_3D_genome(locus_coord);
        }
        return 1;
    }
  //mygenome->save_interaction_adjacency_matrix (initial_interaction_matrix);
  //mygenome->print_pdb_genome (initial_pdb);

  // FIXME we haven't interfaced many of the options.
  SmartPtr<TNLP> mynlp = new genome_ipopt_nlp(
                              mygenome, min_clash_dist, min_clash_dist_inter,
                              output_pdb, sphere_radius, use_weights,
                              bp_per_locus, rDNA_frequency_normalizer,
                              weight_of_inter, weight_unseen, true, alpha, beta, locus_coord
                              );

  // Create a new instance of IpoptApplication
  //  (use a SmartPtr, not raw)
  SmartPtr<IpoptApplication> app = new IpoptApplication();

  // Change some options
  // Note: The following choices are only examples, they might not be
  //       suitable for your optimization problem.
  app->Options()->SetNumericValue("tol", 1e-1);
  app->Options()->SetNumericValue("acceptable_tol", 1e-1);
  // I'm going to set the constraint violation to very very high.
  app->Options()->SetNumericValue("constr_viol_tol", 1e10);
  app->Options()->SetNumericValue("mu_init", 0.0001);
  // This is super high. It should not impact the results
  app->Options()->SetNumericValue("dual_inf_tol", 10000);
  app->Options()->SetNumericValue("compl_inf_tol", 1000000);
  // This should be zero.
  app->Options()->SetIntegerValue("acceptable_iter", 0);

  app->Options()->SetIntegerValue("max_iter", 100000);

  //app->Options()->SetStringValue("mu_strategy", "monotone");
  app->Options()->SetStringValue("mu_strategy", "adaptive");
  app->Options()->SetStringValue("output_file", logging_filename);
  app->Options()->SetStringValue("hessian_approximation", "limited-memory");

  // The following overwrites the default name (ipopt.opt) of the
  // options file
  // app->Options()->SetStringValue("option_file_name", "hs071.opt");

  // Intialize the IpoptApplication and process the options
  ApplicationReturnStatus status;
  status = app->Initialize();
  if (status != Solve_Succeeded) {
    printf("\n\n*** Error during initialization!\n");
    return (int) status;
  }

  // Ask Ipopt to solve the problem
  status = app->OptimizeTNLP(mynlp);

  if (status == Solve_Succeeded || status == Solved_To_Acceptable_Level) {
    printf("\n\n*** The problem solved!\n");
  }
  else {
    printf("\n\n*** The problem FAILED!\n");
    exit(1);
  }

  // As the SmartPtrs go out of scope, the reference count
  // will be decremented and the objects will automatically
  // be deleted.

  return 1;     //(int) status;

}