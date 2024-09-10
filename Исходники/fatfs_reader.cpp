    void sendFile(const char *filename) {

      scoped_ptr<File> file;
      char buffer[256];

      // open the file - we own the file pointer that comes back upon success and
      // we must remember to delete it when we're finished

      if(!_fs->openFile(filename,file.address()))
        error();

      // declare a file reader to read lines from the file and also a
      // UsartPollingOutputStream for convenient output to the USART

      FileReader reader(*file);
      UsartPollingOutputStream output(*_usart);

      while(reader.available()) {

        // read the next line and send to the USART

        if(!reader.readLine(buffer,sizeof(buffer)))
          error();

        output << buffer << "\r\n";
      }
    }