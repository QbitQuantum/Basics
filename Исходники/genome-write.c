void
Genome_write (char *genomesubdir, char *fileroot, FILE *input, 
	      IIT_T contig_iit, IIT_T altstrain_iit, bool uncompressedp, bool rawp,
	      bool writefilep, unsigned int genomelength, int index1part) {
  unsigned int nuint4;
  FILE *refgenome_fp;
  char *filename;
  UINT4 *genomecomp;

  fprintf(stderr,"Genome length is %u nt\n",genomelength);
  if (uncompressedp == true) {
    filename = (char *) CALLOC(strlen(genomesubdir)+strlen("/")+
			       strlen(fileroot)+strlen(".genome")+1,sizeof(char));
    sprintf(filename,"%s/%s.genome",genomesubdir,fileroot);
    if ((refgenome_fp = FOPEN_WRITE_BINARY(filename)) == NULL) {
      fprintf(stderr,"Can't write to file %s\n",filename);
      exit(9);
    }
    if (rawp == true) {
      genome_writeraw_file(refgenome_fp,input,contig_iit,altstrain_iit,fileroot,index1part);
    } else {
      genome_write_file(refgenome_fp,input,contig_iit,altstrain_iit,fileroot,/*uncompressedp*/true,index1part);
    }
    fclose(refgenome_fp);
    FREE(filename);

  } else if (writefilep == true) {
    filename = (char *) CALLOC(strlen(genomesubdir)+strlen("/")+
			       strlen(fileroot)+strlen(".genomecomp")+1,sizeof(char));
    sprintf(filename,"%s/%s.genomecomp",genomesubdir,fileroot);
    fprintf(stderr,"User requested build of genome in file\n");

    if ((refgenome_fp = FOPEN_RW_BINARY(filename)) == NULL) {
      fprintf(stderr,"Can't open file %s for read/write\n",filename);
      exit(9);
    }
    genome_write_file(refgenome_fp,input,contig_iit,altstrain_iit,fileroot,/*uncompressedp*/false,index1part);
    fclose(refgenome_fp);
    FREE(filename);

  } else {
    filename = (char *) CALLOC(strlen(genomesubdir)+strlen("/")+
			       strlen(fileroot)+strlen(".genomecomp")+1,sizeof(char));
    sprintf(filename,"%s/%s.genomecomp",genomesubdir,fileroot);

    nuint4 = ((genomelength + 31)/32U)*3;
    fprintf(stderr,"Trying to allocate %d*%u bytes of memory...",nuint4,(unsigned int) sizeof(UINT4));
    genomecomp = (UINT4 *) CALLOC_NO_EXCEPTION(nuint4,sizeof(UINT4));
    if (genomecomp == NULL) {
      fprintf(stderr,"failed.  Building genome in file.\n");
      if ((refgenome_fp = FOPEN_RW_BINARY(filename)) == NULL) {
	fprintf(stderr,"Can't open file %s for read/write\n",filename);
	exit(9);
      }
      genome_write_file(refgenome_fp,input,contig_iit,altstrain_iit,fileroot,/*uncompressedp*/false,index1part);
      fclose(refgenome_fp);

    } else {
      fprintf(stderr,"succeeded.  Building genome in memory.\n");
      /* Creates X's at end */
      genomecomp[nuint4-3] = 0xFFFFFFFF;
      genomecomp[nuint4-2] = 0xFFFFFFFF;
      genomecomp[nuint4-1] = 0xFFFFFFFF;

      if ((refgenome_fp = FOPEN_WRITE_BINARY(filename)) == NULL) {
	fprintf(stderr,"Can't open file %s for write\n",filename);
	exit(9);
      }
      genome_write_memory(refgenome_fp,input,contig_iit,altstrain_iit,genomecomp,nuint4,fileroot);
      fclose(refgenome_fp);
      FREE(genomecomp);
    }

    FREE(filename);
  }

  return;
}