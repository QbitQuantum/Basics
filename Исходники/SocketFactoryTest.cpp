        virtual void run(){
            try{
                unsigned char buf[1000];

                ServerSocket server;
                server.bind( "127.0.0.1", SocketFactoryTest::DEFAULT_PORT );

                net::Socket* socket = server.accept();
                server.close();

                socket->setSoLinger( false, 0 );

                synchronized(&mutex)
                {
                    numClients++;
                    mutex.notifyAll();
                }

                while( !done && socket != NULL ){

                    io::InputStream* stream = socket->getInputStream();
                    memset( buf, 0, 1000 );
                    try{
                        if( stream->read( buf, 1000, 0, 1000 ) == -1 ) {
                            done = true;
                            continue;
                        }

                        lastMessage = (char*)buf;

                        if( strcmp( (char*)buf, "reply" ) == 0 ){
                            io::OutputStream* output = socket->getOutputStream();
                            output->write( (unsigned char*)"hello", (int)strlen("hello"), 0, (int)strlen("hello") );
                        }

                    }catch( io::IOException& ex ){
                        done = true;
                    }
                }

                socket->close();
                delete socket;

                numClients--;

                synchronized(&mutex) {
                    mutex.notifyAll();
                }

            }catch( io::IOException& ex ){
                printf("%s\n", ex.getMessage().c_str() );
                CPPUNIT_ASSERT( false );
            }catch( ... ){
                CPPUNIT_ASSERT( false );
            }
        }