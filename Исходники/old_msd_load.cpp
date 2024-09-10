int GetHeaderAndBodyNormalHttpSession(std::string &url, std::string type)
{
    try
    {
      //printf("Complete URL (%s)\n", url.c_str());
      URI uri(url);
      HTTPClientSession session(uri.getHost(), uri.getPort());
      HTTPRequest request(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), "HTTP/1.1");
     // request.set("user-agent", "Poco HTTPClientSession");
      //request.add("UDN-securelink", "true");

      //request.add("X-client-token", "innermatch");
      //request.add("X-seq-match", "seqtest1");
      //Set session timeout to 10 minutes
      //session.setTimeout(Poco::Timespan(1200L,0L));
      session.sendRequest(request);
      __sync_add_and_fetch(&(requestSent),1);
#if 0
      Poco::Net::StreamSocket &str = session.socket();
      str.setReceiveTimeout(Poco::Timespan(1200L,0L));
#endif
      HTTPResponse response;
      std::istream& rs = session.receiveResponse(response);
      //printing response headers
#if 0
      printf("\n\n\n");
      cout << "RESPONSE HEADERS:" <<endl;
      cout << response.getReason() <<endl;
      cout << response.getStatus() <<endl;
      cout << response.getVersion() <<endl;
#endif

      if(response.getStatus() != 200)
      {
        printf("status is not 200 -- for(%s--%d) \n", url.c_str(), response.getStatus());
        if(response.getStatus() == 400)
        {
        __sync_add_and_fetch(&(mo_400_response),1);
        }

        if(response.getStatus() == 500)
        {
        __sync_add_and_fetch(&(mo_500_response),1);
        }

        if(response.getStatus() == 503)
        {
        __sync_add_and_fetch(&(mo_503_response),1);
        }

      }
      else
      {
        __sync_add_and_fetch(&(mo_200_response),1);
      }

      string name;
      string lmtheader;
      bool isLMTHeaderPresent = false;
      string value;
      NameValueCollection::ConstIterator i = response.begin();
      while(i!=response.end())
      {
        name=i->first;
        value=i->second;
        if(name.compare("Last-Modified") == 0)
        {
          isLMTHeaderPresent = true;
          //printf("Last Modified header:%s \n", value.c_str());
        }

        //cout << name << "=" << value << endl << flush;
        ++i;
      }
      if(!isLMTHeaderPresent)
      {
       __sync_add_and_fetch(&(noLMTHeaders),1);
        printf("Last Modified header is not present (%s)\n", url.c_str());
      }
#if 0
      int ret;
      remove("/home/MSD/POCO_LEARNING/poco_examples/pocossl/examples/vipin.mp4");
      remove("/opt/universalcache/upload/.cache/*");
      std::ofstream out("/home/MSD/POCO_LEARNING/poco_examples/pocossl/examples/vipin.mp4", std::ofstream::binary|std::ofstream::app);
      //flush any previous ontent
      //out.flush();
      unsigned char ciphertext[INTERNAL_RSP_READ_BUFFER];
      int totallength = 0;
      while(!rs.eof())
      {
        rs.read ((char *)ciphertext, INTERNAL_RSP_READ_BUFFER);
        int ciphertext_len = rs.gcount();
        totallength +=ciphertext_len;
        out.write ((char *)ciphertext,(size_t)ciphertext_len);
      }
      //printf("RECEIVED --------(%d) \n",totallength);
      out.close();
#endif
    }
    catch (Exception& ex)
    {
       __sync_add_and_fetch(&(errors),1);
      std::cout <<"ERROR(%s-%s):----"<<type <<"--" <<url <<"---" << ex.displayText() << std::endl;
      return 1;
    }
}