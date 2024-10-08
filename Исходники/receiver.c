void cLivePatFilter::Process(u_short Pid, u_char Tid, const u_char *Data, int Length)
{
  if (Pid == 0x00)
  {
    if (Tid == 0x00)
    {
      SI::PAT pat(Data, false);
      if (!pat.CheckCRCAndParse())
        return;
      SI::PAT::Association assoc;
      for (SI::Loop::Iterator it; pat.associationLoop.getNext(assoc, it); )
      {
        if (!assoc.isNITPid())
        {
          const cChannel *Channel =  Channels.GetByServiceID(Source(), Transponder(), assoc.getServiceId());
          if (Channel && (Channel == m_Channel))
          {
            int prevPmtPid = m_pmtPid;
            if (0 != (m_pmtPid = assoc.getPid()))
            {
              if (m_pmtPid != prevPmtPid)
              {
                m_pmtSid = assoc.getServiceId();
                Add(m_pmtPid, 0x02);
                m_pmtVersion = -1;
                break;
              }
              return;
            }
          }
        }
      }
    }
  }
  else if (Pid == m_pmtPid && Tid == SI::TableIdPMT && Source() && Transponder())
  {
    SI::PMT pmt(Data, false);
    if (!pmt.CheckCRCAndParse())
      return;
    if (pmt.getServiceId() != m_pmtSid)
      return; // skip broken PMT records
    if (m_pmtVersion != -1)
    {
      if (m_pmtVersion != pmt.getVersionNumber())
      {
        cFilter::Del(m_pmtPid, 0x02);
        m_pmtPid = 0; // this triggers PAT scan
      }
      return;
    }
    m_pmtVersion = pmt.getVersionNumber();

    cChannel *Channel = Channels.GetByServiceID(Source(), Transponder(), pmt.getServiceId());
    if (Channel) {
       // Scan the stream-specific loop:
       SI::PMT::Stream stream;
       int Vpid = 0;
       int Ppid = 0;
       int Vtype = 0;
       int Apids[MAXAPIDS + 1] = { 0 }; // these lists are zero-terminated
       int Atypes[MAXAPIDS + 1] = { 0 };
       int Dpids[MAXDPIDS + 1] = { 0 };
       int Dtypes[MAXDPIDS + 1] = { 0 };
       int Spids[MAXSPIDS + 1] = { 0 };
       uchar SubtitlingTypes[MAXSPIDS + 1] = { 0 };
       uint16_t CompositionPageIds[MAXSPIDS + 1] = { 0 };
       uint16_t AncillaryPageIds[MAXSPIDS + 1] = { 0 };
       char ALangs[MAXAPIDS][MAXLANGCODE2] = { "" };
       char DLangs[MAXDPIDS][MAXLANGCODE2] = { "" };
       char SLangs[MAXSPIDS][MAXLANGCODE2] = { "" };
       int Tpid = 0;
       int NumApids = 0;
       int NumDpids = 0;
       int NumSpids = 0;
       for (SI::Loop::Iterator it; pmt.streamLoop.getNext(stream, it); ) {
           bool ProcessCaDescriptors = false;
           int esPid = stream.getPid();
           switch (stream.getStreamType()) {
             case 1: // STREAMTYPE_11172_VIDEO
             case 2: // STREAMTYPE_13818_VIDEO
             case 0x1B: // MPEG4
                     Vpid = esPid;
                     Ppid = pmt.getPCRPid();
                     Vtype = stream.getStreamType();
                     ProcessCaDescriptors = true;
                     break;
             case 3: // STREAMTYPE_11172_AUDIO
             case 4: // STREAMTYPE_13818_AUDIO
             case 0x0F: // ISO/IEC 13818-7 Audio with ADTS transport syntax
             case 0x11: // ISO/IEC 14496-3 Audio with LATM transport syntax
                     {
                     if (NumApids < MAXAPIDS) {
                        Apids[NumApids] = esPid;
                        Atypes[NumApids] = stream.getStreamType();
                        SI::Descriptor *d;
                        for (SI::Loop::Iterator it; (d = stream.streamDescriptors.getNext(it)); ) {
                            switch (d->getDescriptorTag()) {
                              case SI::ISO639LanguageDescriptorTag: {
                                   SI::ISO639LanguageDescriptor *ld = (SI::ISO639LanguageDescriptor *)d;
                                   SI::ISO639LanguageDescriptor::Language l;
                                   char *s = ALangs[NumApids];
                                   int n = 0;
                                   for (SI::Loop::Iterator it; ld->languageLoop.getNext(l, it); ) {
                                       if (*ld->languageCode != '-') { // some use "---" to indicate "none"
                                          if (n > 0)
                                             *s++ = '+';
                                          strn0cpy(s, I18nNormalizeLanguageCode(l.languageCode), MAXLANGCODE1);
                                          s += strlen(s);
                                          if (n++ > 1)
                                             break;
                                          }
                                       }
                                   }
                                   break;
                              default: ;
                              }
                            delete d;
                            }
                        NumApids++;
                        }
                     ProcessCaDescriptors = true;
                     }
                     break;
             case 5: // STREAMTYPE_13818_PRIVATE
             case 6: // STREAMTYPE_13818_PES_PRIVATE
             //XXX case 8: // STREAMTYPE_13818_DSMCC
                     {
                     int dpid = 0;
                     int dtype = 0;
                     char lang[MAXLANGCODE1] = { 0 };
                     SI::Descriptor *d;
                     for (SI::Loop::Iterator it; (d = stream.streamDescriptors.getNext(it)); ) {
                         switch (d->getDescriptorTag()) {
                           case SI::AC3DescriptorTag:
                           case SI::EnhancedAC3DescriptorTag:
                                dpid = esPid;
                                dtype = d->getDescriptorTag();
                                ProcessCaDescriptors = true;
                                break;
                           case SI::SubtitlingDescriptorTag:
                                if (NumSpids < MAXSPIDS) {
                                   Spids[NumSpids] = esPid;
                                   SI::SubtitlingDescriptor *sd = (SI::SubtitlingDescriptor *)d;
                                   SI::SubtitlingDescriptor::Subtitling sub;
                                   char *s = SLangs[NumSpids];
                                   int n = 0;
                                   for (SI::Loop::Iterator it; sd->subtitlingLoop.getNext(sub, it); ) {
                                       if (sub.languageCode[0]) {
                                          SubtitlingTypes[NumSpids] = sub.getSubtitlingType();
                                          CompositionPageIds[NumSpids] = sub.getCompositionPageId();
                                          AncillaryPageIds[NumSpids] = sub.getAncillaryPageId();
                                          if (n > 0)
                                             *s++ = '+';
                                          strn0cpy(s, I18nNormalizeLanguageCode(sub.languageCode), MAXLANGCODE1);
                                          s += strlen(s);
                                          if (n++ > 1)
                                             break;
                                          }
                                       }
                                   NumSpids++;
                                   }
                                break;
                           case SI::TeletextDescriptorTag:
                                Tpid = esPid;
                                break;
                           case SI::ISO639LanguageDescriptorTag: {
                                SI::ISO639LanguageDescriptor *ld = (SI::ISO639LanguageDescriptor *)d;
                                strn0cpy(lang, I18nNormalizeLanguageCode(ld->languageCode), MAXLANGCODE1);
                                }
                                break;
                           default: ;
                           }
                         delete d;
                         }
                     if (dpid) {
                        if (NumDpids < MAXDPIDS) {
                           Dpids[NumDpids] = dpid;
                           Dtypes[NumDpids] = dtype;
                           strn0cpy(DLangs[NumDpids], lang, MAXLANGCODE1);
                           NumDpids++;
                           }
                        }
                     }
                     break;
             case 0x80: // STREAMTYPE_USER_PRIVATE
#if APIVERSNUM >= 10728
                     if (Setup.StandardCompliance == STANDARD_ANSISCTE)
#endif
                     { // DigiCipher II VIDEO (ANSI/SCTE 57)
                        Vpid = esPid;
                        Ppid = pmt.getPCRPid();
                        Vtype = 0x02; // compression based upon MPEG-2
                        ProcessCaDescriptors = true;
                        break;
                        }
                     // fall through
             case 0x81: // STREAMTYPE_USER_PRIVATE
#if APIVERSNUM >= 10728
                     if (Setup.StandardCompliance == STANDARD_ANSISCTE)
#endif
                     { // ATSC A/53 AUDIO (ANSI/SCTE 57)
                        char lang[MAXLANGCODE1] = { 0 };
                        SI::Descriptor *d;
                        for (SI::Loop::Iterator it; (d = stream.streamDescriptors.getNext(it)); ) {
                            switch (d->getDescriptorTag()) {
                              case SI::ISO639LanguageDescriptorTag: {
                                   SI::ISO639LanguageDescriptor *ld = (SI::ISO639LanguageDescriptor *)d;
                                   strn0cpy(lang, I18nNormalizeLanguageCode(ld->languageCode), MAXLANGCODE1);
                                   }
                                   break;
                              default: ;
                              }
                           delete d;
                           }
                        if (NumDpids < MAXDPIDS) {
                           Dpids[NumDpids] = esPid;
                           Dtypes[NumDpids] = SI::AC3DescriptorTag;
                           strn0cpy(DLangs[NumDpids], lang, MAXLANGCODE1);
                           NumDpids++;
                           }
                        ProcessCaDescriptors = true;
                        break;
                        }
                     // fall through
             case 0x82: // STREAMTYPE_USER_PRIVATE
#if APIVERSNUM >= 10728
                     if (Setup.StandardCompliance == STANDARD_ANSISCTE)
#endif
                     { // STANDARD SUBTITLE (ANSI/SCTE 27)
                        //TODO
                        break;
                        }
                     // fall through
             case 0x83 ... 0xFF: // STREAMTYPE_USER_PRIVATE
                     {
                     char lang[MAXLANGCODE1] = { 0 };
                     bool IsAc3 = false;
                     SI::Descriptor *d;
                     for (SI::Loop::Iterator it; (d = stream.streamDescriptors.getNext(it)); ) {
                         switch (d->getDescriptorTag()) {
                           case SI::RegistrationDescriptorTag: {
                                SI::RegistrationDescriptor *rd = (SI::RegistrationDescriptor *)d;
                                // http://www.smpte-ra.org/mpegreg/mpegreg.html
                                switch (rd->getFormatIdentifier()) {
                                  case 0x41432D33: // 'AC-3'
                                       IsAc3 = true;
                                       break;
                                  default:
                                       //printf("Format identifier: 0x%08X (pid: %d)\n", rd->getFormatIdentifier(), esPid);
                                       break;
                                  }
                                }
                                break;
                           case SI::ISO639LanguageDescriptorTag: {
                                SI::ISO639LanguageDescriptor *ld = (SI::ISO639LanguageDescriptor *)d;
                                strn0cpy(lang, I18nNormalizeLanguageCode(ld->languageCode), MAXLANGCODE1);
                                }
                                break;
                           default: ;
                           }
                        delete d;
                        }
                     if (IsAc3) {
                        if (NumDpids < MAXDPIDS) {
                           Dpids[NumDpids] = esPid;
                           Dtypes[NumDpids] = SI::AC3DescriptorTag;
                           strn0cpy(DLangs[NumDpids], lang, MAXLANGCODE1);
                           NumDpids++;
                           }
                        ProcessCaDescriptors = true;
                        }
                     }
                     break;
             default: ;//printf("PID: %5d %5d %2d %3d %3d\n", pmt.getServiceId(), stream.getPid(), stream.getStreamType(), pmt.getVersionNumber(), Channel->Number());
             }
           }
       cChannel pmtChannel(*Channel);
       pmtChannel.SetPids(Vpid, Ppid, Vtype, Apids, Atypes, ALangs, Dpids, Dtypes, DLangs, Spids, SLangs, Tpid);
       pmtChannel.SetSubtitlingDescriptors(SubtitlingTypes, CompositionPageIds, AncillaryPageIds);
       m_Streamer->SetTpid(Tpid);
       cPatPmtGenerator patPmtGenerator(&pmtChannel);
       m_Streamer->m_bufferLock.Lock();
       m_Streamer->Put(patPmtGenerator.GetPat(), TS_SIZE);
       int Index = 0;
       while (uchar *pmt = patPmtGenerator.GetPmt(Index))
         m_Streamer->Put(pmt, TS_SIZE);
       m_Streamer->m_bufferLock.Unlock();
       }
  }