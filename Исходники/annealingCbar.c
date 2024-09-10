//**********************************************************************
//**********************************************************************
int rewiring_Cbar_annealing(GRAPH G,double B,double increment,double accmin,int rewires,gsl_rng* randgsl){
	
	
	double Caim = G.Ccoef;
    
 /***********************************************************************
	 we create a random network with the same degree sequence 
 ************************************************************************/
	
	rewiring_Pk(G,rewires,randgsl);
    
    double C  = clustering_coeff(G);
    
    double Cnew = C;
    
	printf("Caim %f Cinitial %f\n",Caim,C);
 /***********************************************************************
	       we do the rewiring preserving the C(k)
 ************************************************************************/	
	
	int s1,s2,r1,r2,pos_r,pos_s;						    /// rewiring variables that will store the proposed rewiring
	
	double p,AH;
	int accepted=0,rewirestemp=0,pirem=0;					/// during the proces we count how many proposals rewirings are with AH>0, AH<o and AH=0
	double averAH = 0,averAHneg = 0,averAHpos = 0,oldacc=0;
	int numAH0 = 0,numAHneg = 0,numAHpos = 0;
		
	double H = fabs(C - Caim);                              /// initial energy
	
		
	/******** we start the rewiring *************/
	
	printf("Annealed rewiring fixing the clustering coefficient...\n");fflush(stdout);
	
	time_t start,end;										/// we will measure the time
	double dif;
	time (&start);
	
	int i;	
	for(i=1; oldacc>accmin || i<rewires*G.E+2 ;++i){
		
					
		while(!choose_2_edges_random(G,&pos_r,&pos_s,randgsl)){} /// we try to find two edges avoiding selfedges and multipledges
		
		r1 = G.edge[pos_r].s;								/// the nodes are
		r2 = G.edge[pos_r].d; 
		
		s1 = G.edge[pos_s].s;
		s2 = G.edge[pos_s].d;
		
		AH = calc_AH_Cbar(G,s1,s2,r1,r2,C,&Cnew,Caim);	    /// we calculate the increment of energy that would cause the rewiring
		
		averAH = averAH + fabs(AH);							///we also counbt the average AH of the proposals
		
		if(AH < 0.) {										/// we count how many proposals have AH > 0
			
			numAHneg++;
			averAHneg = averAHneg + AH;
		}
		else if (AH > 0.) {									/// we count how many proposals have AH < 0
			
			numAHpos++;
			averAHpos = averAHpos + AH;
			
		}
		else numAH0++;										/// we count how many proposals have AH = 0
		
		p =  gsl_rng_uniform(randgsl);						/// we throw a random number (0,1)
		
		/********** IF we acccept **************/
		
		if( p < exp(-B*AH) ){						
			
			
			swap_edges(G,s1,s2,r1,r2);					    /// we make the proposed rewired
			
			G.edge[pos_r].d = s2;							/// we modify the edge vector
			G.edge[pos_s].d = r2;
			
			C = Cnew;
			
			if(fabs(AH)>0.)	accepted++;						/// we coubt how many changes we accept
			
			H = H + AH;
		}
		
		/********** IF we reject **************/
		
		else {								
			
			Cnew = C;
		}
		
		rewirestemp++;
		
		/********** we reduce the temperature and we check the acceptance **************/
		
		if(rewirestemp > rewires*G.E ) {	///we try to find the appropiate temperature in order to have the desire acceptation
			
			printf("acceptance rate = %f "                ,(double)accepted/(numAHneg+numAHpos));				/// the acceptance
			//printf("AH = %f "                 ,averAH/(numAHneg+numAHpos));							/// the average energy of the proposed swaps
			//printf("numAHneg = %f AHneg = %e ",(double)numAHneg/rewirestemp,averAHneg/numAHneg);	/// the proportion of negative energy swaps and the average
			//printf("numAHpos = %f AHpos = %e ",(double)numAHpos/rewirestemp,averAHpos/numAHpos);	/// the proportion of positive energy swaps and the average
			//printf("numAH0=%f "               ,(double)numAH0/rewirestemp);							/// the proportion of proposals that do not change the energy
			printf("Beta=%e Energy=%e\n"              ,B,H);												/// the temperature and the energy
			fflush(stdout);
			
			if( ((double)accepted/(numAHneg+numAHpos)) > oldacc && i > rewires*G.E + 2 ) pirem++;	/// in case we havethe acceptance has increased 10 times the rewiring proces
			if(pirem>30) break;
			
			oldacc		= ((double)accepted/(numAHneg+numAHpos));								/// we save the old acceptance in order to compare with the next one
			accepted    = 0;												/// we put to zero all the acceptance counters
			rewirestemp = 0;
			averAH      = 0; numAHneg = 0;averAHneg = 0;
			numAH0      = 0; numAHpos = 0;averAHpos = 0;
			
			B = B*increment;												/// we reduce the temperature
			
		}
		
					
	}
	
      

	time (&end);											///we count the rewiring time and take conclusions
	dif = difftime (end,start);
	printf ("You rewired the entire network %.2f times with %.2lf seconds.\n",(double)i/G.E, dif );
	printf("Cfinal %f\n",C);
    
 /***********************************************************************
		 we free the memory
 ************************************************************************/
	

	
	return 0;
	
}