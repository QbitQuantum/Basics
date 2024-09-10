void SoundCardPMO::HandleTimeInfoEvent(PMOTimeInfoEvent *pEvent)
{
   MediaTimeInfoEvent *pmtpi;
   int32               hours, minutes, seconds;
   int                 iTotalTime = 0;
   MMTIME              sTime;

   if (m_iBaseTime == MAXINT32)
   {
       if (!pEvent)
          return;
          
       m_iBaseTime = (pEvent->GetFrameNumber() * m_samples_per_frame) / 
                      m_samples_per_second;

       sTime.wType = TIME_BYTES;
       if (waveOutGetPosition(m_hwo, &sTime, sizeof(sTime)) != MMSYSERR_NOERROR)
           return;
   
       m_iBaseTime -= (sTime.u.cb / (m_samples_per_second * m_iBytesPerSample));
	   m_iLastTime = 0;
   }

   if (m_samples_per_second <= 0)
      return;

   sTime.wType = TIME_BYTES;
   if (waveOutGetPosition(m_hwo, &sTime, sizeof(sTime)) != MMSYSERR_NOERROR)
       return;
   
   iTotalTime = (sTime.u.cb / (m_samples_per_second * m_iBytesPerSample)) +
                m_iBaseTime;

   // Time needs to be greater or equal to the last time for each pass,
   // otherwise we have a break in playback, in which case we need to
   // reset the base time. After a break in playback the waveOutGetPosition()
   // function will reset back to 0. 
   // Alternatively, if m_iBaseTime gets messed up (i.e. its more than 24 hours!)
   // force a reset as well.
   if (iTotalTime < m_iLastTime || (m_iBaseTime > 86400 && m_iBaseTime < MAXINT32))
   {
	   Debug_v("Reset: %d %d %d", iTotalTime, m_iLastTime, m_iBaseTime);
	   m_iBaseTime = MAXINT32;
	   return;
   }
      
   hours = iTotalTime / 3600;
   minutes = (iTotalTime - 
                (hours * 3600)) / 60;
   seconds = iTotalTime - 
                (hours * 3600) - 
                (minutes * 60);

   // If something became wonky, reset.
   if (minutes < 0 || minutes > 59 || 
	   seconds < 0 || seconds > 59 || 
	   hours < 0 || hours > 24)
   {
	  m_iBaseTime = MAXINT32;
      return;
   }

   pmtpi = new MediaTimeInfoEvent(hours, minutes, seconds, 0,
                                  (float)iTotalTime, 0);
   m_pTarget->AcceptEvent(pmtpi);
   m_iLastTime = iTotalTime;
}