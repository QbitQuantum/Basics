int main(int argc, char **argv)
{
   int nb_samples, total_samples=0, nb_encoded;
   int c;
   int option_index = 0;
   char *inFile, *outFile;
   FILE *fin, *fout;
   short input[MAX_FRAME_SIZE];
   spx_int32_t frame_size;
   int quiet=0;
   spx_int32_t vbr_enabled=0;
   spx_int32_t vbr_max=0;
   int abr_enabled=0;
   spx_int32_t vad_enabled=0;
   spx_int32_t dtx_enabled=0;
   int nbBytes;
   const SpeexMode *mode=NULL;
   int modeID = -1;
   void *st;
   SpeexBits bits;
   char cbits[MAX_FRAME_BYTES];
   int with_skeleton = 0;
   struct option long_options[] =
   {
      {"wideband", no_argument, NULL, 0},
      {"ultra-wideband", no_argument, NULL, 0},
      {"narrowband", no_argument, NULL, 0},
      {"vbr", no_argument, NULL, 0},
      {"vbr-max-bitrate", required_argument, NULL, 0},
      {"abr", required_argument, NULL, 0},
      {"vad", no_argument, NULL, 0},
      {"dtx", no_argument, NULL, 0},
      {"quality", required_argument, NULL, 0},
      {"bitrate", required_argument, NULL, 0},
      {"nframes", required_argument, NULL, 0},
      {"comp", required_argument, NULL, 0},
#ifdef USE_SPEEXDSP
      {"denoise", no_argument, NULL, 0},
      {"agc", no_argument, NULL, 0},
#endif
      {"no-highpass", no_argument, NULL, 0},
      {"skeleton",no_argument,NULL, 0},
      {"help", no_argument, NULL, 0},
      {"quiet", no_argument, NULL, 0},
      {"le", no_argument, NULL, 0},
      {"be", no_argument, NULL, 0},
      {"8bit", no_argument, NULL, 0},
      {"16bit", no_argument, NULL, 0},
      {"stereo", no_argument, NULL, 0},
      {"rate", required_argument, NULL, 0},
      {"version", no_argument, NULL, 0},
      {"version-short", no_argument, NULL, 0},
      {"comment", required_argument, NULL, 0},
      {"author", required_argument, NULL, 0},
      {"title", required_argument, NULL, 0},
      {"print-rate", no_argument, NULL, 0},
      {0, 0, 0, 0}
   };
   int print_bitrate=0;
   spx_int32_t rate=0;
   spx_int32_t size;
   int chan=1;
   int fmt=16;
   spx_int32_t quality=-1;
   float vbr_quality=-1;
   int lsb=1;
   ogg_stream_state os;
   ogg_stream_state so; /* ogg stream for skeleton bitstream */
   ogg_page og;
   ogg_packet op;
   int bytes_written=0, ret, result;
   int id=-1;
   SpeexHeader header;
   int nframes=1;
   spx_int32_t complexity=3;
   const char* speex_version;
   char vendor_string[64];
   char *comments;
   int comments_length;
   int close_in=0, close_out=0;
   int eos=0;
   spx_int32_t bitrate=0;
   double cumul_bits=0, enc_frames=0;
   char first_bytes[12];
   int wave_input=0;
   spx_int32_t tmp;
#ifdef USE_SPEEXDSP
   SpeexPreprocessState *preprocess = NULL;
   int denoise_enabled=0, agc_enabled=0;
#endif
   int highpass_enabled=1;
   int output_rate=0;
   spx_int32_t lookahead = 0;

   speex_lib_ctl(SPEEX_LIB_GET_VERSION_STRING, (void*)&speex_version);
   snprintf(vendor_string, sizeof(vendor_string), "Encoded with Speex %s", speex_version);

   comment_init(&comments, &comments_length, vendor_string);

   /*Process command-line options*/
   while(1)
   {
      c = getopt_long (argc, argv, "nwuhvV",
                       long_options, &option_index);
      if (c==-1)
         break;

      switch(c)
      {
      case 0:
         if (strcmp(long_options[option_index].name,"narrowband")==0)
         {
            modeID = SPEEX_MODEID_NB;
         } else if (strcmp(long_options[option_index].name,"wideband")==0)
         {
            modeID = SPEEX_MODEID_WB;
         } else if (strcmp(long_options[option_index].name,"ultra-wideband")==0)
         {
            modeID = SPEEX_MODEID_UWB;
         } else if (strcmp(long_options[option_index].name,"vbr")==0)
         {
            vbr_enabled=1;
         } else if (strcmp(long_options[option_index].name,"vbr-max-bitrate")==0)
         {
            vbr_max=atoi(optarg);
            if (vbr_max<1)
            {
               fprintf (stderr, "Invalid VBR max bit-rate value: %d\n", vbr_max);
               exit(1);
            }
         } else if (strcmp(long_options[option_index].name,"abr")==0)
         {
            abr_enabled=atoi(optarg);
            if (!abr_enabled)
            {
               fprintf (stderr, "Invalid ABR value: %d\n", abr_enabled);
               exit(1);
            }
         } else if (strcmp(long_options[option_index].name,"vad")==0)
         {
            vad_enabled=1;
         } else if (strcmp(long_options[option_index].name,"dtx")==0)
         {
            dtx_enabled=1;
         } else if (strcmp(long_options[option_index].name,"quality")==0)
         {
            quality = atoi (optarg);
            vbr_quality=atof(optarg);
         } else if (strcmp(long_options[option_index].name,"bitrate")==0)
         {
            bitrate = atoi (optarg);
         } else if (strcmp(long_options[option_index].name,"nframes")==0)
         {
            nframes = atoi (optarg);
            if (nframes<1)
               nframes=1;
            if (nframes>10)
               nframes=10;
         } else if (strcmp(long_options[option_index].name,"comp")==0)
         {
            complexity = atoi (optarg);
#ifdef USE_SPEEXDSP
         } else if (strcmp(long_options[option_index].name,"denoise")==0)
         {
            denoise_enabled=1;
         } else if (strcmp(long_options[option_index].name,"agc")==0)
         {
            agc_enabled=1;
#endif
         } else if (strcmp(long_options[option_index].name,"no-highpass")==0)
         {
            highpass_enabled=0;
         } else if (strcmp(long_options[option_index].name,"skeleton")==0)
         {
            with_skeleton=1;
         } else if (strcmp(long_options[option_index].name,"help")==0)
         {
            usage();
            exit(0);
         } else if (strcmp(long_options[option_index].name,"quiet")==0)
         {
            quiet = 1;
         } else if (strcmp(long_options[option_index].name,"version")==0)
         {
            version();
            exit(0);
         } else if (strcmp(long_options[option_index].name,"version-short")==0)
         {
            version_short();
            exit(0);
         } else if (strcmp(long_options[option_index].name,"print-rate")==0)
         {
            output_rate=1;
         } else if (strcmp(long_options[option_index].name,"le")==0)
         {
            lsb=1;
         } else if (strcmp(long_options[option_index].name,"be")==0)
         {
            lsb=0;
         } else if (strcmp(long_options[option_index].name,"8bit")==0)
         {
            fmt=8;
         } else if (strcmp(long_options[option_index].name,"16bit")==0)
         {
            fmt=16;
         } else if (strcmp(long_options[option_index].name,"stereo")==0)
         {
            chan=2;
         } else if (strcmp(long_options[option_index].name,"rate")==0)
         {
            rate=atoi (optarg);
         } else if (strcmp(long_options[option_index].name,"comment")==0)
         {
            if (!strchr(optarg, '='))
            {
               fprintf (stderr, "Invalid comment: %s\n", optarg);
               fprintf (stderr, "Comments must be of the form name=value\n");
               exit(1);
            }
           comment_add(&comments, &comments_length, NULL, optarg);
         } else if (strcmp(long_options[option_index].name,"author")==0)
         {
           comment_add(&comments, &comments_length, "author=", optarg);
         } else if (strcmp(long_options[option_index].name,"title")==0)
         {
           comment_add(&comments, &comments_length, "title=", optarg);
         }

         break;
      case 'n':
         modeID = SPEEX_MODEID_NB;
         break;
      case 'h':
         usage();
         exit(0);
         break;
      case 'v':
         version();
         exit(0);
         break;
      case 'V':
         print_bitrate=1;
         break;
      case 'w':
         modeID = SPEEX_MODEID_WB;
         break;
      case 'u':
         modeID = SPEEX_MODEID_UWB;
         break;
      case '?':
         usage();
         exit(1);
         break;
      }
   }
   if (argc-optind!=2)
   {
      usage();
      exit(1);
   }
   inFile=argv[optind];
   outFile=argv[optind+1];

   /*Initialize Ogg stream struct*/
   srand(time(NULL));
   if (ogg_stream_init(&os, rand())==-1)
   {
      fprintf(stderr,"Error: stream init failed\n");
      exit(1);
   }
   if (with_skeleton && ogg_stream_init(&so, rand())==-1)
   {
      fprintf(stderr,"Error: stream init failed\n");
      exit(1);
   }

   if (strcmp(inFile, "-")==0)
   {
#if defined WIN32 || defined _WIN32
         _setmode(_fileno(stdin), _O_BINARY);
#elif defined OS2
         _fsetmode(stdin,"b");
#endif
      fin=stdin;
   }
   else
   {
      fin = fopen(inFile, "rb");
      if (!fin)
      {
         perror(inFile);
         exit(1);
      }
      close_in=1;
   }

   {
      if (fread(first_bytes, 1, 12, fin) != 12)
      {
         perror("short file");
         exit(1);
      }
      if (strncmp(first_bytes,"RIFF",4)==0 || strncmp(first_bytes,"riff",4)==0)
      {
         if (read_wav_header(fin, &rate, &chan, &fmt, &size)==-1)
            exit(1);
         wave_input=1;
         lsb=1; /* CHECK: exists big-endian .wav ?? */
      }
   }

   if (modeID==-1 && !rate)
   {
      /* By default, use narrowband/8 kHz */
      modeID = SPEEX_MODEID_NB;
      rate=8000;
   } else if (modeID!=-1 && rate)
   {
      mode = speex_lib_get_mode (modeID);
      if (rate>48000)
      {
         fprintf (stderr, "Error: sampling rate too high: %d Hz, try down-sampling\n", rate);
         exit(1);
      } else if (rate>25000)
      {
         if (modeID != SPEEX_MODEID_UWB)
         {
            fprintf (stderr, "Warning: Trying to encode in %s at %d Hz. I'll do it but I suggest you try ultra-wideband instead\n", mode->modeName , rate);
         }
      } else if (rate>12500)
      {
         if (modeID != SPEEX_MODEID_WB)
         {
            fprintf (stderr, "Warning: Trying to encode in %s at %d Hz. I'll do it but I suggest you try wideband instead\n", mode->modeName , rate);
         }
      } else if (rate>=6000)
      {
         if (modeID != SPEEX_MODEID_NB)
         {
            fprintf (stderr, "Warning: Trying to encode in %s at %d Hz. I'll do it but I suggest you try narrowband instead\n", mode->modeName , rate);
         }
      } else {
         fprintf (stderr, "Error: sampling rate too low: %d Hz\n", rate);
         exit(1);
      }
   } else if (modeID==-1)
   {
      if (rate>48000)
      {
         fprintf (stderr, "Error: sampling rate too high: %d Hz, try down-sampling\n", rate);
         exit(1);
      } else if (rate>25000)
      {
         modeID = SPEEX_MODEID_UWB;
      } else if (rate>12500)
      {
         modeID = SPEEX_MODEID_WB;
      } else if (rate>=6000)
      {
         modeID = SPEEX_MODEID_NB;
      } else {
         fprintf (stderr, "Error: Sampling rate too low: %d Hz\n", rate);
         exit(1);
      }
   } else if (!rate)
   {
      if (modeID == SPEEX_MODEID_NB)
         rate=8000;
      else if (modeID == SPEEX_MODEID_WB)
         rate=16000;
      else if (modeID == SPEEX_MODEID_UWB)
         rate=32000;
   }

   if (!quiet)
      if (rate!=8000 && rate!=16000 && rate!=32000)
         fprintf (stderr, "Warning: Speex is only optimized for 8, 16 and 32 kHz. It will still work at %d Hz but your mileage may vary\n", rate);

   if (!mode)
      mode = speex_lib_get_mode (modeID);

   speex_init_header(&header, rate, 1, mode);
   header.frames_per_packet=nframes;
   header.vbr=vbr_enabled;
   header.nb_channels = chan;

   {
      char *st_string="mono";
      if (chan==2)
         st_string="stereo";
      if (!quiet)
         fprintf (stderr, "Encoding %d Hz audio using %s mode (%s)\n",
               header.rate, mode->modeName, st_string);
   }
   /*fprintf (stderr, "Encoding %d Hz audio at %d bps using %s mode\n",
     header.rate, mode->bitrate, mode->modeName);*/

   /*Initialize Speex encoder*/
   st = speex_encoder_init(mode);

   if (strcmp(outFile,"-")==0)
   {
#if defined WIN32 || defined _WIN32
      _setmode(_fileno(stdout), _O_BINARY);
#endif
      fout=stdout;
   }
   else
   {
      fout = fopen(outFile, "wb");
      if (!fout)
      {
         perror(outFile);
         exit(1);
      }
      close_out=1;
   }

   speex_encoder_ctl(st, SPEEX_GET_FRAME_SIZE, &frame_size);
   speex_encoder_ctl(st, SPEEX_SET_COMPLEXITY, &complexity);
   speex_encoder_ctl(st, SPEEX_SET_SAMPLING_RATE, &rate);

   if (quality >= 0)
   {
      if (vbr_enabled)
      {
         if (vbr_max>0)
            speex_encoder_ctl(st, SPEEX_SET_VBR_MAX_BITRATE, &vbr_max);
         speex_encoder_ctl(st, SPEEX_SET_VBR_QUALITY, &vbr_quality);
      }
      else
         speex_encoder_ctl(st, SPEEX_SET_QUALITY, &quality);
   }
   if (bitrate)
   {
      if (quality >= 0 && vbr_enabled)
         fprintf (stderr, "Warning: --bitrate option is overriding --quality\n");
      speex_encoder_ctl(st, SPEEX_SET_BITRATE, &bitrate);
   }
   if (vbr_enabled)
   {
      tmp=1;
      speex_encoder_ctl(st, SPEEX_SET_VBR, &tmp);
   } else if (vad_enabled)
   {
      tmp=1;
      speex_encoder_ctl(st, SPEEX_SET_VAD, &tmp);
   }
   if (dtx_enabled)
      speex_encoder_ctl(st, SPEEX_SET_DTX, &tmp);
   if (dtx_enabled && !(vbr_enabled || abr_enabled || vad_enabled))
   {
      fprintf (stderr, "Warning: --dtx is useless without --vad, --vbr or --abr\n");
   } else if ((vbr_enabled || abr_enabled) && (vad_enabled))
   {
      fprintf (stderr, "Warning: --vad is already implied by --vbr or --abr\n");
   }
   if (with_skeleton) {
      fprintf (stderr, "Warning: Enabling skeleton output may cause some decoders to fail.\n");
   }

   if (abr_enabled)
   {
      speex_encoder_ctl(st, SPEEX_SET_ABR, &abr_enabled);
   }

   speex_encoder_ctl(st, SPEEX_SET_HIGHPASS, &highpass_enabled);

   speex_encoder_ctl(st, SPEEX_GET_LOOKAHEAD, &lookahead);

#ifdef USE_SPEEXDSP
   if (denoise_enabled || agc_enabled)
   {
      preprocess = speex_preprocess_state_init(frame_size, rate);
      speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_SET_DENOISE, &denoise_enabled);
      speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_SET_AGC, &agc_enabled);
      lookahead += frame_size;
   }
#endif
   /* first packet should be the skeleton header. */

   if (with_skeleton) {
      add_fishead_packet(&so);
      if ((ret = flush_ogg_stream_to_file(&so, fout))) {
         fprintf (stderr,"Error: failed skeleton (fishead) header to output stream\n");
         exit(1);
      } else
         bytes_written += ret;
   }

   /*Write header*/
   {
      int packet_size;
      op.packet = (unsigned char *)speex_header_to_packet(&header, &packet_size);
      op.bytes = packet_size;
      op.b_o_s = 1;
      op.e_o_s = 0;
      op.granulepos = 0;
      op.packetno = 0;
      ogg_stream_packetin(&os, &op);
      free(op.packet);

      while((result = ogg_stream_flush(&os, &og)))
      {
         if(!result) break;
         ret = oe_write_page(&og, fout);
         if(ret != og.header_len + og.body_len)
         {
            fprintf (stderr,"Error: failed writing header to output stream\n");
            exit(1);
         }
         else
            bytes_written += ret;
      }

      op.packet = (unsigned char *)comments;
      op.bytes = comments_length;
      op.b_o_s = 0;
      op.e_o_s = 0;
      op.granulepos = 0;
      op.packetno = 1;
      ogg_stream_packetin(&os, &op);
   }

   /* fisbone packet should be write after all bos pages */
   if (with_skeleton) {
      add_fisbone_packet(&so, os.serialno, &header);
      if ((ret = flush_ogg_stream_to_file(&so, fout))) {
         fprintf (stderr,"Error: failed writing skeleton (fisbone )header to output stream\n");
         exit(1);
      } else
         bytes_written += ret;
   }

   /* writing the rest of the speex header packets */
   while((result = ogg_stream_flush(&os, &og)))
   {
      if(!result) break;
      ret = oe_write_page(&og, fout);
      if(ret != og.header_len + og.body_len)
      {
         fprintf (stderr,"Error: failed writing header to output stream\n");
         exit(1);
      }
      else
         bytes_written += ret;
   }

   free(comments);

   /* write the skeleton eos packet */
   if (with_skeleton) {
      add_eos_packet_to_stream(&so);
      if ((ret = flush_ogg_stream_to_file(&so, fout))) {
         fprintf (stderr,"Error: failed writing skeleton header to output stream\n");
         exit(1);
      } else
         bytes_written += ret;
   }


   speex_bits_init(&bits);

   if (!wave_input)
   {
      nb_samples = read_samples(fin,frame_size,fmt,chan,lsb,input, first_bytes, NULL);
   } else {
      nb_samples = read_samples(fin,frame_size,fmt,chan,lsb,input, NULL, &size);
   }
   if (nb_samples==0)
      eos=1;
   total_samples += nb_samples;
   nb_encoded = -lookahead;
   /*Main encoding loop (one frame per iteration)*/
   while (!eos || total_samples>nb_encoded)
   {
      id++;
      /*Encode current frame*/
      if (chan==2)
         speex_encode_stereo_int(input, frame_size, &bits);

#ifdef USE_SPEEXDSP
      if (preprocess)
         speex_preprocess(preprocess, input, NULL);
#endif
      speex_encode_int(st, input, &bits);

      nb_encoded += frame_size;
      if (print_bitrate) {
         int tmp;
         char ch=13;
         speex_encoder_ctl(st, SPEEX_GET_BITRATE, &tmp);
         fputc (ch, stderr);
         cumul_bits += tmp;
         enc_frames += 1;
         if (!quiet)
         {
            if (vad_enabled || vbr_enabled || abr_enabled)
               fprintf (stderr, "Bitrate is use: %d bps  (average %d bps)   ", tmp, (int)(cumul_bits/enc_frames));
            else
               fprintf (stderr, "Bitrate is use: %d bps     ", tmp);
            if (output_rate)
               printf ("%d\n", tmp);
         }

      }

      if (wave_input)
      {
         nb_samples = read_samples(fin,frame_size,fmt,chan,lsb,input, NULL, &size);
      } else {
         nb_samples = read_samples(fin,frame_size,fmt,chan,lsb,input, NULL, NULL);
      }
      if (nb_samples==0)
      {
         eos=1;
      }
      if (eos && total_samples<=nb_encoded)
         op.e_o_s = 1;
      else
         op.e_o_s = 0;
      total_samples += nb_samples;

      if ((id+1)%nframes!=0)
         continue;
      speex_bits_insert_terminator(&bits);
      nbBytes = speex_bits_write(&bits, cbits, MAX_FRAME_BYTES);
      speex_bits_reset(&bits);
      op.packet = (unsigned char *)cbits;
      op.bytes = nbBytes;
      op.b_o_s = 0;
      /*Is this redundent?*/
      if (eos && total_samples<=nb_encoded)
         op.e_o_s = 1;
      else
         op.e_o_s = 0;
      op.granulepos = (id+1)*frame_size-lookahead;
      if (op.granulepos>total_samples)
         op.granulepos = total_samples;
      /*printf ("granulepos: %d %d %d %d %d %d\n", (int)op.granulepos, id, nframes, lookahead, 5, 6);*/
      op.packetno = 2+id/nframes;
      ogg_stream_packetin(&os, &op);

      /*Write all new pages (most likely 0 or 1)*/
      while (ogg_stream_pageout(&os,&og))
      {
         ret = oe_write_page(&og, fout);
         if(ret != og.header_len + og.body_len)
         {
            fprintf (stderr,"Error: failed writing header to output stream\n");
            exit(1);
         }
         else
            bytes_written += ret;
      }
   }
   if ((id+1)%nframes!=0)
   {
      while ((id+1)%nframes!=0)
      {
         id++;
         speex_bits_pack(&bits, 15, 5);
      }
      nbBytes = speex_bits_write(&bits, cbits, MAX_FRAME_BYTES);
      op.packet = (unsigned char *)cbits;
      op.bytes = nbBytes;
      op.b_o_s = 0;
      op.e_o_s = 1;
      op.granulepos = (id+1)*frame_size-lookahead;
      if (op.granulepos>total_samples)
         op.granulepos = total_samples;

      op.packetno = 2+id/nframes;
      ogg_stream_packetin(&os, &op);
   }
   /*Flush all pages left to be written*/
   while (ogg_stream_flush(&os, &og))
   {
      ret = oe_write_page(&og, fout);
      if(ret != og.header_len + og.body_len)
      {
         fprintf (stderr,"Error: failed writing header to output stream\n");
         exit(1);
      }
      else
         bytes_written += ret;
   }

   speex_encoder_destroy(st);
   speex_bits_destroy(&bits);
   ogg_stream_clear(&os);

   if (close_in)
      fclose(fin);
   if (close_out)
      fclose(fout);
   return 0;
}