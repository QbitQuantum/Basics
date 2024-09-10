void RunTestChatHistory( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
//void     RunTestChatHistory( ClientNetworkWrapper& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestChatHistory " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   int standardTab = 12;
   ListChatHistoryInstructions();

   

   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }

      if( triedLogin == false && 
         network.IsConnected() == true &&
         network.IsLoggedIn() == false
         )
      {
         network.RequestLogin( userEmail, userPassword, "En" );
         triedLogin = true;

         cout << "Login attempted for " << userEmail << ", pwd= " << userPassword << endl;
         //exit(0);// aggressive exit
      }

      if( key )
      {
         if( key == 'r' )
         {
            cout << " r- request channel list " << endl;
            network.RequestChatChannelList();
         }
         if( key == 'd' )
         {
            cout << " d- dump chat channel list" << endl;
            int numChannels = network.GetNumChannels();
            if( numChannels == 0 )
            {
               cout << "you don't have any chat channels" << endl;
            }
            else
            {
               for( int i=0; i<numChannels; i++ )
               {
                  ChatChannel channel;
                  network.GetChannel( i, channel );
                  if( channel.channelName.size() != 0 )
                  {
                     cout << "  name: " << channel.channelName << endl;
                     cout << "  uuid: " << channel.uuid << endl << "*******" << endl;
                  }
               }
            }
         }
         if( key == 'c' )
         {
            cout << "Get chat history for channel" << endl;
            int numChannels = network.GetNumChannels();
            if( numChannels == 0 )
            {
               cout << "you don't have any chat channels" << endl;
            }
            else
            {
               ChatChannel channel;
               int channelIndex = rand() % numChannels;
               network.GetChannel( channelIndex, channel );
               cout << "Requesting channel name: " << channel.channelName << endl;
               cout << "                   uuid: " << channel.uuid << endl;
               network.RequestChatChannelHistory( channel.uuid, 20, 0, "2014-04-22" );
            }
         }
         if( key == 'p' )
         {
            string requestedUser = "******";
            if( userEmail == "user3" )
               requestedUser = "******";
            network.RequestChatP2PHistory( requestedUser, 20, 0, "2014-04-22" );
         }
       /*  if( key == 'u' )
         {
            //cout << "Request history for channel: " << "Chu-Chu-Chu, 67196c651e06feb0, 3786" << endl;
            cout << " * Chu-Chu-Cho                 7196c651e06feb0" << endl;
            network.RequestChatChannelHistory( "67196c651e06feb0", 20, 0, "2014-04-22" );

         }*/
         if( key == 'x' )
         {
            cout << " x- request chat history channel: Tri Star( 10 ):      67196c651e06feb0" << endl;
            //cout << " x- request chat history channel: Chu-Chu-Chu:67196c651e06feb0" << endl;
            RequestHistory( network, "67196c651e06feb0", 0 );
         }
         if( key == 'z' )
         {
            cout << " z- request chat history channel: Chu-Chu-Chu( 3786 ): 6d7d9f7e14620dab" << endl;
            RequestHistory( network, "6d7d9f7e14620dab", 0 );
         }
         if( key == 'a' )
         {
            cout << " a- request chat history channel: summonwar_0000237( 52 ): 9eeb850487faf7cf" << endl;
            RequestHistory( network, "9eeb850487faf7cf", 0 );   
         }
         if( key == 'q' )
         {
            cout << " q- request chat history channel: Show me the money( 0 ): 47d473b25ec50179" << endl;
            RequestHistory( network, "9eeb850487faf7cf", 0 );   
         }
         if( key == 'w' )
         {
            cout << " w- request chat history channel: Test 123( 36 ): 6d248e52143b1c87" << endl;
            RequestHistory( network, "6d248e52143b1c87", 20 );  
         }
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: "******" email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListChatHistoryInstructions();
         }
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 100 );
   }


   network.RequestLogout();

   cout << "Logging out .. press any key to exit"  << endl;
   getch();
   network.Exit();
}