uint8_t mpeg_passthrough(const char *name,ADM_OUT_FORMAT format )
{
  uint32_t len, flags;
  AVDMGenericAudioStream *audio=NULL;
  uint32_t audiolen;
  
  DIA_encoding *work;
  ADM_MUXER_TYPE mux;
  
  double total_wanted=0;
  uint32_t total_got=0;
  uint8_t ret=0;
 
  ADMMpegMuxer *muxer=NULL;
  ADMBitstream bitstream(0);
  
  	printf("Saving as mpg PS to file %s\n",name);
  
  	// First we check it is mpeg
	if(!isMpeg12Compatible(avifileinfo->fcc))
  	{
          GUI_Error_HIG(QT_TR_NOOP("This is not MPEG compatible"), QT_TR_NOOP("You can't use the Copy codec."));
		return 0 ;
  	}
  	if(!currentaudiostream)
  	{
          GUI_Error_HIG(QT_TR_NOOP("There is no audio track"), NULL);
		return 0;
  	}
  
	ADM_assert (video_body->getFlags (frameStart, &flags));
        if(!(flags&AVI_KEY_FRAME))
        {
          GUI_Error_HIG(QT_TR_NOOP("The first frame is not intra frame"), QT_TR_NOOP("Use the &lt;&lt; and the &gt;&gt; buttons to move using Intra frames."));
                return 0;
        }
	
  	audio=mpt_getAudioStream();
	
	// Have to check the type
	// If it is mpeg2 we use DVD-PS
	// If it is mpeg1 we use VCD-PS
	// Later check if it is SVCD
	if(!audio)
	{
          GUI_Error_HIG(QT_TR_NOOP("Audio track is not suitable"), NULL);
		return 0;
	}
	// Check
	WAVHeader *hdr=audio->getInfo();
	uint32_t isMpeg1;
	uint32_t isLav;
	if(!prefs->get(FEATURE_USE_LAVCODEC_MPEG2, &isLav))
		{
		 isLav=0;
		}

	if(!isLav)
	{
		decoderMpeg *mpeghdr;
	
		mpeghdr=(decoderMpeg *)video_body->rawGetDecoder(0);
		isMpeg1=mpeghdr->isMpeg1();
	}
	else
	{
		// How to know if it is mpeg 1?
		// Assume it is not
		/*
		decoderFFMpeg12 *mpeghdr;
	
		mpeghdr=(decoderFFMpeg12 *)video_body->rawGetDecoder(0);
		isMpeg1=mpeghdr->isMpeg1();
		*/
		isMpeg1=0;
	
	}
	
	switch(format)
        {
        case ADM_PS:	
                if(isMpeg1)
                {
                        if(hdr->frequency!=44100 ||  hdr->encoding != WAV_MP2)
                        {
                          GUI_Error_HIG(QT_TR_NOOP("Incompatible audio"), QT_TR_NOOP("For VCD, audio must be 44.1 kHz MP2."));
                                return 0 ;
                        }
                        mux=MUXER_VCD;
                        printf("PassThrough: Using VCD PS\n");        
                }else
                {    // Mpeg2 
                        aviInfo info;
                        video_body->getVideoInfo(&info);
                        if(hdr->frequency==44100 && info.width==480&& hdr->encoding == WAV_MP2 ) // SVCD ?
                        {
                                mux=MUXER_SVCD;
                                printf("PassThrough: Using SVCD PS\n");
                        }
                        else
                        {
                            uint32_t valid=0;
                                if(!prefs->get(FEATURE_MPEG_NO_LIMIT,&valid)) valid=0;
                                 // mpeg2, we do only DVD right now
                                if(hdr->frequency==48000) valid=1;
                                if((hdr->encoding != WAV_MP2 && hdr->encoding!=WAV_AC3 && hdr->encoding!=WAV_LPCM
                                && hdr->encoding!=WAV_DTS))
                                {
                                  valid=0;  
                                }
                    
                                if(!valid)
                                {
                                        deleteAudioFilter(audio);
                                       GUI_Error_HIG(("Incompatible audio"),QT_TR_NOOP( "For DVD, audio must be 48 kHz MP2(stereo), AC3, DTS or LPCM (stereo)."));
                                       return 0;
                                }
                         
                               mux=MUXER_DVD;
                               printf("PassThrough: Using DVD PS\n");
                        }
                }

  	        muxer=new mplexMuxer();
                break;
        case ADM_TS:     
             printf("Using TS output format\n");   
             muxer=new tsMuxer(); //lavMuxer();
             mux=MUXER_TS;
             break;
        default:
                ADM_assert(0);
                break;
        }
        
        if(!muxer)
         {
                 printf("No muxer ?\n");
                 return 0;
        }
	if(!muxer->open(name,0,mux,avifileinfo,audio->getInfo()))
	{
		delete muxer;
		muxer=NULL;
		printf("Muxer init failed\n");
		return 0;
		
	}
        
	// In copy mode it is better to recompute the gop timestamp
	muxer->forceRestamp();
  ///____________________________
  work=new DIA_encoding(avifileinfo->fps1000);
  work->setCodec(QT_TR_NOOP("Copy"));
  work->setAudioCodec(QT_TR_NOOP("---"));
  work->setPhasis(QT_TR_NOOP("Saving"));
  if(!audioProcessMode())
     work->setAudioCodec(QT_TR_NOOP("Copy"));
  else
     work->setAudioCodec(getStrFromAudioCodec(audio->getInfo()->encoding));
  switch(mux)
  {
    case MUXER_TS: work->setContainer(QT_TR_NOOP("MPEG TS"));break;
    case MUXER_VCD: work->setContainer(QT_TR_NOOP("MPEG VCD"));break;
    case MUXER_SVCD: work->setContainer(QT_TR_NOOP("MPEG SVCD"));break;
    case MUXER_DVD: work->setContainer(QT_TR_NOOP("MPEG DVD"));break;
    default:
        ADM_assert(0);
  }
  
  uint32_t cur=0;
  uint32_t target_sample=0;
  double target_time;
  aviInfo info;
        video_body->getVideoInfo(&info);
        target_time=frameEnd-frameStart+1;
        target_time*=1000;
        target_time/=info.fps1000; // target_time in second
        target_time*=audio->getInfo()->frequency;
        target_sample=(uint32_t)floor(target_time);

  uint8_t *buffer = new uint8_t[avifileinfo->width * avifileinfo->height * 3];
  uint8_t *audiobuffer = new uint8_t[4*48000*2]; // 2 sec worth of lpcm
  uint32_t position;
  EncoderCopy *copy=NULL;
        bitstream.data=buffer;
        bitstream.bufferSize=avifileinfo->width * avifileinfo->height * 3;
        
     /***************************
      Special case : Multithreaded
     ***************************/
        if(mux==MUXER_VCD || mux==MUXER_SVCD || mux==MUXER_DVD)
        {
          pthread_t audioThread,videoThread,muxerThread;
          copy=new EncoderCopy(NULL);
          muxerMT context;
          
          copy->configure(NULL);
          // 
          memset(&context,0,sizeof(context));
          context.videoEncoder=copy;
          context.audioEncoder=audio;
          context.muxer=( mplexMuxer *)muxer;
          context.nbVideoFrame=copy->getNbFrame();
          context.audioTargetSample=target_sample;
          context.audioBuffer=audiobuffer;
          context.bitstream=&bitstream;
          context.opaque=(void *)work;

           // start audio thread
          ADM_assert(!pthread_create(&audioThread,NULL,(THRINP)defaultAudioSlave,&context)); 
          ADM_assert(!pthread_create(&videoThread,NULL,(THRINP)copyVideoSlave,&context)); 
          while(1)
          {
            accessMutex.lock();
            if(context.audioDone==2 || context.videoDone==2 || !work->isAlive()) //ERROR
            {
              context.audioAbort=1;
              context.videoAbort=1;
              printf("[Copy] aborting\n");
            }
            if(context.audioDone && context.videoDone)
            {
              printf("[Copy]Both audio & video done\n");
              if(context.audioDone==1 && context.videoDone==1) ret=1;
              else ret=0;
              accessMutex.unlock();
              goto _abt;
            }
             // Update UI
            work->setAudioSize(context.feedAudio);
            context.feedVideo=0;
            accessMutex.unlock();
            ADM_usleep(1000*1000);
             
          }    
    
    
        }
        /**************************************************************************************/
        /* If we get here, it means output is MPEG_TS */ 
        /* We must use the audio packet Queue */
        /**************************************************************************************/
        ADM_assert(mux==MUXER_TS);
        {
            PacketQueue *pq;
            uint32_t mx,sample;
            pthread_t     audioThread;
            copy=new EncoderCopy(NULL);
            audioQueueMT context;
            uint8_t r;
            
            copy->configure(NULL);
            pq=new PacketQueue("TS audioQ",5000,2*1024*1024);
            memset(&context,0,sizeof(context));
            context.audioEncoder=audio;
            context.audioTargetSample=target_sample;
            context.packetQueue=pq;
              // start audio thread
            ADM_assert(!pthread_create(&audioThread,NULL,(THRINP)defaultAudioQueueSlave,&context));
            // Go!
             
            ADM_usleep(4000);
            mx=copy->getNbFrame();
            printf("Writing %u frames\n",mx);
            for(int frame=0;frame<mx;frame++)
            {
              while(muxer->needAudio())
              {
                if(pq->Pop(audiobuffer,&audiolen,&sample))
                {
                  if(audiolen)
                  {
                    muxer->writeAudioPacket(audiolen,audiobuffer);
                    //work->feedAudioFrame(audiolen);
                  }
                }else break;
              }
              ADM_assert(copy);
              bitstream.cleanup(frame);
              r=copy->encode ( frame, &bitstream);
              if(!r)
              {
                printf("TS:Frame %u error\n",frame);
                GUI_Error_HIG (QT_TR_NOOP("Error while encoding"), NULL);
                goto  stopit;
              }
              muxer->writeVideoPacket( &bitstream);

              work->setFrame(frame,bitstream.len,bitstream.out_quantizer,mx);
//              work->feedFrame(bitstream.len);
              if(!work->isAlive())
              {
                goto stopit;
              }
            }
        
    ret=1;
stopit:
    context.audioAbort=1;
    pq->Abort();
    // Wait for audio slave to be over
    while(!context.audioDone)
    {
      printf("Waiting Audio thread\n");
      ADM_usleep(500000); 
    }
    delete pq;
  } // End ts case 
  /************************************** TS End *********************************/
_abt:
  delete work;
  muxer->close();
  delete muxer;
  delete [] buffer;
  delete [] audiobuffer;
  deleteAudioFilter(audio);
  if(copy) delete copy;
  return ret;

}