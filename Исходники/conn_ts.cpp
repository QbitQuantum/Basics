  ///\brief Main function for the TS Connector
  ///\param conn A socket describing the connection the client.
  ///\param streamName The stream to connect to.
  ///\return The exit code of the connector.
  int tsConnector(Socket::Connection conn, std::string streamName, std::string trackIDs){
    std::string ToPack;
    TS::Packet PackData;
    std::string DTMIData;
    int PacketNumber = 0;
    long long unsigned int TimeStamp = 0;
    int ThisNaluSize;
    char VideoCounter = 0;
    char AudioCounter = 0;
    bool WritePesHeader;
    bool IsKeyFrame;
    bool FirstKeyFrame = true;
    bool FirstIDRInKeyFrame;
    MP4::AVCC avccbox;
    bool haveAvcc = false;

    DTSC::Stream Strm;
    bool inited = false;
    Socket::Connection ss;

    while (conn.connected()){
      if ( !inited){
        ss = Util::Stream::getStream(streamName);
        if ( !ss.connected()){
  #if DEBUG >= 1
          fprintf(stderr, "Could not connect to server!\n");
  #endif
          conn.close();
          break;
        }

        if(trackIDs == ""){
          // no track ids given? Find the first video and first audio track (if available) and use those!
          int videoID = -1;
          int audioID = -1;

          Strm.waitForMeta(ss);
          
          if (Strm.metadata.isMember("tracks")){

            for (JSON::ObjIter trackIt = Strm.metadata["tracks"].ObjBegin(); trackIt != Strm.metadata["tracks"].ObjEnd(); trackIt++){

              if (audioID == -1 && trackIt->second["type"].asString() == "audio"){
                audioID = trackIt->second["trackid"].asInt();
                if( trackIDs != ""){
                  trackIDs += " " + trackIt->second["trackid"].asString();
                }else{
                    trackIDs = trackIt->second["trackid"].asString();
                }
              }

              if (videoID == -1 && trackIt->second["type"].asString() == "video"){
                videoID = trackIt->second["trackid"].asInt();
                if( trackIDs != ""){
                  trackIDs += " " + trackIt->second["trackid"].asString();
                }else{
                  trackIDs = trackIt->second["trackid"].asString();
                }
              }

            }	// for iterator
          } // if isMember("tracks")
        } // if trackIDs == ""

        std::string cmd = "t " + trackIDs + "\ns 0\np\n";
        ss.SendNow( cmd );
        inited = true;
      }
      if (ss.spool()){
        while (Strm.parsePacket(ss.Received())){

          std::stringstream TSBuf;
          Socket::Buffer ToPack;
          //write PAT and PMT TS packets
          if (PacketNumber == 0){
            PackData.DefaultPAT();
            TSBuf.write(PackData.ToString(), 188);
            PackData.DefaultPMT();
            TSBuf.write(PackData.ToString(), 188);
            PacketNumber += 2;
          }

          int PIDno = 0;
          char * ContCounter = 0;
          if (Strm.lastType() == DTSC::VIDEO){
		      if ( !haveAvcc){
		          avccbox.setPayload(Strm.getTrackById(Strm.getPacket()["trackid"].asInt())["init"].asString());
		        haveAvcc = true;
		      }

            IsKeyFrame = Strm.getPacket().isMember("keyframe");
            if (IsKeyFrame){
              TimeStamp = (Strm.getPacket()["time"].asInt() * 27000);
            }
            ToPack.append(avccbox.asAnnexB());
                while (Strm.lastData().size() > 4){
              ThisNaluSize = (Strm.lastData()[0] << 24) + (Strm.lastData()[1] << 16) + (Strm.lastData()[2] << 8) + Strm.lastData()[3];
              Strm.lastData().replace(0, 4, TS::NalHeader, 4);
              if (ThisNaluSize + 4 == Strm.lastData().size()){
                ToPack.append(Strm.lastData());
                break;
              }else{
                ToPack.append(Strm.lastData().c_str(), ThisNaluSize + 4);
                Strm.lastData().erase(0, ThisNaluSize + 4);
              }
            }
            ToPack.prepend(TS::Packet::getPESVideoLeadIn(0ul, Strm.getPacket()["time"].asInt() * 90));
            PIDno = 0x100 - 1 + Strm.getPacket()["trackid"].asInt();
            ContCounter = &VideoCounter;
          }else if (Strm.lastType() == DTSC::AUDIO){
                ToPack.append(TS::GetAudioHeader(Strm.lastData().size(), Strm.getTrackById(Strm.getPacket()["trackid"].asInt())["init"].asString()));
            ToPack.append(Strm.lastData());
            ToPack.prepend(TS::Packet::getPESAudioLeadIn(ToPack.bytes(1073741824ul), Strm.getPacket()["time"].asInt() * 90));
            PIDno = 0x100 - 1 + Strm.getPacket()["trackid"].asInt();
            ContCounter = &AudioCounter;
                IsKeyFrame = false;
          }

          //initial packet
          PackData.Clear();
          PackData.PID(PIDno);
          PackData.ContinuityCounter(( *ContCounter)++);
          PackData.UnitStart(1);
          if (IsKeyFrame){
            PackData.RandomAccess(1);
            PackData.PCR(TimeStamp);
          }
          unsigned int toSend = PackData.AddStuffing(ToPack.bytes(184));
          std::string gonnaSend = ToPack.remove(toSend);
          PackData.FillFree(gonnaSend);
          TSBuf.write(PackData.ToString(), 188);
          PacketNumber++;

          //rest of packets
          while (ToPack.size()){
            PackData.Clear();
            PackData.PID(PIDno);
            PackData.ContinuityCounter(( *ContCounter)++);
            toSend = PackData.AddStuffing(ToPack.bytes(184));
            gonnaSend = ToPack.remove(toSend);
            PackData.FillFree(gonnaSend);
            TSBuf.write(PackData.ToString(), 188);
            PacketNumber++;
          }

          TSBuf.flush();
          if (TSBuf.str().size()){
            conn.SendNow(TSBuf.str().c_str(), TSBuf.str().size());
            TSBuf.str("");
          }
          TSBuf.str("");
          PacketNumber = 0;
        }
      }else{
        Util::sleep(1000);
        conn.spool();
      }
    }
    return 0;
  }