int convert_volslice(slice *slicei, int *thread_index) {
    char slicefile_svz[1024];
    char *slice_file;
    char filetype[1024];
    char *shortlabel;
    int ijkbar[6];
    uLong framesize;
    float *sliceframe_data=NULL;
    int sizebefore, sizeafter;
    int returncode;
    LINT data_loc;
    int percent_done;
    int percent_next=10;
#ifndef pp_THREAD
    int count=0;
#endif
    FILE *SLICEFILE;
    FILE *slicestream;

#ifdef pp_THREAD
    if(GLOBcleanfiles==0) {
        int fileindex;

        fileindex = slicei + 1 - sliceinfo;
        sprintf(threadinfo[*thread_index].label,"vsf %i",fileindex);
    }
#endif

    slice_file=slicei->file;

    // check if slice file is accessible

    strcpy(filetype,"");
    shortlabel=slicei->label.shortlabel;
    if(strlen(shortlabel)>0)strcat(filetype,shortlabel);
    trim(filetype);

    if(getfileinfo(slice_file,NULL,NULL)!=0) {
        fprintf(stderr,"*** Warning: The file %s does not exist\n",slice_file);
        return 0;
    }

    SLICEFILE=fopen(slice_file,"rb");
    if(SLICEFILE==NULL) {
        fprintf(stderr,"*** Warning: The file %s could not be opened\n",slice_file);
        return 0;
    }

    // set up slice compressed file

    if(GLOBdestdir!=NULL) {
        strcpy(slicefile_svz,GLOBdestdir);
        strcat(slicefile_svz,slicei->filebase);
    }
    else {
        strcpy(slicefile_svz,slicei->file);
    }

    if(strlen(slicefile_svz)>4)strcat(slicefile_svz,".svv");

    if(GLOBcleanfiles==1) {
        slicestream=fopen(slicefile_svz,"rb");
        if(slicestream!=NULL) {
            fclose(slicestream);
            PRINTF("  Removing %s\n",slicefile_svz);
            UNLINK(slicefile_svz);
            LOCK_COMPRESS;
            GLOBfilesremoved++;
            UNLOCK_COMPRESS;
        }
        return 0;
    }

    if(GLOBoverwrite_slice==0) {
        slicestream=fopen(slicefile_svz,"rb");
        if(slicestream!=NULL) {
            fclose(slicestream);
            fprintf(stderr,"*** Warning: The file %s exists.\n",slicefile_svz);
            fprintf(stderr,"     Use the -f option to overwrite smokezip compressed files\n");
            return 0;
        }
    }

    slicestream=fopen(slicefile_svz,"wb");
    if(slicestream==NULL) {
        fprintf(stderr,"*** Warning: The file %s could not be opened for writing\n",slicefile_svz);
        return 0;
    }

    // read and write slice header

#ifndef pp_THREAD
    if(GLOBcleanfiles==0) {
        PRINTF("Compressing %s (%s)\n",slice_file,filetype);
    }
#endif


    {
        int skip;

        skip = 3*(4+30+4);  // skip over 3 records each containing a 30 byte FORTRAN character string
        returncode=FSEEK(SLICEFILE,skip,SEEK_CUR);
        sizebefore=skip;
    }

    FORTSLICEREAD(ijkbar,6);
    sizebefore+=4+6*4+4;
    sizeafter=0;

    {
        int one=1, version_local=0, completion=0;

        fwrite(&one,4,1,slicestream);
        fwrite(&version_local,4,1,slicestream);
        fwrite(&completion,4,1,slicestream);
    }


    {
        int ni, nj, nk;

        ni = ijkbar[1]+1-ijkbar[0];
        nj = ijkbar[3]+1-ijkbar[2];
        nk = ijkbar[5]+1-ijkbar[4];
        framesize = ni*nj*nk;
        NewMemory((void **)&sliceframe_data,framesize*sizeof(float));

        for(;;) {
            float vmin, vmax;
            float *valmin, *valmax;
            unsigned char *compressed_data_out;
            uLongf ncompressed_data_out;
            float time_local;

            FORTSLICEREAD(&time_local,1);
            if(returncode==0)break;
            CheckMemory;
            sizebefore+=12;

            FORTSLICEREAD(sliceframe_data,framesize);    //---------------
            if(returncode==0)break;
            CheckMemory;
            sizebefore+=(4+framesize*sizeof(float)+4);

            valmin=NULL;
            valmax=NULL;
            if(slicei->voltype==1) {
                vmin=0.0;
                valmin=&vmin;
            }
            else if(slicei->voltype==2) {
                vmin=20.0;
                valmin=&vmin;
                vmax=1400.0;
                valmax=&vmax;
            }
            else {
                ASSERT(0);
            }
            CheckMemory;
            compress_volsliceframe(sliceframe_data, framesize, time_local, valmin, valmax,
                                   &compressed_data_out, &ncompressed_data_out);
            CheckMemory;
            sizeafter+=ncompressed_data_out;
            if(ncompressed_data_out>0) {
                fwrite(compressed_data_out,1,ncompressed_data_out,slicestream);
            }
            CheckMemory;
            FREEMEMORY(compressed_data_out);

#ifndef pp_THREAD
            count++;
#endif

            data_loc=FTELL(SLICEFILE);
            percent_done=100.0*(float)data_loc/(float)slicei->filesize;
#ifdef pp_THREAD
            threadinfo[*thread_index].stat=percent_done;
            if(percent_done>percent_next) {
                LOCK_PRINT;
                print_thread_stats();
                UNLOCK_PRINT;
                percent_next+=10;
            }
#else
            if(percent_done>percent_next) {
                PRINTF(" %i%s",percent_next,GLOBpp);
                FFLUSH();
                percent_next+=10;
            }
#endif

        }
        if(returncode!=0) {
            fprintf(stderr,"*** Error: compress returncode=%i\n",returncode);
        }
        FREEMEMORY(sliceframe_data);
    }

#ifndef pp_THREAD
    PRINTF(" 100%s completed\n",GLOBpp);
#endif

    {
        int completion=1;

        FSEEK(slicestream,4,SEEK_SET);
        fwrite(&completion,4,1,slicestream);
    }
    fclose(SLICEFILE);
    fclose(slicestream);

    {
        char before_label[256],after_label[256];

        getfilesizelabel(sizebefore,before_label);
        getfilesizelabel(sizeafter,after_label);
#ifdef pp_THREAD
        slicei->vol_compressed=1;
        sprintf(slicei->volsummary,"compressed from %s to %s (%4.1f%s reduction)",before_label,after_label,(float)sizebefore/(float)sizeafter,GLOBx);
        threadinfo[*thread_index].stat=-1;
#else
        PRINTF("  records=%i, ",count);
        PRINTF("Sizes: original=%s, ",before_label);
        PRINTF("compressed=%s (%4.1f%s reduction)\n\n",after_label,(float)sizebefore/(float)sizeafter,GLOBx);
#endif
    }

    return 1;

}