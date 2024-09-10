// Read input file (HMM, HHM, or alignment format), and add pseudocounts etc.
void ReadInput(char* infile, HMM& q, Alignment* qali=NULL)
{
    char path[NAMELEN];

    // Open query file and determine file type
    char line[LINELEN]=""; // input line
    FILE* inf=NULL;
    if (strcmp(infile,"stdin"))
    {
        inf = fopen(infile, "r");
        if (!inf) OpenFileError(infile);
        Pathname(path,infile);
    }
    else
    {
        inf = stdin;
        if (v>=2) printf("Reading HMM / multiple alignment from standard input ...\n(To get a help list instead, quit and type %s -h.)\n",program_name);
        *path='\0';
    }

    fgetline(line,LINELEN-1,inf);

    // Is infile a HMMER3 file?
    if (!strncmp(line,"HMMER3",6))
    {
        if (v>=2) cout<<"Query file is in HMMER3 format\n";
	cerr<<"WARNING: Use of HMMER3 format as input will result in severe loss of sensitivity!\n";

        // Read 'query HMMER file
        rewind(inf);
        q.ReadHMMer3(inf,path);
    }

    // ... or is infile an old HMMER file?
    else if (!strncmp(line,"HMMER",5))
    {
        if (v>=2) cout<<"Query file is in HMMER format\n";
	cerr<<"WARNING: Use of HMMER format as input will result in severe loss of sensitivity!\n";

        // Read 'query HMMER file
        rewind(inf);
        q.ReadHMMer(inf,path);
    }

    // ... or is it an hhm file?
    else if (!strncmp(line,"NAME",4) || !strncmp(line,"HH",2))
    {
        if (v>=2) cout<<"Query file is in HHM format\n";

        // Rewind to beginning of line and read query hhm file
        rewind(inf);
        q.Read(inf,path);
        if (v>=2 && q.Neff_HMM>11.0)
            fprintf(stderr,"WARNING: HMM %s looks too diverse (Neff=%.1f>11). Better check the underlying alignment... \n",q.name,q.Neff_HMM);

    }
    // ... or is it an alignment file
    else
    {
        Alignment* pali;
        if (qali==NULL) pali=new(Alignment); else pali=qali;
        if (par.calibrate) {
            printf("\nError in %s: only HHM files can be calibrated.\n",program_name);
            printf("Build an HHM file from your alignment with 'hhmake -i %s' and rerun hhsearch with the hhm file\n\n",infile);
            exit(1);
        }

        if (v>=2 && strcmp(infile,"stdin")) cout<<infile<<" is in A2M, A3M or FASTA format\n";

        // Read alignment from infile into matrix X[k][l] as ASCII (and supply first line as extra argument)
        pali->Read(inf,infile,line);

        // Convert ASCII to int (0-20),throw out all insert states, record their number in I[k][i]
        // and store marked sequences in name[k] and seq[k]
        pali->Compress(infile);

        // Sort out the nseqdis most dissimilar sequences for display in the output alignments
        pali->FilterForDisplay(par.max_seqid,par.coverage,par.qid,par.qsc,par.nseqdis);

        // Remove sequences with seq. identity larger than seqid percent (remove the shorter of two)
        pali->N_filtered = pali->Filter(par.max_seqid,par.coverage,par.qid,par.qsc,par.Ndiff);

	if (par.Neff>=0.999) 
	  pali->FilterNeff();

        // Calculate pos-specific weights, AA frequencies and transitions -> f[i][a], tr[i][a]
        pali->FrequenciesAndTransitions(q);
        if (v>=2 && q.Neff_HMM>11.0)
            fprintf(stderr,"WARNING: alignment %s looks too diverse (Neff=%.1f>11). Better check it with an alignment viewer... \n",q.name,q.Neff_HMM);

        if (qali==NULL) delete(pali);
    }
    fclose(inf);

    return;
}