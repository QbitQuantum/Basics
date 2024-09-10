 TempFile::TempFile() {
     if (tmpnam_s(m_buffer)) {
         throw std::runtime_error("Could not get a temp filename");
     }
     if (fopen_s(&m_file, m_buffer, "w")) {
         char buffer[100];
         if (strerror_s(buffer, errno)) {
             throw std::runtime_error("Could not translate errno to string");
         }
         throw std::runtime_error("Could not open the temp file: " + std::string(m_buffer) + buffer);
     }
 }