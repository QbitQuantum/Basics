/* Initialization of neurons parameters */
int initialization(neuron **nrn, int numNeurons, int simTime)
{
    int i, j, idj, size=0;
    char *fname;
    double tmp;
    FILE *fp, *fq;

    srand (time(NULL));
        
    for(i = 0; i < numNeurons; ++i){
        (*nrn)[i].numPreSyn = 0;
        (*nrn)[i].E = 0.0;
        for(j = 0; j < simTime; ++j){
            (*nrn)[i].V[j] = randm(0.01, 0.1);
            (*nrn)[i].Z[j] = randm(0.01, 0.05);
            (*nrn)[i].S[j] = randm(0.01, 0.05);
            (*nrn)[i].N[j] = randm(0.01, 0.05);
        }
    }

    if(!(fp = fopen("stimuli.dat", "r"))){
        fname = "stimuli.dat";
        goto fail;
    }

    for(i = 0; i < numNeurons; ++i){
        for(j = 0; j < simTime; ++j){
            fscanf(fp, "%lf", &(*nrn)[i].Iext[j]);
        }
    }
    
    fclose(fp);

    if(!(fq = fopen("synapses.dat", "r"))){
        fname = "synapses.dat";
        goto fail;
    }

    for(i = 0; i < numNeurons; ++i){
        idj = 0;
        for(j = 0; j < numNeurons; ++j){
            fscanf(fp, "%lf", &tmp);
            if (tmp != 0){
                if (j == 0){
                    (*nrn)[i].W[0] = tmp;
                    (*nrn)[i].pre_id[0] = j;
                }else{
                    size++;
                    (*nrn)[i].W = (double *)realloc((*nrn)[i].W, size*sizeof(double));
                    (*nrn)[i].W[idj] = tmp;

                    (*nrn)[i].pre_id = (int *)realloc((*nrn)[i].pre_id,
                                size*sizeof(int));
                    (*nrn)[i].pre_id[idj] = j;
                    idj++;
                }
                (*nrn)[i].numPreSyn++;
            }
        }
    }

    fclose(fp);

    return 0;

fail:
    printf("File %s cannot be opened!\n", fname);
    exit(-1);
}