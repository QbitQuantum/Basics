/*--------------------------------------------------------------------------------*/
bool XMLADMData::ReadChnaFromFile(const std::string& filename, bool finalise)
{
  EnhancedFile fp;
  bool success = false;

  if (fp.fopen(filename.c_str()))
  {
    char buffer[1024];
    int l;

    success = true;

    while (success && ((l = fp.readline(buffer, sizeof(buffer) - 1)) != EOF))
    {
      if (l > 0)
      {
        std::vector<std::string> words;

        SplitString(std::string(buffer), words);

        if (words.size() == 4)
        {
          uint_t tracknum;

          if (Evaluate(words[0], tracknum))
          {
            if (tracknum)
            {
              const std::string& trackuid    = words[1];
              const std::string& trackformat = words[2];
              const std::string& packformat  = words[3];
              ADMAudioTrack *track;
              std::string id;

              if ((track = dynamic_cast<ADMAudioTrack *>(Create(ADMAudioTrack::Type, trackuid, ""))) != NULL)
              {
                XMLValue tvalue, pvalue;

                track->SetTrackNum(tracknum - 1);

                tvalue.name = ADMAudioTrackFormat::Reference;
                tvalue.value = trackformat;
                track->AddValue(tvalue);

                pvalue.name = ADMAudioPackFormat::Reference;
                pvalue.value = packformat;
                track->AddValue(pvalue);

                track->SetValues();

                BBCDEBUG2(("Track %u: Index %u UID '%s' TrackFormatRef '%s' PackFormatRef '%s'",
                        (uint_t)tracklist.size(),
                        track->GetTrackNum() + 1,
                        track->GetID().c_str(),
                        tvalue.value.c_str(),
                        pvalue.value.c_str()));
              }
              else
              {
                BBCERROR("Failed to create AudioTrack for UID %u", tracknum);
                success = false;
              }
            }
          }
          else
          {
            BBCERROR("CHNA line '%s' word 1 ('%s') should be a track number", buffer, words[0].c_str());
            success = false;
          }
        }
        else
        {
          BBCERROR("CHNA line '%s' requires 4 words", buffer);
          success = false;
        }
      }
    }

    fp.fclose();

    if (success && finalise) Finalise();
  }

  return success;
}