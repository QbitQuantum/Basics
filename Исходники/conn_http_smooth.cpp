  /// Main function for Connector_HTTP_Dynamic
  int Connector_HTTP_Dynamic(Socket::Connection conn){
    std::deque<std::string> FlashBuf;
    std::vector<int> Timestamps;
    int FlashBufSize = 0;
    long long int FlashBufTime = 0;

    DTSC::Stream Strm; //Incoming stream buffer.
    HTTP::Parser HTTP_R, HTTP_S; //HTTP Receiver en HTTP Sender.

    bool ready4data = false; //Set to true when streaming is to begin.
    bool pending_manifest = false;
    bool receive_marks = false; //when set to true, this stream will ignore keyframes and instead use pause marks
    bool inited = false;
    Socket::Connection ss( -1);
    std::string streamname;
    std::string recBuffer = "";

    bool wantsVideo = false;
    bool wantsAudio = false;

    std::string Quality;
    int Segment = -1;
    long long int ReqFragment = -1;
    int temp;
    std::string tempStr;
    int Flash_RequestPending = 0;
    unsigned int lastStats = 0;
    conn.setBlocking(false); //do not block on conn.spool() when no data is available

    while (conn.connected()){
      if (conn.spool() || conn.Received().size()){
        //make sure it ends in a \n
        if ( *(conn.Received().get().rbegin()) != '\n'){
          std::string tmp = conn.Received().get();
          conn.Received().get().clear();
          if (conn.Received().size()){
            conn.Received().get().insert(0, tmp);
          }else{
            conn.Received().append(tmp);
          }
        }
        if (HTTP_R.Read(conn.Received().get())){
#if DEBUG >= 4
          std::cout << "Received request: " << HTTP_R.getUrl() << std::endl;
#endif
          conn.setHost(HTTP_R.GetHeader("X-Origin"));
          if (HTTP_R.url.find("Manifest") == std::string::npos){
            streamname = HTTP_R.url.substr(8, HTTP_R.url.find("/", 8) - 12);
            if ( !ss){
              ss = Util::Stream::getStream(streamname);
              if ( !ss.connected()){
#if DEBUG >= 1
                fprintf(stderr, "Could not connect to server!\n");
#endif
                ss.close();
                HTTP_S.Clean();
                HTTP_S.SetBody("No such stream " + streamname + " is available on the system. Please try again.\n");
                conn.SendNow(HTTP_S.BuildResponse("404", "Not found"));
                ready4data = false;
                continue;
              }
              ss.setBlocking(false);
              inited = true;
            }
            Quality = HTTP_R.url.substr(HTTP_R.url.find("/Q(", 8) + 3);
            Quality = Quality.substr(0, Quality.find(")"));
            tempStr = HTTP_R.url.substr(HTTP_R.url.find(")/") + 2);
            wantsAudio = false;
            wantsVideo = false;
            if (tempStr[0] == 'A'){
              wantsAudio = true;
            }
            if (tempStr[0] == 'V'){
              wantsVideo = true;
            }
            tempStr = tempStr.substr(tempStr.find("(") + 1);
            ReqFragment = atoll(tempStr.substr(0, tempStr.find(")")).c_str());
#if DEBUG >= 4
            printf("Quality: %s, Frag %d\n", Quality.c_str(), (ReqFragment / 10000));
#endif
            std::stringstream sstream;
            sstream << "s " << (ReqFragment / 10000) << "\no \n";
            ss.SendNow(sstream.str().c_str());
            Flash_RequestPending++;
          }else{
            streamname = HTTP_R.url.substr(8, HTTP_R.url.find("/", 8) - 12);
            if ( !Strm.metadata.isNull()){
              HTTP_S.Clean();
              HTTP_S.SetHeader("Content-Type", "text/xml");
              HTTP_S.SetHeader("Cache-Control", "no-cache");
              if (Strm.metadata.isMember("length")){
                receive_marks = true;
              }
              std::string manifest = BuildManifest(streamname, Strm.metadata);
              HTTP_S.SetBody(manifest);
              conn.SendNow(HTTP_S.BuildResponse("200", "OK"));
#if DEBUG >= 3
              printf("Sent manifest\n");
#endif
              pending_manifest = false;
            }else{
              pending_manifest = true;
            }
          }
          ready4data = true;
          HTTP_R.Clean(); //clean for any possible next requests
        }
      }else{
        if (Flash_RequestPending){
          usleep(1000); //sleep 1ms
        }else{
          usleep(10000); //sleep 10ms
        }
      }
      if (ready4data){
        if ( !inited){
          //we are ready, connect the socket!
          ss = Util::Stream::getStream(streamname);
          if ( !ss.connected()){
#if DEBUG >= 1
            fprintf(stderr, "Could not connect to server!\n");
#endif
            ss.close();
            HTTP_S.Clean();
            HTTP_S.SetBody("No such stream " + streamname + " is available on the system. Please try again.\n");
            conn.SendNow(HTTP_S.BuildResponse("404", "Not found"));
            ready4data = false;
            continue;
          }
          ss.setBlocking(false);
#if DEBUG >= 3
          fprintf(stderr, "Everything connected, starting to send video data...\n");
#endif
          inited = true;
        }
        unsigned int now = Util::epoch();
        if (now != lastStats){
          lastStats = now;
          ss.SendNow(conn.getStats("HTTP_Smooth").c_str());
        }
        if (ss.spool()){
          while (Strm.parsePacket(ss.Received())){
            if (Strm.getPacket(0).isMember("time")){
              if ( !Strm.metadata.isMember("firsttime")){
                Strm.metadata["firsttime"] = Strm.getPacket(0)["time"];
              }else{
                if ( !Strm.metadata.isMember("length") || Strm.metadata["length"].asInt() == 0){
                  Strm.getPacket(0)["time"] = Strm.getPacket(0)["time"].asInt() - Strm.metadata["firsttime"].asInt();
                }
              }
              Strm.metadata["lasttime"] = Strm.getPacket(0)["time"];
            }
            if (pending_manifest){
              HTTP_S.Clean();
              HTTP_S.SetHeader("Content-Type", "text/xml");
              HTTP_S.SetHeader("Cache-Control", "no-cache");
              if (Strm.metadata.isMember("length")){
                receive_marks = true;
              }
              std::string manifest = BuildManifest(streamname, Strm.metadata);
              HTTP_S.SetBody(manifest);
              conn.SendNow(HTTP_S.BuildResponse("200", "OK"));
#if DEBUG >= 3
              printf("Sent manifest\n");
#endif
              pending_manifest = false;
            }
            if ( !receive_marks && Strm.metadata.isMember("length")){
              receive_marks = true;
            }
            if (Strm.lastType() == DTSC::PAUSEMARK){
              Timestamps.push_back(Strm.getPacket(0)["time"].asInt());
            }
            if ((Strm.getPacket(0).isMember("keyframe") && !receive_marks) || Strm.lastType() == DTSC::PAUSEMARK){
#if DEBUG >= 4
              fprintf(stderr, "Received a %s fragment of %i bytes.\n", Strm.getPacket(0)["datatype"].asString().c_str(), FlashBufSize);
#endif
              if (Flash_RequestPending > 0 && FlashBufSize){
#if DEBUG >= 3
                fprintf(stderr, "Sending a fragment...");
#endif
                //static std::string btstrp;
                //btstrp = GenerateBootstrap(streamname, Strm.metadata, ReqFragment, FlashBufTime, Strm.getPacket(0)["time"]);
                HTTP_S.Clean();
                HTTP_S.SetHeader("Content-Type", "video/mp4");
                HTTP_S.SetBody("");

                int myDuration;

                MP4::MFHD mfhd_box;
                for (int i = 0; i < Strm.metadata["keytime"].size(); i++){
                  if (Strm.metadata["keytime"][i].asInt() >= (ReqFragment / 10000)){
                    mfhd_box.setSequenceNumber(i + 1);
                    if (i != Strm.metadata["keytime"].size()){
                      myDuration = Strm.metadata["keytime"][i + 1].asInt() - Strm.metadata["keytime"][i].asInt();
                    }else{
                      myDuration = Strm.metadata["lastms"].asInt() - Strm.metadata["keytime"][i].asInt();
                    }
                    myDuration = myDuration * 10000;
                    break;
                  }
                }

                MP4::TFHD tfhd_box;
                tfhd_box.setFlags(MP4::tfhdSampleFlag);
                tfhd_box.setTrackID(1);
                tfhd_box.setDefaultSampleFlags(0x000000C0 | MP4::noIPicture | MP4::noDisposable | MP4::noKeySample);

                MP4::TRUN trun_box;
                //maybe reinsert dataOffset
                trun_box.setFlags(MP4::trundataOffset | MP4::trunfirstSampleFlags | MP4::trunsampleDuration | MP4::trunsampleSize);
                trun_box.setDataOffset(42);
                trun_box.setFirstSampleFlags(0x00000040 | MP4::isIPicture | MP4::noDisposable | MP4::isKeySample);
                for (int i = 0; i < FlashBuf.size(); i++){
                  MP4::trunSampleInformation trunSample;
                  trunSample.sampleSize = FlashBuf[i].size();
                  //trunSample.sampleDuration = (Timestamps[i+1]-Timestamps[i]) * 10000;
                  trunSample.sampleDuration = (((double)myDuration / FlashBuf.size()) * i) - (((double)myDuration / FlashBuf.size()) * (i - 1));
                  trun_box.setSampleInformation(trunSample, i);
                }
                MP4::SDTP sdtp_box;
                sdtp_box.setVersion(0);
                sdtp_box.setValue(0x24, 4);
                for (int i = 1; i < FlashBuf.size(); i++){
                  sdtp_box.setValue(0x14, 4 + i);
                }

                MP4::TRAF traf_box;
                traf_box.setContent(tfhd_box, 0);
                traf_box.setContent(trun_box, 1);
                traf_box.setContent(sdtp_box, 2);

                MP4::MOOF moof_box;
                moof_box.setContent(mfhd_box, 0);
                moof_box.setContent(traf_box, 1);

                //setting tha offsets!
                trun_box.setDataOffset(moof_box.boxedSize() + 8);
                traf_box.setContent(trun_box, 1);
                moof_box.setContent(traf_box, 1);

                //std::cerr << "\t[encoded] = " << ((MP4::TRUN&)(((MP4::TRAF&)(moof_box.getContent(1))).getContent(1))).getDataOffset() << std::endl;

                HTTP_S.SetHeader("Content-Length", FlashBufSize + 8 + moof_box.boxedSize()); //32+33+btstrp.size());
                conn.SendNow(HTTP_S.BuildResponse("200", "OK"));

                conn.SendNow(moof_box.asBox(), moof_box.boxedSize());

                unsigned long size = htonl(FlashBufSize+8);
                conn.SendNow((char*) &size, 4);
                conn.SendNow("mdat", 4);
                while (FlashBuf.size() > 0){
                  conn.SendNow(FlashBuf.front());
                  FlashBuf.pop_front();
                }
                Flash_RequestPending--;
#if DEBUG >= 3
                fprintf(stderr, "Done\n");
#endif
              }
              FlashBuf.clear();
              FlashBufSize = 0;
            }
            if ((wantsAudio && Strm.lastType() == DTSC::AUDIO) || (wantsVideo && Strm.lastType() == DTSC::VIDEO)){
              FlashBuf.push_back(Strm.lastData());
              FlashBufSize += Strm.lastData().size();
              Timestamps.push_back(Strm.getPacket(0)["time"].asInt());
            }
          }
          if (pending_manifest && !Strm.metadata.isNull()){
            HTTP_S.Clean();
            HTTP_S.SetHeader("Content-Type", "text/xml");
            HTTP_S.SetHeader("Cache-Control", "no-cache");
            if (Strm.metadata.isMember("length")){
              receive_marks = true;
            }
            std::string manifest = BuildManifest(streamname, Strm.metadata);
            HTTP_S.SetBody(manifest);
            conn.SendNow(HTTP_S.BuildResponse("200", "OK"));
#if DEBUG >= 3
            printf("Sent manifest\n");
#endif
            pending_manifest = false;
          }
        }
        if ( !ss.connected()){
          break;
        }
      }
    }
    conn.close();
    ss.SendNow(conn.getStats("HTTP_Smooth").c_str());
    ss.close();
    return 0;
  } //Connector_HTTP_Smooth main function