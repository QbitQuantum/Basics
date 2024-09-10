static inline 
int create_subtasks(cluster_t *cl, int tid, proc_t *procinfo, 
		    rrr_t *RRR, val_t *Wstruct, vec_t *Zstruct,
		    workQ_t *workQ, counter_t *num_left)
{
  /* From inputs */
  int              cl_begin  = cl->begin;
  int              cl_end    = cl->end;
  int              depth     = cl->depth;
  int              bl_begin  = cl->bl_begin;
  int              bl_end    = cl->bl_end;
  int              bl_size   = bl_end - bl_begin + 1;
  double           bl_spdiam = cl->bl_spdiam;
  double           lgap;

  int              pid       = procinfo->pid;
  int              nproc     = procinfo->nproc;
  int              nthreads  = procinfo->nthreads;

  double *restrict Wgap      = Wstruct->Wgap;
  double *restrict Wshifted  = Wstruct->Wshifted;
  int    *restrict iproc     = Wstruct->iproc;

  int              ldz       = Zstruct->ldz;
  double *restrict Z         = Zstruct->Z;
  int    *restrict Zindex    = Zstruct->Zindex;

  /* others */
  int    i, l;
  int    max_size;
  task_t *task;
  bool   task_inserted;
  int    new_first, new_last, new_size, new_ftt1, new_ftt2;
  int    sn_first, sn_last, sn_size;
  rrr_t  *RRR_parent;
  int    new_lpid, new_rpid;
  double *restrict D_parent;
  double *restrict L_parent;
  int    my_first, my_last;
  bool   copy_parent_rrr;


  max_size = fmax(1, PMR_get_counter_value(num_left) /
		     (fmin(depth+1,4)*nthreads) );
  task_inserted = true;
  new_first = cl_begin;
  for (i=cl_begin; i<=cl_end; i++) {    

    if ( i == cl_end )
      new_last = i;
    else if ( Wgap[i] >= MIN_RELGAP*fabs(Wshifted[i]) )
      new_last = i;
    else
      continue;

    new_size = new_last - new_first + 1;

    if (new_size == 1) {
      /* singleton was found */
      
      if (new_first==cl_begin || task_inserted==true) {
	/* initialize new singleton task */
	sn_first = new_first;
	sn_last  = new_first;
	sn_size  = 1;
      } else {
	/* extend singleton task by one */
	sn_last++;
	sn_size++;
      }
      
      /* insert task if ... */
      if (i==cl_end || sn_size>=max_size ||
	    Wgap[i+1] < MIN_RELGAP*fabs(Wshifted[i+1])) {

	if (sn_first == cl_begin) {
	  lgap = cl->lgap;
	} else {
	  lgap = Wgap[sn_first-1];
	}
	
	PMR_increment_rrr_dependencies(RRR);
	
	task = PMR_create_s_task(sn_first, sn_last, depth+1, bl_begin,
				 bl_end, bl_spdiam, lgap, RRR);
	
	PMR_insert_task_at_back(workQ->s_queue, task);
	  
	task_inserted = true;
      } else {
	task_inserted = false;
      }
      
    } else {
      /* cluster was found */

      /* check if process involved in processing the new cluster */
      new_lpid = nproc-1;
      new_rpid = 0;
      for (l=new_first; l<=new_last; l++) {
	if (iproc[l] != -1) {
	  new_lpid = imin(new_lpid, iproc[l]);
	  new_rpid = imax(new_rpid, iproc[l]);
	  }
      }
      if (new_lpid > pid || new_rpid < pid) {
	task_inserted = true;
	new_first = i + 1;
	continue;
      }

      /* find gap to the left */
      if (new_first == cl_begin) {
	lgap = cl->lgap;
      } else {
	lgap = Wgap[new_first - 1];
      }
    
      /* determine where to store the parent rrr needed by the
       * cluster to find its new rrr */
      my_first = imax(new_first, cl->proc_W_begin);
      my_last  = imin(new_last,  cl->proc_W_end);
      if ( my_first == my_last ) {
	/* only one eigenvalue of cluster belongs to process */
	copy_parent_rrr = true;
      } else {
	/* store parent rrr in Z at column new_ftt */
	copy_parent_rrr = false;
      }
      new_ftt1 = Zindex[my_first    ];
      new_ftt2 = Zindex[my_first + 1];

      if (copy_parent_rrr == true) {
	/* Copy parent RRR into alloceted arrays and mark them
	 * for freeing later */
	D_parent = (double *) malloc(bl_size * sizeof(double));
	assert(D_parent != NULL);
	
	L_parent = (double *) malloc(bl_size * sizeof(double));
	assert(L_parent != NULL);

	memcpy(D_parent, RRR->D, bl_size*sizeof(double));
	memcpy(L_parent, RRR->L, bl_size*sizeof(double));

	RRR_parent = PMR_create_rrr(D_parent, L_parent, NULL, 
				    NULL, bl_size, depth);
	PMR_set_copied_parent_rrr_flag(RRR_parent, true);

      } else {
	/* copy parent RRR into Z to make cluster task independent */
	memcpy(&Z[new_ftt1*ldz+bl_begin], RRR->D, 
	       bl_size*sizeof(double));
	memcpy(&Z[new_ftt2*ldz+bl_begin], RRR->L, 
	       bl_size*sizeof(double));

	RRR_parent = PMR_create_rrr(&Z[new_ftt1*ldz + bl_begin],
				    &Z[new_ftt2*ldz + bl_begin],
				    NULL, NULL, bl_size, depth);
      }
      
      /* Create the task for the cluster and put it in the queue */ 
      task = PMR_create_c_task(new_first, new_last, depth+1, 
			       bl_begin, bl_end, bl_spdiam, lgap, 
			       cl->proc_W_begin, cl->proc_W_end, 
			       new_lpid, new_rpid, RRR_parent);

      if (new_lpid != new_rpid)
	PMR_insert_task_at_back(workQ->r_queue, task);
      else
	PMR_insert_task_at_back(workQ->c_queue, task);

      task_inserted = true;
      
    } /* if singleton or cluster found */

    new_first = i + 1;
  } /* end i */
  
  /* set flag in RRR that last singleton is created */
  PMR_set_parent_processed_flag(RRR);
  
  /* clean up */
  PMR_try_destroy_rrr(RRR);
  free(cl);

  return(0);
} /* end create_subtasks */