void FileTransferSocketThread::execute()
{
    if(info.hostType == eServer)
    {
        ServerSocket serverSocket;
        serverSocket.bind(this->info.serverPort);
        serverSocket.listen(1);
        Socket *clientSocket = serverSocket.accept();

        char data[513]="";
        memset(data, 0, 256);

        clientSocket->receive(data,256, true);
        if(*data == SEND_FILE)
        {
            FileInfo file;

            memcpy(&file, data+1, sizeof(file));

            *data=ACK;
            clientSocket->send(data,256);

            Checksum checksum;
            checksum.addFile(file.fileName);
            file.filecrc  = checksum.getSum();

            ifstream infile(file.fileName.c_str(), ios::in | ios::binary | ios::ate);
            if(infile.is_open() == true)
            {
                file.filesize = infile.tellg();
                infile.seekg (0, ios::beg);

                memset(data, 0, 256);
                *data=SEND_FILE;
                memcpy(data+1,&file,sizeof(file));

                clientSocket->send(data,256);
                clientSocket->receive(data,256, true);
                if(*data != ACK) {
                   //transfer error
                }

                int remain=file.filesize % 512 ;
                int packs=(file.filesize-remain)/512;

                while(packs--)
                {
                    infile.read(data,512);
                    //if(!ReadFile(file,data,512,&read,NULL))
                    //    ; //read error
                    //if(written!=pack)
                    //    ; //read error
                    clientSocket->send(data,512);
                    clientSocket->receive(data,256, true);
                    if(*data!=ACK) {
                           //transfer error
                    }
                }

                infile.read(data,remain);
                //if(!ReadFile(file,data,remain,&read,NULL))
                //   ; //read error
                //if(written!=pack)
                //   ; //read error

                clientSocket->send(data,remain);
                clientSocket->receive(data,256, true);
                if(*data!=ACK) {
                   //transfer error
                }

                infile.close();
            }
        }

        delete clientSocket;
    }
    else
    {
        Ip ip(this->info.serverIP);
        ClientSocket clientSocket;
        clientSocket.connect(this->info.serverIP, this->info.serverPort);

        if(clientSocket.isConnected() == true)
        {
            FileInfo file;
            file.fileName = this->info.fileName;
            //file.filesize =
            //file.filecrc  = this->info.

            string path = extractDirectoryPathFromFile(file.fileName);
            createDirectoryPaths(path);
            ofstream outFile(file.fileName.c_str(), ios_base::binary | ios_base::out);
            if(outFile.is_open() == true)
            {
                char data[513]="";
                memset(data, 0, 256);
                *data=SEND_FILE;
                memcpy(data+1,&file,sizeof(file));

                clientSocket.send(data,256);
                clientSocket.receive(data,256, true);
                if(*data!=ACK) {
                  //transfer error
                }

                clientSocket.receive(data,256,true);
                if(*data == SEND_FILE)
                {
                   memcpy(&file, data+1, sizeof(file));
                   *data=ACK;
                   clientSocket.send(data,256);

                   int remain = file.filesize % 512 ;
                   int packs  = (file.filesize-remain) / 512;

                   while(packs--)
                   {
                      clientSocket.receive(data,512,true);

                      outFile.write(data, 512);
                      if(outFile.bad())
                      {
                          //int ii = 0;
                      }
                      //if(!WriteFile(file,data,512,&written,NULL))
                      //   ; //write error
                      //if(written != pack)
                      //   ; //write error
                      *data=ACK;
                      clientSocket.send(data,256);
                    }
                    clientSocket.receive(data,remain,true);

                    outFile.write(data, remain);
                    if(outFile.bad())
                    {
                        //int ii = 0;
                    }

                    //if(!WriteFile(file,data,remain,&written,NULL))
                    //    ; //write error
                    //if(written!=pack)
                    //    ; //write error
                    *data=ACK;
                    clientSocket.send(data,256);

                    Checksum checksum;
                    checksum.addFile(file.fileName);
                    uint32 crc = checksum.getSum();
                    if(file.filecrc != crc)
                    {
                        //int ii = 0;
                    }

                    //if(calc_crc(file)!=info.crc)
                    //   ; //transfeer error
                }

                outFile.close();
            }
        }
    }
}