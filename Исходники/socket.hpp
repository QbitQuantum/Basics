      void _accept()
      {
         #if _WIN32
            int client_length = sizeof(sockaddr_in);
         #else
            socklen_t client_length = sizeof(sockaddr_in);
         #endif

         _m_accepted_fd = ::accept(_m_socket_fd, (sockaddr *)&_m_client_address, &client_length);

         // -1 on failure
         if (_m_accepted_fd < 0)
         {
            std::string err = "Unable to connect to socket - error number: ";
            
            err += errno;
            
            err += " -- ";
            
            #if _WIN32
               char buffer[256];

               err += strerror_s(buffer, 256, errno);
            #else
               err += strerror(errno);
            #endif
            
            throw std::runtime_error(err);
         }
      }