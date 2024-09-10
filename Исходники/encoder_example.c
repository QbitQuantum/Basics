int main(int argc,char *argv[]){
  int c,long_option_index,ret;

  ogg_stream_state to; /* take physical pages, weld into a logical
                           stream of packets */
  ogg_stream_state vo; /* take physical pages, weld into a logical
                           stream of packets */
  ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
  ogg_packet       op; /* one raw packet of data for decode */

  theora_state     td;
  theora_info      ti;
  theora_comment   tc;

  vorbis_info      vi; /* struct that stores all the static vorbis bitstream
                          settings */
  vorbis_comment   vc; /* struct that stores all the user comments */

  vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
  vorbis_block     vb; /* local working space for packet->PCM decode */

  int audioflag=0;
  int videoflag=0;
  int akbps=0;
  int vkbps=0;

  ogg_int64_t audio_bytesout=0;
  ogg_int64_t video_bytesout=0;
  double timebase;


  FILE* outfile = stdout;

#ifdef _WIN32 
# ifdef THEORA_PERF_DATA
    LARGE_INTEGER start_time;
    LARGE_INTEGER final_time;

    LONGLONG elapsed_ticks;
    LARGE_INTEGER ticks_per_second;
    
    LONGLONG elapsed_secs;
    LONGLONG elapsed_sec_mod;
    double elapsed_secs_dbl ;
# endif
  /* We need to set stdin/stdout to binary mode. Damn windows. */
  /* if we were reading/writing a file, it would also need to in
     binary mode, eg, fopen("file.wav","wb"); */
  /* Beware the evil ifdef. We avoid these where we can, but this one we
     cannot. Don't add any more, you'll probably go to hell if you do. */
  _setmode( _fileno( stdin ), _O_BINARY );
  _setmode( _fileno( stdout ), _O_BINARY );


#endif

  while((c=getopt_long(argc,argv,optstring,options,&long_option_index))!=EOF){
    switch(c){
    case 'o':
      outfile=fopen(optarg,"wb");
      if(outfile==NULL){
        fprintf(stderr,"Unable to open output file '%s'\n", optarg);
        exit(1);
      }
      break;;

    case 'a':
      audio_q=atof(optarg)*.099;
      if(audio_q<-.1 || audio_q>1){
        fprintf(stderr,"Illegal audio quality (choose -1 through 10)\n");
        exit(1);
      }
      audio_r=-1;
      break;

    case 'v':
      video_q=rint(atof(optarg)*6.3);
      if(video_q<0 || video_q>63){
        fprintf(stderr,"Illegal video quality (choose 0 through 10)\n");
        exit(1);
      }
      video_r=0;
      break;

    case 'A':
      audio_r=atof(optarg)*1000;
      if(audio_q<0){
        fprintf(stderr,"Illegal audio quality (choose > 0 please)\n");
        exit(1);
      }
      audio_q=-99;
      break;

    case 'V':
      video_r=rint(atof(optarg)*1000);
      if(video_r<45000 || video_r>2000000){
        fprintf(stderr,"Illegal video bitrate (choose 45kbps through 2000kbps)\n");
        exit(1);
      }
      video_q=0;
     break;

    case 's':
      video_an=rint(atof(optarg));
      break;

    case 'S':
      video_ad=rint(atof(optarg));
      break;

    case 'f':
      video_hzn=rint(atof(optarg));
      break;

    case 'F':
      video_hzd=rint(atof(optarg));
      break;

    default:
      usage();
    }
  }

  while(optind<argc){
    /* assume that anything following the options must be a filename */
    id_file(argv[optind]);
    optind++;
  }



#ifdef THEORA_PERF_DATA
# ifdef WIN32
    QueryPerformanceCounter(&start_time);
# endif
#endif


  /* yayness.  Set up Ogg output stream */
  srand(time(NULL));
  {
    /* need two inequal serial numbers */
    int serial1, serial2;
    serial1 = rand();
    serial2 = rand();
    if (serial1 == serial2) serial2++;
    ogg_stream_init(&to,serial1);
    ogg_stream_init(&vo,serial2);
  }

  /* Set up Theora encoder */
  if(!video){
    fprintf(stderr,"No video files submitted for compression?\n");
    exit(1);
  }
  /* Theora has a divisible-by-sixteen restriction for the encoded video size */
  /* scale the frame size up to the nearest /16 and calculate offsets */
  video_x=((frame_x + 15) >>4)<<4;
  video_y=((frame_y + 15) >>4)<<4;
  /* We force the offset to be even.
     This ensures that the chroma samples align properly with the luma
      samples. */
  frame_x_offset=((video_x-frame_x)/2)&~1;
  frame_y_offset=((video_y-frame_y)/2)&~1;

  theora_info_init(&ti);
  ti.width=video_x;
  ti.height=video_y;
  ti.frame_width=frame_x;
  ti.frame_height=frame_y;
  ti.offset_x=frame_x_offset;
  ti.offset_y=frame_y_offset;
  ti.fps_numerator=video_hzn;
  ti.fps_denominator=video_hzd;
  ti.aspect_numerator=video_an;
  ti.aspect_denominator=video_ad;
  ti.colorspace=OC_CS_UNSPECIFIED;
  ti.pixelformat=OC_PF_420;
  ti.target_bitrate=video_r;
  ti.quality=video_q;

  ti.dropframes_p=0;
  ti.quick_p=1;
  ti.keyframe_auto_p=1;
  ti.keyframe_frequency=64;
  ti.keyframe_frequency_force=64;
  ti.keyframe_data_target_bitrate=video_r*1.5;
  ti.keyframe_auto_threshold=80;
  ti.keyframe_mindistance=8;
  ti.noise_sensitivity=1;

  theora_encode_init(&td,&ti);
  theora_info_clear(&ti);

  /* initialize Vorbis too, assuming we have audio to compress. */
  if(audio){
    vorbis_info_init(&vi);
    if(audio_q>-99)
      ret = vorbis_encode_init_vbr(&vi,audio_ch,audio_hz,audio_q);
    else
      ret = vorbis_encode_init(&vi,audio_ch,audio_hz,-1,audio_r,-1);
    if(ret){
      fprintf(stderr,"The Vorbis encoder could not set up a mode according to\n"
              "the requested quality or bitrate.\n\n");
      exit(1);
    }

    vorbis_comment_init(&vc);
    vorbis_analysis_init(&vd,&vi);
    vorbis_block_init(&vd,&vb);
  }

  /* write the bitstream header packets with proper page interleave */

  /* first packet will get its own page automatically */
  theora_encode_header(&td,&op);
  ogg_stream_packetin(&to,&op);
  if(ogg_stream_pageout(&to,&og)!=1){
    fprintf(stderr,"Internal Ogg library error.\n");
    exit(1);
  }
  fwrite(og.header,1,og.header_len,outfile);
  fwrite(og.body,1,og.body_len,outfile);

  /* create the remaining theora headers */
  theora_comment_init(&tc);
  theora_encode_comment(&tc,&op);
  ogg_stream_packetin(&to,&op);
  /*theora_encode_comment() doesn't take a theora_state parameter, so it has to
     allocate its own buffer to pass back the packet data.
    If we don't free it here, we'll leak.
    libogg2 makes this much cleaner: the stream owns the buffer after you call
     packetin in libogg2, but this is not true in libogg1.*/
  free(op.packet);
  theora_encode_tables(&td,&op);
  ogg_stream_packetin(&to,&op);

  if(audio){
    ogg_packet header;
    ogg_packet header_comm;
    ogg_packet header_code;

    vorbis_analysis_headerout(&vd,&vc,&header,&header_comm,&header_code);
    ogg_stream_packetin(&vo,&header); /* automatically placed in its own
                                         page */
    if(ogg_stream_pageout(&vo,&og)!=1){
      fprintf(stderr,"Internal Ogg library error.\n");
      exit(1);
    }
    fwrite(og.header,1,og.header_len,outfile);
    fwrite(og.body,1,og.body_len,outfile);

    /* remaining vorbis header packets */
    ogg_stream_packetin(&vo,&header_comm);
    ogg_stream_packetin(&vo,&header_code);
  }

  /* Flush the rest of our headers. This ensures
     the actual data in each stream will start
     on a new page, as per spec. */
  while(1){
    int result = ogg_stream_flush(&to,&og);
      if(result<0){
        /* can't get here */
        fprintf(stderr,"Internal Ogg library error.\n");
        exit(1);
      }
    if(result==0)break;
    fwrite(og.header,1,og.header_len,outfile);
    fwrite(og.body,1,og.body_len,outfile);
  }
  if(audio){
    while(1){
      int result=ogg_stream_flush(&vo,&og);
      if(result<0){
        /* can't get here */
        fprintf(stderr,"Internal Ogg library error.\n");
        exit(1);
      }
      if(result==0)break;
      fwrite(og.header,1,og.header_len,outfile);
      fwrite(og.body,1,og.body_len,outfile);
    }
  }

  /* setup complete.  Raw processing loop */
  fprintf(stderr,"Compressing....\n");
  while(1){
    ogg_page audiopage;
    ogg_page videopage;

    /* is there an audio page flushed?  If not, fetch one if possible */
    audioflag=fetch_and_process_audio(audio,&audiopage,&vo,&vd,&vb,audioflag);

    /* is there a video page flushed?  If not, fetch one if possible */
    videoflag=fetch_and_process_video(video,&videopage,&to,&td,videoflag);

    /* no pages of either?  Must be end of stream. */
    if(!audioflag && !videoflag)break;

    /* which is earlier; the end of the audio page or the end of the
       video page? Flush the earlier to stream */
    {
      int audio_or_video=-1;
      double audiotime=
        audioflag?vorbis_granule_time(&vd,ogg_page_granulepos(&audiopage)):-1;
      double videotime=
        videoflag?theora_granule_time(&td,ogg_page_granulepos(&videopage)):-1;

      if(!audioflag){
        audio_or_video=1;
      } else if(!videoflag) {
        audio_or_video=0;
      } else {
        if(audiotime<videotime)
          audio_or_video=0;
        else
          audio_or_video=1;
      }

      if(audio_or_video==1){
        /* flush a video page */
        video_bytesout+=fwrite(videopage.header,1,videopage.header_len,outfile);
        video_bytesout+=fwrite(videopage.body,1,videopage.body_len,outfile);
        videoflag=0;
        timebase=videotime;
        
      }else{
        /* flush an audio page */
        audio_bytesout+=fwrite(audiopage.header,1,audiopage.header_len,outfile);
        audio_bytesout+=fwrite(audiopage.body,1,audiopage.body_len,outfile);
        audioflag=0;
        timebase=audiotime;
      }
      {
        int hundredths=timebase*100-(long)timebase*100;
        int seconds=(long)timebase%60;
        int minutes=((long)timebase/60)%60;
        int hours=(long)timebase/3600;
        
        if(audio_or_video)
          vkbps=rint(video_bytesout*8./timebase*.001);
        else
          akbps=rint(audio_bytesout*8./timebase*.001);
        
        fprintf(stderr,
                "\r      %d:%02d:%02d.%02d audio: %dkbps video: %dkbps                 ",
                hours,minutes,seconds,hundredths,akbps,vkbps);
      }
    }

  }

  /* clear out state */

  if(audio){
    ogg_stream_clear(&vo);
    vorbis_block_clear(&vb);
    vorbis_dsp_clear(&vd);
    vorbis_comment_clear(&vc);
    vorbis_info_clear(&vi);
  }
  if(video){
    ogg_stream_clear(&to);
    theora_clear(&td);
  }

  if(outfile && outfile!=stdout)fclose(outfile);

  fprintf(stderr,"\r   \ndone.\n\n");

#ifdef THEORA_PERF_DATA
# ifdef WIN32
    QueryPerformanceCounter(&final_time);
    elapsed_ticks = final_time.QuadPart - start_time.QuadPart;
    ticks_per_second;
    QueryPerformanceFrequency(&ticks_per_second);
    elapsed_secs = elapsed_ticks / ticks_per_second.QuadPart;
    elapsed_sec_mod = elapsed_ticks % ticks_per_second.QuadPart;
    elapsed_secs_dbl = elapsed_secs;
    elapsed_secs_dbl += ((double)elapsed_sec_mod / (double)ticks_per_second.QuadPart);
    printf("Encode time = %lld ticks\n", elapsed_ticks);
    printf("~%lld and %lld / %lld seconds\n", elapsed_secs, elapsed_sec_mod, ticks_per_second.QuadPart);
    printf("~%Lf seconds\n", elapsed_secs_dbl);
# endif

#endif 

  return(0);

}