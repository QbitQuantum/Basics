static void
NewWriter ( struct AHIRequest *ioreq,
            struct AHIDevUnit *iounit,
            struct AHIBase *AHIBase )
{
  int channel, sound;
  BOOL delay = FALSE;
  struct AHISampleInfo si;
  struct Library *AHIsubBase;

  AHIsubBase = ((struct AHIPrivAudioCtrl *) iounit->AudioCtrl)->ahiac_SubLib;

  si.ahisi_Type    = ioreq->ahir_Type;
  si.ahisi_Address = ioreq->ahir_Std.io_Data;
  si.ahisi_Length  = ioreq->ahir_Std.io_Length;

  // Load the sound
  
  for(sound = 0; sound < MAXSOUNDS; sound++)
  {
    if(iounit->Sounds[sound] == SOUND_FREE)
    {
      iounit->Sounds[sound] = SOUND_IN_USE;
      break;
    }
  }

  if((sound < MAXSOUNDS) &&
     (AHI_LoadSound(sound, AHIST_DYNAMICSAMPLE, &si, iounit->AudioCtrl)
      == AHIE_OK)) {

    GetExtras(ioreq)->Sound = sound;

    ObtainSemaphore(&iounit->ListLock);
  
    if(ioreq->ahir_Link)
    {
      // See if the linked request is playing, silent or waiting...
  
      if(FindNode((struct List *) &iounit->PlayingList,
          (struct Node *) ioreq->ahir_Link))
      {
        delay = TRUE;
      }
      else if(FindNode((struct List *) &iounit->SilentList,
          (struct Node *) ioreq->ahir_Link))
      {
        delay = TRUE;
      }
      else if(FindNode((struct List *) &iounit->WaitingList,
          (struct Node *) ioreq->ahir_Link))
      {
        delay = TRUE;
      }
    }

  // NOTE: ahir_Link changes direction here. When the user set's it, she makes a new
  // request point to an old. We let the old point to the next (that's more natural,
  // anyway...) It the user tries to link more than one request to another, we fail.
  
    if(delay)
    {
      if( ! ioreq->ahir_Link->ahir_Link)
      {
        struct AHIRequest *otherioreq = ioreq->ahir_Link;
      
        channel = GetExtras(ioreq->ahir_Link)->Channel;
        GetExtras(ioreq)->Channel = NOCHANNEL;
  
        otherioreq->ahir_Link = ioreq;
        ioreq->ahir_Link = NULL;
        Enqueue((struct List *) &iounit->WaitingList,(struct Node *) ioreq);
  
        if(channel != NOCHANNEL)
        {
          // Attach the request to the currently playing one
  
          AHIsub_Disable((struct AHIAudioCtrlDrv *) iounit->AudioCtrl);

          // Make SURE the current sound isn't already finished!
          
          if(otherioreq->ahir_Std.io_Command == AHICMD_WRITTEN)
          {
            AHIsub_Enable((struct AHIAudioCtrlDrv *) iounit->AudioCtrl);

            // OOPS! It's finished! Undo...
            Remove((struct Node *) ioreq);
            
            // Start sound as if it wasn't delayed (see below);
            AddWriter(ioreq, iounit, AHIBase);
          }
          else
          {
            iounit->Voices[channel].QueuedRequest = ioreq;
            iounit->Voices[channel].NextOffset  = PLAY;
            iounit->Voices[channel].NextRequest = NULL;
            AHI_Play(iounit->AudioCtrl,
                AHIP_BeginChannel,  channel,
                AHIP_LoopFreq,      ioreq->ahir_Frequency,
                AHIP_LoopVol,       ioreq->ahir_Volume,
                AHIP_LoopPan,       ioreq->ahir_Position,
                AHIP_LoopSound,     GetExtras(ioreq)->Sound,
                AHIP_LoopOffset,    ioreq->ahir_Std.io_Actual,
                AHIP_LoopLength,    ioreq->ahir_Std.io_Length - ioreq->ahir_Std.io_Actual,
                AHIP_EndChannel,    NULL,
                TAG_DONE);
            AHIsub_Enable((struct AHIAudioCtrlDrv *) iounit->AudioCtrl);
          }

        }
      }
      else // She tried to add more than one request to another one
      { 
        ioreq->ahir_Std.io_Error = AHIE_UNKNOWN;
        TermIO(ioreq, AHIBase);
      }
    }
    else // Sound is not delayed
    {
      ioreq->ahir_Link=NULL;
      AddWriter(ioreq, iounit, AHIBase);
    }

    ReleaseSemaphore(&iounit->ListLock);
  }
  else // No free sound found, or sound failed to load
  {
    ioreq->ahir_Std.io_Error = AHIE_UNKNOWN;
    TermIO(ioreq, AHIBase);
  }
}