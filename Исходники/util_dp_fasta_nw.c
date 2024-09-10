int cfasta_gotoh_pair_wise (Alignment *A,int*ns, int **l_s,Constraint_list *CL)
    {
/*TREATMENT OF THE TERMINAL GAP PENALTIES*/
/*TG_MODE=0---> gop and gep*/
/*TG_MODE=1---> ---     gep*/
/*TG_MODE=2---> ---     ---*/


	int maximise;

/*VARIABLES FOR THE MULTIPLE SEQUENCE ALIGNMENT*/
	int **tot_diag;

	int *diag;
	int ktup;
	static int n_groups;
	static char **group_list;
	int score, new_score;
        int n_chosen_diag=20;
        int step;
	int max_n_chosen_diag;
	int l1, l2;
        /********Prepare Penalties******/


	maximise=CL->maximise;
	ktup=CL->ktup;

	/********************************/




	if ( !group_list)
	   {

	       group_list=make_group_aa (&n_groups, CL->matrix_for_aa_group);
	   }

	l1=strlen (A->seq_al[l_s[0][0]]);
	l2=strlen (A->seq_al[l_s[1][0]]);

	if ( !CL->fasta_step)
	    {
	    step=MIN(l1,l2);
	    step=(int) log ((double)MAX(step, 1));
	    step=MAX(step, 20);
	    }
	else
	    {
		step=CL->fasta_step;
	    }


	tot_diag=evaluate_diagonals ( A, ns, l_s, CL, maximise,n_groups,group_list, ktup);


	max_n_chosen_diag=strlen (A->seq_al[l_s[0][0]])+strlen (A->seq_al[l_s[1][0]])-1;
	/*max_n_chosen_diag=(int)log10((double)(l1+l2))*10;*/

	n_chosen_diag+=step;
	n_chosen_diag=MIN(n_chosen_diag, max_n_chosen_diag);


	diag=extract_N_diag (strlen (A->seq_al[l_s[0][0]]),strlen (A->seq_al[l_s[1][0]]), tot_diag, n_chosen_diag, 0);


	score    =make_fasta_gotoh_pair_wise ( A, ns, l_s, CL, diag);

	new_score=0;
	vfree ( diag);


	while (new_score!=score && n_chosen_diag< max_n_chosen_diag    )
	  {


	    score=new_score;

	    ungap_sub_aln ( A, ns[0], l_s[0]);
	    ungap_sub_aln ( A, ns[1], l_s[1]);


	    n_chosen_diag+=step;
	    n_chosen_diag=MIN(n_chosen_diag, max_n_chosen_diag);


	    diag     =extract_N_diag (strlen (A->seq_al[l_s[0][0]]),strlen (A->seq_al[l_s[1][0]]), tot_diag, n_chosen_diag, 0);
	    new_score=make_fasta_gotoh_pair_wise (  A, ns, l_s, CL, diag);

	    vfree ( diag);

	  }

	score=new_score;
	free_int (tot_diag, -1);

	return score;
    }