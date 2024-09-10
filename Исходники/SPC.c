void SPC_HIERARCHICAL(edge_t * V, nid_t n, int d, int k, nid_t minClusSize, int Nmc, int * Nc, nid_t ** Cn, nid_t *** C, nid_t ** P)
{
    // Declare variables
    FS_TREE * FST;
  	Graph * D, * MSG, * Tb;
    edge_t tmin, tmax, aKi, aWs, ival, b_thresh, tval, maxval, cval, Tsp;
    edge_t minTempStep, minTempStep_end, ta, tb, tc, Tspa;
    edge_t * Teval;
    nid_t tid, maxid, mcid, Sma, Smb, Smc, cid, cid2, tcs;
    nid_t * maxCor, * Ct, * MCS, * MCI, * newC;
    List * S;  
    int i, j, l, init_temps, ei, scan_temps, scan_print, ilc, ncf, Njumps;
    int p, jj, maxPosClusts, llci, hier_print, plt, nsplits;
    int SI[1000]; 
    int ** Ch;
    int * ChN, * newCh;


    //0. Find the fair-split tree
    //mexPrintf("Computing fair-split tree...\n"); mexEvalString("drawnow;");
    FST = FAIR_SPLIT(V, n, d); //compute the fair split tree
    //mexPrintf("  Finished.\n"); mexEvalString("drawnow;");


    // 1. Find mutual K Nearest Neighbors
    mexPrintf("Finding mutual K Nearest Neighbors...\n"); mexEvalString("drawnow;");
    D = NEW_ALGRAPH(n,0); //graph of distances between mutual KNN
    FS_AMKNN(FST, D, n, k); //compute the approx MKNN using the fair-split tree
    mexPrintf("  Finished.\n"); mexEvalString("drawnow;");


    // 2. Find Approximate Minimum Spanning Graph
    //mexPrintf("Approximating the minimum spanning graph...\n"); mexEvalString("drawnow;");
    MSG = NEW_ALGRAPH(n,0); //allocate new graph for min span graph
    FS_AEMSG(FST, MSG); //compute approx. min spanning graph using fair-split tree
    //mexPrintf("  Finished.\n"); mexEvalString("drawnow;");
    CLEAR_FS_TREE(FST); //don't need the tree anymore


    // 3. Superimpose KNN and MST
    ALG_ORIP(D, MSG); //OR the edges of each graph, store in D
    ALG_CLEAR(MSG); //free the MST from mem


    // 4. Calculate interaction values between each neighbor
    b_thresh = 0.5; //probability threshold for edge
    aKi = 1.0/(2.0*((float) D->ne)/((float) D->n)); //inverse of avg. number of neighbors
    aWs = ALG_AVG_EDGE_WEIGHT(D); //the average distance between neighbors
    aWs = 2.0*aWs*aWs; //twice the squared average distance between neighbors
    Tb = NEW_ALGRAPH(n, 0); //allocate new graph for break temps
    for (i=0;  i<D->n; i++) { //for each node
        for (j=0; j<LIST_LENGTH(D->nodes[i]); j++) { //for each edge from that node
            tid = LIST_GET_ID(D->nodes[i], j); //id of edge's endpoint
            if (i < tid) { //undir graph, so only worry about lesser->larger id edges
                tval = LIST_GET_VAL(D->nodes[i], j); //distance between i and tid
                ival = aKi*exp(-tval*tval/aWs); //this interaction strength
                ival = -ival/log(1.0-b_thresh); //the temp above which this edge breaks
                ival = 1e3*ival*ival*ival; //cubing it and *1k seems to work well just to get a more linear eval
                if (ival > tmax) tmax = ival; //store max edge val
                if (ival < tmin) tmin = ival; //store min val
                ALG_ADD_EDGE(Tb, i, tid, ival); //add the interaction to the graph
            }
        }
    }


    // Get the max-correlation neighbor of each point
    maxCor = malloc(Tb->n * sizeof(nid_t)); //id of the max-cor point for each point
    for (i=0; i<Tb->n; i++) { //for each node
        maxid = 0;
        maxval = 0;
        for (j=1; j<LIST_LENGTH(Tb->nodes[i]); j++) { //for each edge
            mcid = LIST_GET_ID(Tb->nodes[i], j); //get this child's id
            cval = LIST_GET_VAL(Tb->nodes[i], j); //get child's value
            if (cval > maxval) {
                maxval = cval;
                maxid = mcid;
            }
        }
        maxCor[i] = maxid;
    }
    

    // 5. Guestimate SPM-to-Paramagnetic phase transition temperature
    Tsp = tmax;


    // 6. Evaluate at the theoretical SPM->PM temp
    init_temps = 100;
    ei = 0;  //index of current evaluation
    S = NEW_LIST(10); //dfs stack of nodes to visit during subgraphs search
    Teval = malloc(init_temps*sizeof(edge_t)); //temps which were evaluated
    Ct = malloc(n*init_temps*sizeof(nid_t)); //clusterids at each temp
    MCS = malloc(Nmc*init_temps*sizeof(nid_t)); //max cluster sizes
    MCI = malloc(Nmc*init_temps*sizeof(nid_t)); //ids of the max clusters
    THRESH_SUBGRAPHS_SIZES(Tb, maxCor, Tsp, Nmc, S, Ct, MCS, MCI); //find the cluster ids and sizes of the largest clusters at the theoretical temp
    *Teval = Tsp; //store where we evaluated at
    ei++; //increment evaluation index

    // 6.5 "Evaluate" at T=0
    for (i=0; i<n; i++) { *(Ct+n+i) = 1; } //all points are of the same cluster
    for (i=1; i<Nmc; i++) { *(MCI+Nmc+i) = -1; } //all points are of the same cluster
    for (i=1; i<Nmc; i++) { *(MCS+Nmc+i) = 0; } //all other cluster sizes are 0
    *(MCS+Nmc) = n; //at lowest temp, largest cluster consists of all points
    *(MCI+Nmc) = 1; //and it has id of 1
    *(Teval+1) = 0.0;
    ei++;


    // 7. Find the true SPM->PM phase transition temperature
    //mexPrintf("Finding true SPM->PM temp...\n");
    minTempStep_end = Tsp/100;
    ta=0; tb=Tsp; //bound temps for binary search
    Sma=n; Smb=*MCS; //max cluster size at bound temps
    while ( tb-ta > minTempStep_end ) {
        if ( Smb > minClusSize ) { //SPM->PM temp is above our bracket
            ta = tb; //set A to B
            Sma = Smb; //set A to B
            tb = 2*tb; //extend bracket range
            *(Teval+ei) = tb; //evaluate at new T
            THRESH_SUBGRAPHS_SIZES(Tb, maxCor, tb, Nmc, S, Ct+ei*n, MCS+ei*Nmc, MCI+ei*Nmc);
            Smb = *(MCS+ei*Nmc); //store the max cluster size @ that temp
        } else { //SPM->PM temp is below top bracket
            tc = (ta+tb)/2; //midpoint temperature between brackets
            *(Teval+ei) = tc; //evaluate at midpoint
            THRESH_SUBGRAPHS_SIZES(Tb, maxCor, tc, Nmc, S, Ct+ei*n, MCS+ei*Nmc, MCI+ei*Nmc);
            Smc = *(MCS+ei*Nmc); //store the max cluster size @ that temp
            if ( Smc < minClusSize ) { //SPM->PM is between A and C
                tb = tc; //set B to C
                Smb = Smc;
            } else { //SPM->PM is between C and B
                ta = tc; //set A to C
            }
        }
        ei++; //increment evaluation index
        if (ei >= init_temps) { //double array sizes if we need more space
            doubleArraySizes(&Teval, &Ct, &MCS, &MCI, &init_temps, n, Nmc);
        }
    }
    Tspa = tb; //the actual SPM->PM transtion temperature
    //mexPrintf("  Finished.\n");


    // 8. Do an initial scan across temperatures
    scan_temps = 50;  
    scan_print = scan_temps/10;
    mexPrintf("Performing initial scan over temperatures...\n"); mexEvalString("drawnow;");
    for (i=1; i<scan_temps; i++) {
        tc = i*Tspa/scan_temps; //linspace from 0 to SPM->PM
        *(Teval+ei) = tc; //evaluate at each temp
        THRESH_SUBGRAPHS_SIZES(Tb, maxCor, tc, Nmc, S, Ct+ei*n, MCS+ei*Nmc, MCI+ei*Nmc);
        ei++;
        if (ei >= init_temps) { //double array sizes if we need more space
            doubleArraySizes(&Teval, &Ct, &MCS, &MCI, &init_temps, n, Nmc);
        }
    scan_print = scan_temps/10;
        if (i%scan_print==0) { //print progress
            //mexPrintf("  %.1f percent complete\n", 100 * (float) i / (float) scan_temps);
            //mexEvalString("drawnow;");
        }
    }
    mexPrintf("  Finished.\n"); mexEvalString("drawnow;");


    // 9. Find the jump points for each i-th largest cluster
    minTempStep = Tspa/800;
    Njumps = 0;  //number of jumps so far
    printf("Zooming in on cluster splits...\n"); mexEvalString("drawnow;");
    for (ilc=1; ilc<Nmc; ilc++) {  //for each of the i-th largest clusters
        //printf("  Looking for %d-largest cluster jumps (out of %d)...\n", ilc+1, Nmc);  ncf = 1;
        //mexEvalString("drawnow;");
        sortTemps(Teval, ei, SI); //get the order of Teval in SI
        i = 1;
        while ( Teval[SI[i]] < Tspa ) { //while we haven't reached the SPM->PM temp
            if ( ( *(MCS+Nmc*SI[i]+ilc) > *(MCS+Nmc*SI[i-1]+ilc) ) //if i-th largest cluster increased in size since last timestep
              && ( *(MCS+Nmc*SI[i]+ilc) > minClusSize ) // and it's not too small,
              && ( Teval[SI[i]]-Teval[SI[i-1]] > minTempStep ) ) { // and we haven't already zoomed in here
                // Then do a binary search for jump point between these two points!
                //printf("    Found total of %d, this one at T=%f\n", ncf++, Teval[SI[i]]);
                //mexEvalString("drawnow;");
                ta = Teval[SI[i-1]];  tb = Teval[SI[i]]; //bracket the jump point
                Sma = *(MCS+Nmc*SI[i-1]+ilc);
                Smb = *(MCS+Nmc*SI[i]+ilc);
                while ( tb-ta > minTempStep ) {
                    tc = (ta+tb)/2; //midpoint
                    *(Teval+ei) = tc; //evaluate at midpoint
                    THRESH_SUBGRAPHS_SIZES(Tb, maxCor, tc, Nmc, S, Ct+ei*n, MCS+ei*Nmc, MCI+ei*Nmc);
                    Smc = *(MCS+ei*Nmc+ilc); //store the max cluster size @ that temp
                    ei++;
                    if (ei >= init_temps) { //double array sizes if we need more space
                        doubleArraySizes(&Teval, &Ct, &MCS, &MCI, &init_temps, n, Nmc);
                    }
                    if (Sma < Smc && Smc > minClusSize) { //there is a jump between A and C and C is above size threshold
                        tb = tc; //set B to C
                        Smb = Smc;
                    } else { //jump point is between C and B
                        ta = tc;  //set A to C
                        Sma = Smc;
                    }
                }
                sortTemps(Teval, ei, SI); //get the order of Teval in SI
            }
            i++; //move on to next temp step
        }
    }
    printf("  Finished.\n"); mexEvalString("drawnow;");

    printf("\nRan %d evaluations total\n\n", ei); mexEvalString("drawnow;");


    // 10. Find the clusters which have jumped at each jump point, and hierarchical structure
    //printf("Determining hierarchical structure of clusters...\n");
    maxPosClusts = 200; //not gonna be more than that many clusters, right?
    *Nc = 0;
    *Cn = malloc(maxPosClusts*sizeof(nid_t)); //allocate list of cluster sizes
    *C = malloc(maxPosClusts*sizeof(nid_t *)); //allocate list of pointers to cluster id lists
    *P = malloc(maxPosClusts*sizeof(nid_t)); //allocate list of parent cluster ids
    Ch = malloc(maxPosClusts*sizeof(nid_t *)); //list of pointers to child list for each cluster
    for (p=0; p<maxPosClusts; p++) { //initialize to null
        Ch[p] = NULL;
    }
    ChN = malloc(maxPosClusts*sizeof(nid_t)); //number of children for each cluster
    for (p=0; p<maxPosClusts; p++) { //initialize to zero
        ChN[p] = 0;
    }
    llci = 0; //index of the temp of the last break from the largest clus
    hier_print = ei/5;

    for (i=1; i<ei; i++) { //for each evaluation,

        //if (i%hier_print==0) { //print progress occasionally
        //    printf("  %.1f percent complete\n", 100.0 * ((float) i) / ((float) ei));
        //}

        // If the gap is small enough, there may be a split here
        if ( Teval[SI[i]]-Teval[SI[i-1]] < 2*minTempStep ) { 
            nsplits = 0;
            for (j=0; j<Nmc; j++) { //for each of the i-th largest clusters

                // Find which cluster at the last tempstep was its parent
                plt = -1; //parent id at the last temperature
                for (jj=Nmc-1; jj>=0 && plt<0; jj--) {
                    if (isChild(j, i, jj, i-1, MCI, Nmc, SI, Ct, n)) { 
                        plt = jj;
                    }
                }

                // Was there a jump?
                tcs = *(MCS+Nmc*SI[i]+j); //this cluster's size at current temp
                if ((*(MCS+Nmc*SI[i-1]+plt)-tcs) > minClusSize && tcs>minClusSize) { //if there was a jump and this cluster is large enough to consider

                    // Make a new cluster of clus(j,i)
                    nsplits++; //count the number of clusters which split
                    newC = malloc(tcs*sizeof(nid_t)); //list of cluster IDs for the new cluster
                    (*C)[*Nc] = newC; //make corresponding element of C point to that list
                    (*Cn)[*Nc] = tcs; //store the size of the new cluster
                    cid2 = 0; //reset counter
                    for (cid=0; cid<n; cid++) { //for each point,
                        //if this point is in the new cluster
                        if ( *(Ct+n*SI[i]+cid) == *(MCI+Nmc*SI[i]+j) ) { 
                            newC[cid2++] = cid; //store the ids of each point in the cluster
                        }
                    }
                    (*Nc)++; //increment the number of clusters found
                    
                    // Find its parent in the list of existing clusters
                    p = parentSearch(newC, tcs, *C, *Cn, *P, *Nc-1); 
                    (*P)[*Nc-1] = p; //set element in P to the parent clus id of new clus 
                    
                    // Print info
                    //printf("At T=%f, cluster id=%d of size %d broke off from %d\n", Teval[SI[i]], *Nc-1, tcs, p);

                }
            }

            if (nsplits == 1) { //can't have just one! Need to have two which split off
                //so delete the most recently added cluster
                free(newC);
                (*Nc)--; //decrement the number of clusters found
                (*C)[*Nc] = NULL; //make corresponding element of C point to that list
                (*Cn)[*Nc] = -1; //store the size of the new cluster
            }
        }
    }
    //printf("  Finished.\n"); mexEvalString("drawnow;");


    // Done, clean up
    ALG_CLEAR(Tb);
    CLEAR_LIST(S);
    free(maxCor);
    free(Teval);
    free(Ct); 
    free(MCS);
    free(MCI);
    mexPrintf("Done.\n");

}