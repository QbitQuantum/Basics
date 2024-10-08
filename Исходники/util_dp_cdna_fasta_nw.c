Dp_Result * make_fast_dp_pair_wise (Alignment *A,int*ns, int **l_s, Constraint_list *CL,Dp_Model *M)
	{
	  
	  /*SIZE VARIABLES*/ 
	  
	  int ndiag;
	  int l0, l1, len_al,len_diag;
	  static int max_len_al, max_len_diag;
	  static int mI, mJ;
	 
	  
	  /*EVALUATION*/
	  int **mat;
	  int a1, a2;
	  
	  /*DP VARIABLES*/
	  static int *Mat, *LMat, *trace;
	  int a, i, j,l;
	  int state, cur_state, prev_state;
	  int pos_i,  pos_j;
	  int last_i=0, last_j=0;
	  int prev_i, prev_j;
	  int len_i, len_j, len;
	  int t, e, em;
	  
	  int prev_score; 
	  int pc, best_pc;
	  
	  int *prev;
	  int model_index;
	  /*TRACEBACK*/
	  Dp_Result *DPR;
	  int k=0, next_k;
	  int new_i, new_j;
	  
	  
	  ndiag=M->diag[0];

	  l0=strlen (A->seq_al[l_s[0][0]]);
	  l1=strlen (A->seq_al[l_s[1][0]]);
	  len_al =l0+l1+1;	
	  len_diag=ndiag+4;
	  
	  if ( (len_al>max_len_al || len_diag>max_len_diag))
	    {
	      
	      vfree (Mat);
	      vfree (LMat);
	      vfree(trace);	    
	      max_len_diag=max_len_al=0;	   
	    }
	  
	  if (max_len_al==0)
	    {
	      max_len_al=len_al;
	      max_len_diag=len_diag;
	      mI=max_len_al*max_len_diag;
	      mJ=max_len_diag;
	      
	      
	      Mat  =vcalloc ( M->nstate*max_len_al*max_len_diag, sizeof (int));
	      LMat =vcalloc ( M->nstate*max_len_al*max_len_diag, sizeof (int));
	      trace=vcalloc ( M->nstate*max_len_al*max_len_diag, sizeof (int));
	      
	    }
	  
	  prev=vcalloc ( M->nstate, sizeof (int));
	  DPR=vcalloc ( 1, sizeof ( Dp_Result));
	  DPR->traceback=vcalloc (max_len_al, sizeof (int));
	  
/*PREPARE THE EVALUATION*/      
	  if (ns[0]+ns[1]>2)
	    {
	      fprintf ( stderr, "\nERROR: function make_fasta_cdna_pair_wise can only handle two sequences at a time [FATAL:%s]",PROGRAM);
	      crash ("");
	    }
	  mat=CL->M; 					  		

/*INITIALIZATION OF THE DP MATRICES*/

	for (i=0; i<=l0;i++)
	  {						
	    for (j=0; j<=ndiag;j++)
	      {
		for ( state=0; state<M->nstate; state++)
		  {
		    Mat   [state*mI+i*mJ+j]=UNDEFINED;
		    LMat  [state*mI+i*mJ+j]=UNDEFINED;
		    trace [state*mI+i*mJ+j]=M->START;
		  }
	      }
	  }	

	M->diag[0]=0;

	for (i=0; i<=l0; i++)
	  for ( j=0; j<=ndiag; j++)
	    {
	      pos_j=M->diag[j]-l0+i;
	      pos_i=i;
	      if (!(pos_j==0 || pos_i==0))continue;
	      if ( pos_j<0 || pos_i<0)continue;
	      if ( pos_i==0 && pos_j==0)
		  {
		  for ( a=0; a< M->nstate; a++)
		    {
		     Mat  [a*mI+i*mJ+j]=0;
		     LMat [a*mI+i*mJ+j]=0;
		     trace[a*mI+i*mJ+j]=M->START;
		    }
		}
	      else
		{	
		  l=MAX(pos_i,pos_j);
		  for ( state=0; state<M->START; state++)
		    {		     
		      if (pos_j==0 && M->model_properties[state][M->LEN_J])continue;
		      if (pos_i==0 && M->model_properties[state][M->LEN_I])continue;
		     
		     
		     t=M->model[M->START][state];
		     e=M->model_properties[state][M->TERM_EMISSION];
		     Mat   [state*mI+i*mJ+j]=t+e*l;
		     LMat  [state*mI+i*mJ+j]=l;
		     trace [state*mI+i*mJ+j]=M->START;
		    }
		}
	    }

/*DYNAMIC PROGRAMMING: Forward Pass*/

	

	for (i=1; i<=l0;i++)
	  {						
	    for (j=1; j<=ndiag;j++)
	      {
		pos_j=M->diag[j]-l0+i;
		pos_i=i;
		
		if (pos_j<=0 || pos_j>l1 )continue;
		last_i=i;
		last_j=j;
		
		for (cur_state=0; cur_state<M->START; cur_state++)
		  {
		    if (M->model_properties[cur_state][M->DELTA_J])
		      {
			prev_j=j+M->model_properties[cur_state][M->DELTA_J];
			prev_i=i+M->model_properties[cur_state][M->DELTA_I]*FABS((M->diag[j]-M->diag[prev_j]));			
		      }
		    else
		      {
			prev_j=j;
			prev_i=i+M->model_properties[cur_state][M->DELTA_I];
		      }
		    len_i=FABS((i-prev_i));
		    len_j=FABS((M->diag[prev_j]-M->diag[j]));
		    len=MAX(len_i, len_j);
		    a1=A->seq_al[M->model_properties[cur_state][M->F0]  ][pos_i-1];
		    a2=A->seq_al[M->model_properties[cur_state][M->F1]+3][pos_j-1];
		
		    if (M->model_properties[cur_state][M->TYPE]==M->CODING0)
		      {
			if ( a1=='o' || a2=='o')em=-(mat['w'-'A']['w'-'A'])*SCORE_K;
			else if (a1=='x' || a2=='x')em=UNDEFINED;
			else if ( a1==0 || a2==0)exit (0);
			else 
			  {
			    em=(mat[a1-'A'][a2-'A'])*SCORE_K;
			  }
		      }
		    else
		      {
			em=M->model_properties[cur_state][M->EMISSION];
		      }
		    
		    
		   
		    for (pc=best_pc=UNDEFINED, model_index=1; model_index<=M->bounded_model[cur_state][0]; model_index++)
		      {
			prev_state=M->bounded_model[cur_state][model_index];
			
			if(prev_i<0 || prev_j<0 ||prev_i>l0 || prev_j>ndiag || len==UNDEFINED)prev_score=UNDEFINED;
			else prev_score=Mat[prev_state*mI+prev_i*mJ+prev_j];
			t=M->model[prev_state][cur_state];			
			e=em;
		
			if   (prev_score==UNDEFINED || len==UNDEFINED)e=UNDEFINED;			
			else if (len==0|| e==UNDEFINED)e=UNDEFINED;
			else e=e*len;
			
			if (is_defined_int(3,prev_score,e, t))
			  {
			    pc=prev_score+t+e;
			  }
			else  pc=UNDEFINED;
			
			/*Identify the best previous score*/
			if (best_pc==UNDEFINED || (pc>best_pc && pc!=UNDEFINED))
			  {
			    prev[cur_state]=prev_state;
			    best_pc=pc;
			   
			  }
		      }
		    
		    Mat[cur_state*mI+i*mJ+j]=best_pc;
		   


		    if ( Mat[cur_state*mI+i*mJ+j]==UNDEFINED)
		      {
			LMat[cur_state*mI+i*mJ+j]=UNDEFINED;
			trace[cur_state*mI+i*mJ+j]=UNDEFINED;
			continue;
		      }
		    
		    else if ( prev[cur_state]==cur_state)
		      {
			LMat [cur_state*mI+i*mJ+j]=	LMat [cur_state*mI+prev_i*mJ+prev_j]+len;
			trace[cur_state*mI+i*mJ+j]=     trace[cur_state*mI+prev_i*mJ+prev_j];
		      }
		    else
		      {
			LMat[cur_state*mI+i*mJ+j]=len;
			trace[cur_state*mI+i*mJ+j]=prev[cur_state];
		      }
		  }
	      }
	  }
	
	
        i=last_i;
	j=last_j;
	for (pc=best_pc=UNDEFINED, state=0; state<M->START; state++)
	  {
	    t=M->model[state][M->END];
	    e=M->model_properties[state][M->TERM_EMISSION];
	    l=LMat[state*mI+i*mJ+j];
	    
	   
	    if (!is_defined_int(4,t,e,Mat[state*mI+i*mJ+j],l))Mat[state*mI+i*mJ+j]=UNDEFINED;
	    else Mat[state*mI+i*mJ+j]+=t+e*(l);
	    pc=Mat[state*mI+i*mJ+j];
	    
	   
	    if (best_pc==UNDEFINED || (pc>best_pc && pc!=UNDEFINED))
	      {
		k=state;
		best_pc=pc;
	      }
	  }
	 DPR->score=best_pc;
	
/*TRACEBACK*/ 


	e=0;
	len=0;    
	
	
	while (k!=M->START)
	  {
	    next_k=trace[k*mI+i*mJ+j];
	    new_i=i;
	    new_j=j;
	    l=LMat[k*mI+i*mJ+j];
	   	   
	    for (a=0; a< l; a++)
	      {
		DPR->traceback[len++]=k;
	      }
	   new_i+=M->model_properties[k][M->DELTA_I]*l;
	   
	   
	   if ( M->model_properties[k][M->DELTA_J])
	     {
	       while ( next_k!=M->START && FABS((M->diag[j]-M->diag[new_j]))!=l)new_j+=M->model_properties[k][M->DELTA_J];
	     }

	   i=new_i;
	   j=new_j;
	   k=next_k;
	  }
	DPR->len=len;
	DPR->traceback[DPR->len++]=M->START;
	invert_list_int  (DPR->traceback,DPR->len);
	DPR->traceback[DPR->len]=M->END;
	
	vfree (prev);

	return DPR;
	

	}