   void run(int argc, char* argv[], char* env[])
      {
      U_TRACE(5, "Application::run(%d,%p,%p)", argc, argv, env)

      UApplication::run(argc, argv, env);

      // manage options

      time_t queue_time = 0;
      UString outpath, result;
      bool include = false, bstdin = false;

      if (UApplication::isOptions())
         {
         cfg_str    =  opt['c'];
         upload     =  opt['u'];
         bstdin     = (opt['s'] == U_STRING_FROM_CONSTANT("1"));
         include    = (opt['i'] == U_STRING_FROM_CONSTANT("1"));
         outpath    =  opt['o'];
         queue_time =  opt['q'].strtol();
         }

      // manage arg operation

      UString url(argv[optind++]);

      // manage file configuration

      if (cfg_str.empty()) cfg_str = U_STRING_FROM_CONSTANT(U_SYSCONFDIR "/uclient.cfg");

      cfg.UFile::setPath(cfg_str);

      // ----------------------------------------------------------------------------------------------------------------------------------
      // uclient - configuration parameters
      // ----------------------------------------------------------------------------------------------------------------------------------
      // ENABLE_IPV6  flag to indicate use of ipv6
      // SERVER       host name or ip address for server
      // PORT         port number for the server
      //
      // PID_FILE     write pid on file indicated
      // RES_TIMEOUT  timeout for response from server
      //
      // LOG_FILE     locations   for file log
      //
      // CERT_FILE    certificate of client
      // KEY_FILE     private key of client
      // PASSWORD     password for private key of client
      // CA_FILE      locations of trusted CA certificates used in the verification
      // CA_PATH      locations of trusted CA certificates used in the verification
      // VERIFY_MODE  mode of verification (SSL_VERIFY_NONE=0, SSL_VERIFY_PEER=1, SSL_VERIFY_FAIL_IF_NO_PEER_CERT=2, SSL_VERIFY_CLIENT_ONCE=4)
      // CIPHER_SUITE cipher suite model (Intermediate=0, Modern=1, Old=2)
      //
      // FOLLOW_REDIRECTS if yes manage to automatically follow redirects from server
      // USER             if     manage to follow redirects, in response to a HTTP_UNAUTHORISED response from the HTTP server: user
      // PASSWORD_AUTH    if     manage to follow redirects, in response to a HTTP_UNAUTHORISED response from the HTTP server: password
      // ----------------------------------------------------------------------------------------------------------------------------------

      client = new UHttpClient<USSLSocket>(&cfg);

      user             = cfg[*UString::str_USER];
      password         = cfg[U_STRING_FROM_CONSTANT("PASSWORD_AUTH")];
      follow_redirects = cfg.readBoolean(U_STRING_FROM_CONSTANT("FOLLOW_REDIRECTS"));

      client->setFollowRedirects(follow_redirects);
      client->getResponseHeader()->setIgnoreCase(true);
      client->setRequestPasswordAuthentication(user, password);

      UApplication::exit_value = 1;

loop: if (upload)
         {
         UFile file(upload);

         if (client->upload(url, file)) UApplication::exit_value = 0;
         }
      else if (client->connectServer(url))
         {
         bool ok;

         if (bstdin == false) ok = client->sendRequest();
         else
            {
            UString req(U_CAPACITY);

            UServices::readEOF(STDIN_FILENO, req);

            if (req.empty()) U_ERROR("cannot read data from <stdin>");

            ok = client->sendRequest(req);
            }

         if (ok) UApplication::exit_value = 0;
         }

      result = (include ? client->getResponse()
                        : client->getContent());

      if (result)
         {
#     ifdef USE_LIBZ
         if (UStringExt::isGzip(result)) result = UStringExt::gunzip(result);
#     endif

         if (outpath) UFile::writeTo(outpath, result);
         else         (void) write(1, U_STRING_TO_PARAM(result));
         }

      if (queue_time)
         {
         UTimeVal to_sleep(queue_time / 10L);

         U_INTERNAL_ASSERT_EQUALS(UClient_Base::queue_dir, 0)

         if (result.empty() &&
             UApplication::exit_value == 1)
            {
            to_sleep.nanosleep();

            goto loop;
            }

         UFile file;
         char mask[100U];
         uint32_t i, n, pos;
         UVector<UString> vec(64);
         UString req, name, location(U_CAPACITY);

         uint32_t mask_len = u__snprintf(mask, sizeof(mask), "%.*s.*", U_STRING_TO_TRACE(client->UClient_Base::host_port));

         to_sleep.setSecond(to_sleep.getSecond() * 10L);

         U_MESSAGE("monitoring directory %.*S every %u sec - file mask: %.*S",
                        U_STRING_TO_TRACE(*UString::str_CLIENT_QUEUE_DIR), to_sleep.getSecond(), mask_len, mask);

#     ifdef USE_LIBSSL
         client->UClient_Base::setActive(false);
#     endif

         UServer_Base::timeoutMS = client->UClient_Base::timeoutMS;

         UDirWalk dirwalk(*UString::str_CLIENT_QUEUE_DIR, mask, mask_len);

         while (true)
            {
            for (i = 0, n = dirwalk.walk(vec, U_ALPHABETIC_SORT); i < n; ++i) // NB: vec is sorted by string compare...
               {
               file.setPath(vec[i]);

               // -----------------------------------------------------------------------------
               // NB: sometime there is a strange behaviour on openWRT (overlayfs) after unlink
               // -----------------------------------------------------------------------------
               // wifi-aaa.comune.fi.it.090513_132007_139 -> (overlay-whiteout)
               // -----------------------------------------------------------------------------

               req = file.getContent();

               if (req)
                  {
                  name = file.getName();
                  pos  = name.find_last_of('.');

                  U_INTERNAL_ASSERT_DIFFERS(pos, U_NOT_FOUND)

                  location.snprintf("http://%.*s", pos, name.data());

                  (void) location.shrink();

                  if (client->connectServer(location) == false ||
                      client->sendRequest(req)        == false)
                     {
                     break;
                     }
                  }

               (void) file._unlink();
               }

            vec.clear();

            if (client->isOpen()) client->close();

            to_sleep.nanosleep();
            }
         }

      client->closeLog();
      }