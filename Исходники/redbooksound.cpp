    ~CDVolume()
    {
        // restore the volume settings for all of the CD players
        while (!m_listMixerLines.empty())
        {
            MixerLineData& mixerlinedata = m_listMixerLines.back();

            MIXERCONTROLDETAILS mixercontroldetails;

            mixercontroldetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
            mixercontroldetails.dwControlID = mixerlinedata.mixercontrol.dwControlID;
            mixercontroldetails.cChannels = mixerlinedata.cChannels;
            mixercontroldetails.cMultipleItems = 0;
            mixercontroldetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
            mixercontroldetails.paDetails = &(mixerlinedata.vmixercontrolsOld);
            
            ZVerify(mixerSetControlDetails(mixerlinedata.hmixer, &mixercontroldetails, MIXER_SETCONTROLDETAILSF_VALUE) 
                == MMSYSERR_NOERROR);
            ZVerify(mixerClose((HMIXER)mixerlinedata.hmixer) == MMSYSERR_NOERROR);

            m_listMixerLines.pop_back();
        }
    }