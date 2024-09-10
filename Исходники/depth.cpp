/* ********************************
    
    Multiplicative model for the placement of
    a file at a given depth taking into
    account the mean bytes at the depth
    and the count of files at that depth

   ********************************/
int fn_depthsize_prob (long double filesize) {

    double meansizediff[DEPTH_ENTRIES];
    double final_prob[DEPTH_ENTRIES];
    double totalsize_prob=0, totalprob=0;
    double sum1=0, sum2=0, sum3=0;
    int i =0;
    float token_until_now=0;
    int token;
    int factor = 100000;
    double depthsize_prob[DEPTH_ENTRIES];
    
    srand(deseeder());

    if(filesize ==0) 
        return rand()%max_dir_depth+1;

    for(i=0; i< DEPTH_ENTRIES; i++) {
        meansizediff[i]=(double) 1/fabsl(log2l(filesize)-(long double)depth_meansize[i]);
        
        print_debug(0,"%Lf %Lf %f\n", log2l(filesize), (long double)depth_meansize[i], meansizediff[i]);
        totalsize_prob+=meansizediff[i];
    }
    
    for(i=0; i< DEPTH_ENTRIES; i++) {
        final_prob[i]=(depthcount_prob[i]/Total_depthcount_prob)*\
            (meansizediff[i]/totalsize_prob);
    }
    
    for(i=0; i< DEPTH_ENTRIES; i++) {
        totalprob+=final_prob[i];
    }
    
    for(i=0; i< DEPTH_ENTRIES; i++) {
        print_debug(0, "Probsize[%d] %f; Probcount %f; Finalprob %f\n", i+1, \
            meansizediff[i]/totalsize_prob*100, depthcount_prob[i]/Total_depthcount_prob*100,\
                final_prob[i]/totalprob*100);
        sum1+= meansizediff[i]/totalsize_prob;
        sum2+= depthcount_prob[i]/Total_depthcount_prob;
        sum3+= final_prob[i]/totalprob;
    }
    print_debug(0,"sums %f, sumc %f sumt %f\n", sum1, sum2, sum3);
    
    i=0;
    do {
        token_until_now=0;
        token = rand() % factor;
        i=0;
        token_until_now=final_prob[i]/totalprob*factor;
        while (token_until_now < token) {
            print_debug(0,"%f %d\n", token_until_now , token);
            i++;
            token_until_now+=final_prob[i]/totalprob*factor;
        }
        if(i== DEPTH_ENTRIES-1) { // last bin is actually 20 to infinite ..not just 20
            i+= rand()%10;        // e.g., any depth between 20 and 30, if DEPTH_ENTRIES=20
        }
        print_debug(0,"Chosen %d, max_dir %d\n", i, max_dir_depth);
    }
    while(i > max_dir_depth);
    
    return i+1;
}