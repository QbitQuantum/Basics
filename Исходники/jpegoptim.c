int main(int argc, char **argv) 
{
  struct jpeg_decompress_struct dinfo;
  struct jpeg_compress_struct cinfo;
  struct my_error_mgr jcerr,jderr;
  JSAMPARRAY buf = NULL;
  jvirt_barray_ptr *coef_arrays = NULL;
  char marker_str[256];
  char tmpfilename[MAXPATHLEN],tmpdir[MAXPATHLEN];
  char newname[MAXPATHLEN], dest_path[MAXPATHLEN];
  volatile int i;
  int c,j, tmpfd, searchcount, searchdone;
  int opt_index = 0;
  long insize = 0, outsize = 0, lastsize = 0;
  int oldquality;
  double ratio;
  struct stat file_stat;
  jpeg_saved_marker_ptr cmarker; 
  unsigned char *outbuffer = NULL;
  size_t outbuffersize;
  char *outfname = NULL;
  FILE *infile = NULL, *outfile = NULL;
  int marker_in_count, marker_in_size;
  int compress_err_count = 0;
  int decompress_err_count = 0;
  long average_count = 0;
  double average_rate = 0.0, total_save = 0.0;


  if (rcsid)
  ; /* so compiler won't complain about "unused" rcsid string */

  umask(077);
  signal(SIGINT,own_signal_handler);
  signal(SIGTERM,own_signal_handler);

  /* initialize decompression object */
  dinfo.err = jpeg_std_error(&jderr.pub);
  jpeg_create_decompress(&dinfo);
  jderr.pub.error_exit=my_error_exit;
  jderr.pub.output_message=my_output_message;
  jderr.jump_set = 0;

  /* initialize compression object */
  cinfo.err = jpeg_std_error(&jcerr.pub);
  jpeg_create_compress(&cinfo);
  jcerr.pub.error_exit=my_error_exit;
  jcerr.pub.output_message=my_output_message;
  jcerr.jump_set = 0;


  if (argc<2) {
    if (!quiet_mode) fprintf(stderr,PROGRAMNAME ": file arguments missing\n"
			     "Try '" PROGRAMNAME " --help' for more information.\n");
    exit(1);
  }
 
  /* parse command line parameters */
  while(1) {
    opt_index=0;
    if ((c=getopt_long(argc,argv,"d:hm:nstqvfVpPoT:S:b",long_options,&opt_index))
	      == -1) 
      break;

    switch (c) {
    case 'm':
      {
        int tmpvar;

        if (sscanf(optarg,"%d",&tmpvar) == 1) {
	  quality=tmpvar;
	  if (quality < 0) quality=0;
	  if (quality > 100) quality=100;
	}
	else 
	  fatal("invalid argument for -m, --max");
      }
      break;
    case 'd':
      if (realpath(optarg,dest_path)==NULL || !is_directory(dest_path)) {
	fatal("invalid argument for option -d, --dest");
      }
      strncat(dest_path,DIR_SEPARATOR_S,sizeof(dest_path)-strlen(dest_path)-1);

      if (verbose_mode) 
	fprintf(stderr,"Destination directory: %s\n",dest_path);
      dest=1;
      break;
    case 'v':
      verbose_mode++;
      break;
    case 'h':
      print_usage();
      exit(0);
      break;
    case 'q':
      quiet_mode=1;
      break;
    case 't':
      totals_mode=1;
      break;
    case 'n':
      noaction=1;
      break;
    case 'f':
      force=1;
      break;
    case 'b':
      csv=1;
      quiet_mode=1;
      break;
    case '?':
      break;
    case 'V':
      print_version();
      exit(0);
      break;
    case 'o':
      overwrite_mode=1;
      break;
    case 'p':
      preserve_mode=1;
      break;
    case 'P':
      preserve_perms=1;
      break;
    case 's':
      save_exif=0;
      save_iptc=0;
      save_com=0;
      save_icc=0;
      save_xmp=0;
      break;
    case 'T':
      {
	int tmpvar;
	if (sscanf(optarg,"%d",&tmpvar) == 1) {
	  threshold=tmpvar;
	  if (threshold < 0) threshold=0;
	  if (threshold > 100) threshold=100;
	}
	else fatal("invalid argument for -T, --threshold");
      }
      break;
    case 'S':
      {
	unsigned int tmpvar;
	if (sscanf(optarg,"%u",&tmpvar) == 1) {
	  if (tmpvar > 0 && tmpvar < 100 && optarg[strlen(optarg)-1] == '%' ) {
	    target_size=-tmpvar;
	  } else {
	    target_size=tmpvar;
	  }
	  quality=100;
	}
	else fatal("invalid argument for -S, --size");
      }
      break;

    }
  }


  /* check for '-' option indicating input is from stdin... */
  i=1;
  while (argv[i]) {
    if (argv[i][0]=='-' && argv[i][1]==0) stdin_mode=1;
    i++;
  }

  if (stdin_mode) { stdout_mode=1; force=1; }
  if (stdout_mode) { logs_to_stdout=0; }

  if (all_normal && all_progressive)
    fatal("cannot specify both --all-normal and --all-progressive"); 

  if (verbose_mode) {
    if (quality>=0 && target_size==0) 
      fprintf(stderr,"Image quality limit set to: %d\n",quality);
    if (threshold>=0) 
      fprintf(stderr,"Compression threshold (%%) set to: %d\n",threshold);
    if (all_normal) 
      fprintf(stderr,"All output files will be non-progressive\n");
    if (all_progressive) 
      fprintf(stderr,"All output files will be progressive\n");
    if (target_size > 0) 
      fprintf(stderr,"Target size for output files set to: %u Kbytes.\n",
	      target_size);
    if (target_size < 0) 
      fprintf(stderr,"Target size for output files set to: %u%%\n",
	      -target_size);
  }


  /* loop to process the input files */
  i=1;  
  do {
    if (stdin_mode) {
      infile=stdin;
    } else {
      if (!argv[i][0]) continue;
      if (argv[i][0]=='-') continue;
      if (strlen(argv[i]) >= MAXPATHLEN) {
	warn("skipping too long filename: %s",argv[i]);
	continue;
      }

      if (!noaction) {
	/* generate tmp dir & new filename */
	if (dest) {
	  STRNCPY(tmpdir,dest_path,sizeof(tmpdir));
	  STRNCPY(newname,dest_path,sizeof(newname));
	  if (!splitname(argv[i],tmpfilename,sizeof(tmpfilename)))
	    fatal("splitname() failed for: %s",argv[i]);
	  strncat(newname,tmpfilename,sizeof(newname)-strlen(newname)-1);
	} else {
	  if (!splitdir(argv[i],tmpdir,sizeof(tmpdir))) 
	    fatal("splitdir() failed for: %s",argv[i]);
	  STRNCPY(newname,argv[i],sizeof(newname));
	}
      }
      
    retry_point:
      
      if (!is_file(argv[i],&file_stat)) {
	if (is_directory(argv[i])) 
	  warn("skipping directory: %s",argv[i]);
	else
	  warn("skipping special file: %s",argv[i]); 
	continue;
      }
      if ((infile=fopen(argv[i],"rb"))==NULL) {
	warn("cannot open file: %s", argv[i]);
	continue;
      }
    }

   if (setjmp(jderr.setjmp_buffer)) {
     /* error handler for decompress */
     jpeg_abort_decompress(&dinfo);
     fclose(infile);
     if (buf) FREE_LINE_BUF(buf,dinfo.output_height);
     if (!quiet_mode || csv) 
       fprintf(LOG_FH,csv ? ",,,,,error\n" : " [ERROR]\n");
     decompress_err_count++;
     jderr.jump_set=0;
     continue;
   } else {
     jderr.jump_set=1;
   }

   if (!retry && (!quiet_mode || csv)) {
     fprintf(LOG_FH,csv ? "%s," : "%s ",(stdin_mode?"stdin":argv[i])); fflush(LOG_FH); 
   }

   /* prepare to decompress */
   global_error_counter=0;
   jpeg_save_markers(&dinfo, JPEG_COM, 0xffff);
   for (j=0;j<=15;j++) 
     jpeg_save_markers(&dinfo, JPEG_APP0+j, 0xffff);
   jpeg_stdio_src(&dinfo, infile);
   jpeg_read_header(&dinfo, TRUE); 

   /* check for Exif/IPTC/ICC/XMP markers */
   marker_str[0]=0;
   marker_in_count=0;
   marker_in_size=0;
   cmarker=dinfo.marker_list;

   while (cmarker) {
     marker_in_count++;
     marker_in_size+=cmarker->data_length;

     if (cmarker->marker == EXIF_JPEG_MARKER &&
	 !memcmp(cmarker->data,EXIF_IDENT_STRING,EXIF_IDENT_STRING_SIZE))
       strncat(marker_str,"Exif ",sizeof(marker_str)-strlen(marker_str)-1);

     if (cmarker->marker == IPTC_JPEG_MARKER)
       strncat(marker_str,"IPTC ",sizeof(marker_str)-strlen(marker_str)-1);

     if (cmarker->marker == ICC_JPEG_MARKER &&
	 !memcmp(cmarker->data,ICC_IDENT_STRING,ICC_IDENT_STRING_SIZE))
       strncat(marker_str,"ICC ",sizeof(marker_str)-strlen(marker_str)-1);

     if (cmarker->marker == XMP_JPEG_MARKER &&
	 !memcmp(cmarker->data,XMP_IDENT_STRING,XMP_IDENT_STRING_SIZE)) 
       strncat(marker_str,"XMP ",sizeof(marker_str)-strlen(marker_str)-1);

     cmarker=cmarker->next;
   }


   if (verbose_mode > 1) 
     fprintf(LOG_FH,"%d markers found in input file (total size %d bytes)\n",
	     marker_in_count,marker_in_size);
   if (!retry && (!quiet_mode || csv)) {
     fprintf(LOG_FH,csv ? "%dx%d,%dbit,%c," : "%dx%d %dbit %c ",(int)dinfo.image_width,
	     (int)dinfo.image_height,(int)dinfo.num_components*8,
	     (dinfo.progressive_mode?'P':'N'));

     if (!csv) {
       fprintf(LOG_FH,"%s",marker_str);
       if (dinfo.saw_Adobe_marker) fprintf(LOG_FH,"Adobe ");
       if (dinfo.saw_JFIF_marker) fprintf(LOG_FH,"JFIF ");
     }
     fflush(LOG_FH);
   }

   if ((insize=file_size(infile)) < 0)
     fatal("failed to stat() input file");

  /* decompress the file */
   if (quality>=0 && !retry) {
     jpeg_start_decompress(&dinfo);

     /* allocate line buffer to store the decompressed image */
     buf = malloc(sizeof(JSAMPROW)*dinfo.output_height);
     if (!buf) fatal("not enough memory");
     for (j=0;j<dinfo.output_height;j++) {
       buf[j]=malloc(sizeof(JSAMPLE)*dinfo.output_width*
		     dinfo.out_color_components);
       if (!buf[j]) fatal("not enough memory");
     }

     while (dinfo.output_scanline < dinfo.output_height) {
       jpeg_read_scanlines(&dinfo,&buf[dinfo.output_scanline],
			   dinfo.output_height-dinfo.output_scanline);
     }
   } else {
     coef_arrays = jpeg_read_coefficients(&dinfo);
   }

   if (!retry && !quiet_mode) {
     if (global_error_counter==0) fprintf(LOG_FH," [OK] ");
     else fprintf(LOG_FH," [WARNING] ");
     fflush(LOG_FH);
   }

   fclose(infile);
   infile=NULL;
     

   if (dest && !noaction) {
     if (file_exists(newname) && !overwrite_mode) {
       warn("target file already exists: %s\n",newname);
       jpeg_abort_decompress(&dinfo);
       if (buf) FREE_LINE_BUF(buf,dinfo.output_height);
       continue;
     }
   }


   if (setjmp(jcerr.setjmp_buffer)) {
     /* error handler for compress failures */
     
     jpeg_abort_compress(&cinfo);
     jpeg_abort_decompress(&dinfo);
     if (!quiet_mode) fprintf(LOG_FH," [Compress ERROR]\n");
     if (buf) FREE_LINE_BUF(buf,dinfo.output_height);
     compress_err_count++;
     jcerr.jump_set=0;
     continue;
   } else {
     jcerr.jump_set=1;
   }


   lastsize = 0;
   searchcount = 0;
   searchdone = 0;
   oldquality = 200;



  binary_search_loop:

   /* allocate memory buffer that should be large enough to store the output JPEG... */
   if (outbuffer) free(outbuffer);
   outbuffersize=insize + 32768;
   outbuffer=malloc(outbuffersize);
   if (!outbuffer) fatal("not enough memory");

   /* setup custom "destination manager" for libjpeg to write to our buffer */
   jpeg_memory_dest(&cinfo, &outbuffer, &outbuffersize, 65536);

   if (quality>=0 && !retry) {
     /* lossy "optimization" ... */

     cinfo.in_color_space=dinfo.out_color_space;
     cinfo.input_components=dinfo.output_components;
     cinfo.image_width=dinfo.image_width;
     cinfo.image_height=dinfo.image_height;
     jpeg_set_defaults(&cinfo); 
     jpeg_set_quality(&cinfo,quality,TRUE);
     if ( (dinfo.progressive_mode || all_progressive) && !all_normal )
       jpeg_simple_progression(&cinfo);
     cinfo.optimize_coding = TRUE;

     j=0;
     jpeg_start_compress(&cinfo,TRUE);
     
     /* write markers */
     write_markers(&dinfo,&cinfo);

     /* write image */
     while (cinfo.next_scanline < cinfo.image_height) {
       jpeg_write_scanlines(&cinfo,&buf[cinfo.next_scanline],
			    dinfo.output_height);
     }

   } else {
     /* lossless "optimization" ... */

     jpeg_copy_critical_parameters(&dinfo, &cinfo);
     if ( (dinfo.progressive_mode || all_progressive) && !all_normal )
       jpeg_simple_progression(&cinfo);
     cinfo.optimize_coding = TRUE;

     /* write image */
     jpeg_write_coefficients(&cinfo, coef_arrays);

     /* write markers */
     write_markers(&dinfo,&cinfo);

   }

   jpeg_finish_compress(&cinfo);
   outsize=outbuffersize;

   if (target_size != 0 && !retry) {
     /* perform (binary) search to try to reach target file size... */

     long osize = outsize/1024;
     long isize = insize/1024;
     long tsize = target_size;

     if (tsize < 0) { 
       tsize=((-target_size)*insize/100)/1024; 
       if (tsize < 1) tsize=1;
     }

     if (osize == tsize || searchdone || searchcount >= 8 || tsize > isize) {
       if (searchdone < 42 && lastsize > 0) {
	 if (abs(osize-tsize) > abs(lastsize-tsize)) {
	   if (verbose_mode) fprintf(LOG_FH,"(revert to %d)",oldquality);
	   searchdone=42;
	   quality=oldquality;
	   goto binary_search_loop;
	 }
       }
       if (verbose_mode) fprintf(LOG_FH," ");
       
     } else {
       int newquality;
       int dif = round(abs(oldquality-quality)/2.0);
       if (osize > tsize) {
	 newquality=quality-dif;
	 if (dif < 1) { newquality--; searchdone=1; }
	 if (newquality < 0) { newquality=0; searchdone=2; }
       } else {
	 newquality=quality+dif;
	 if (dif < 1) { newquality++; searchdone=3; }
	 if (newquality > 100) { newquality=100; searchdone=4; }
       }
       oldquality=quality;
       quality=newquality;

       if (verbose_mode) fprintf(LOG_FH,"(try %d)",quality);

       lastsize=osize;
       searchcount++;
       goto binary_search_loop;
     }
   } 

   if (buf) FREE_LINE_BUF(buf,dinfo.output_height);
   jpeg_finish_decompress(&dinfo);


   if (quality>=0 && outsize>=insize && !retry && !stdin_mode) {
     if (verbose_mode) fprintf(LOG_FH,"(retry w/lossless) ");
     retry=1;
     goto retry_point; 
   }

   retry=0;
   ratio=(insize-outsize)*100.0/insize;
   if (!quiet_mode || csv)
     fprintf(LOG_FH,csv ? "%ld,%ld,%0.2f," : "%ld --> %ld bytes (%0.2f%%), ",insize,outsize,ratio);
   average_count++;
   average_rate+=(ratio<0 ? 0.0 : ratio);

   if ((outsize < insize && ratio >= threshold) || force) {
        total_save+=(insize-outsize)/1024.0;
	if (!quiet_mode || csv) fprintf(LOG_FH,csv ? "optimized\n" : "optimized.\n");
        if (noaction) continue;

	if (stdout_mode) {
	  outfname=NULL;
	  if (fwrite(outbuffer,outbuffersize,1,stdout) != 1)
	    fatal("write failed to stdout");
	} else {
	  if (preserve_perms && !dest) {
	    /* make backup of the original file */
	    snprintf(tmpfilename,sizeof(tmpfilename),"%s.jpegoptim.bak",newname);
	    if (verbose_mode > 1 && !quiet_mode) 
	      fprintf(LOG_FH,"creating backup of original image as: %s\n",tmpfilename);
	    if (file_exists(tmpfilename))
	      fatal("backup file already exists: %s",tmpfilename);
	    if (copy_file(newname,tmpfilename))
	      fatal("failed to create backup of original file");
	    if ((outfile=fopen(newname,"wb"))==NULL)
	      fatal("error opening output file: %s", newname);
	    outfname=newname;
	  } else {
#ifdef HAVE_MKSTEMPS
	    /* rely on mkstemps() to create us temporary file safely... */  
	    snprintf(tmpfilename,sizeof(tmpfilename),
		     "%sjpegoptim-%d-%d.XXXXXX.tmp", tmpdir, (int)getuid(), (int)getpid());
	    if ((tmpfd = mkstemps(tmpfilename,4)) < 0) 
	      fatal("error creating temp file: mkstemps() failed");
	    if ((outfile=fdopen(tmpfd,"wb"))==NULL) 
#else
	      /* if platform is missing mkstemps(), try to create at least somewhat "safe" temp file... */  
	      snprintf(tmpfilename,sizeof(tmpfilename),
		       "%sjpegoptim-%d-%d.%d.tmp", tmpdir, (int)getuid(), (int)getpid(),time(NULL));
	    tmpfd=0;
	    if ((outfile=fopen(tmpfilename,"wb"))==NULL) 
#endif
	      fatal("error opening temporary file: %s",tmpfilename);
	    outfname=tmpfilename;
	  }

	  if (verbose_mode > 1 && !quiet_mode) 
	    fprintf(LOG_FH,"writing %lu bytes to file: %s\n",
		    (long unsigned int)outbuffersize, outfname);
	  if (fwrite(outbuffer,outbuffersize,1,outfile) != 1)
	    fatal("write failed to file: %s", outfname);
	  fclose(outfile);
	}

	if (outfname) {
	  
	  if (preserve_mode) {
	    /* preserve file modification time */
	    struct utimbuf time_save;
	    time_save.actime=file_stat.st_atime;
	    time_save.modtime=file_stat.st_mtime;
	    if (utime(outfname,&time_save) != 0) 
	      warn("failed to reset output file time/date");
	  }

	  if (preserve_perms && !dest) {
	    /* original file was already replaced, remove backup... */
	    if (delete_file(tmpfilename))
	      warn("failed to remove backup file: %s",tmpfilename);
	  } else {
	    /* make temp file to be the original file... */

	    /* preserve file mode */
	    if (chmod(outfname,(file_stat.st_mode & 0777)) != 0) 
	      warn("failed to set output file mode"); 

	    /* preserve file group (and owner if run by root) */
	    if (chown(outfname,
		      (geteuid()==0 ? file_stat.st_uid : -1),
		      file_stat.st_gid) != 0)
	      warn("failed to reset output file group/owner");

	    if (verbose_mode > 1 && !quiet_mode) 
	      fprintf(LOG_FH,"renaming: %s to %s\n",outfname,newname);
	    if (rename_file(outfname,newname)) fatal("cannot rename temp file");
	  }
	}
   } else {
     if (!quiet_mode || csv) fprintf(LOG_FH,csv ? "skipped\n" : "skipped.\n");
   }
   

  } while (++i<argc && !stdin_mode);


  if (totals_mode && !quiet_mode)
    fprintf(LOG_FH,"Average ""compression"" (%ld files): %0.2f%% (%0.0fk)\n",
	    average_count, average_rate/average_count, total_save);
  jpeg_destroy_decompress(&dinfo);
  jpeg_destroy_compress(&cinfo);

  return (decompress_err_count > 0 || compress_err_count > 0 ? 1 : 0);;
}