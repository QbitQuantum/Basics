void     RunTestAssetsSaveToFile( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccount& account )
{
   cout << "RunTestAssetsSaveToFile " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;

   string targetFile [] = {"allFFs", "multibytes", "ad01" };
   int numFiles = 3;
   int currentFile = 0;

   int standardTab = 12;

   ListAssetSaveToFileInstructions ();
   bool  defaultLogin = false;

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
         
         if( key == 'l' )
         {
            
            if( 
               triedLogin == false && 
               network.IsConnected() == true &&
               network.IsLoggedIn() == false
               )
            {
               cout << " attempting login " << endl;
               network.RequestLogin( userEmail, userPassword, "En" );
               triedLogin = true;

               cout << "Login attempted for " << userEmail << ", pwd= " << userPassword << endl;
               //exit(0);// aggressive exit
            }
            else
            {
               cout << "already logged in" << endl;
            }
         }
         if( key == 'c' )
         {
            cout << "c- request list of categories" << endl;
            network.RequestListOfAssetCategories();
         }

         if( key == 'r' )
         {
            cout << " r- request list of assets per category" << endl;
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               cout << "Category name:" << categoryName << endl;
               network.RequestListOfAssets( categoryName, Platform_ios, "ios" );
            }
            if( categories.size() == 0 )
            {
               cout << "Not enough categories" << endl;
            }
         }
         if( key == 'a' )
         {
            cout << " a- request list of assets" << endl;
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               for( int i=0; i< numInCategory; i++ )
               {
                  AssetInfoExtended asset;
                  
                  network.GetAssetInfo( categoryName, i, asset );
                  cout << "Requesting category 1: " << categoryName << ", asset 3: " << asset.assetName << endl;
                  if( asset.assetName.size() == 0 )
                  {
                     cout << " bad asset " << endl;
                  }
                  else
                  {
                     cout << "Name: " << asset.assetHash << endl;
                     cout << "Product id: " << (int)asset.productId << endl;
                     cout << "Version: " << asset.version << endl;
                     if( asset.IsDataValid() == false )
                     {
                        network.RequestAssetByHash( asset.assetHash );
                     }
                     else
                     {
                        cout << "Already loaded" << endl;
                     }
                  }
               }
            }
            if( categories.size() == 0 )
            {
               cout << "Not enough categories" << endl;
            }
         }
         if( key == 'd' )
         {
            cout << " d- dump list of assets" << endl;
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
               
               for( int i=0; i< numInCategory; i++ )
               {
                  AssetInfoExtended asset;
                  
                  network.GetAssetInfo( categoryName, i, asset );
                  if( asset.assetName.size() == 0 )
                  {
                     cout << " bad asset " << endl;
                  }
                  else
                  {
                     cout << "Name: " << asset.assetName << endl;
                     cout << "hash: " << asset.assetHash << endl;
                     cout << "Product id: " << (int)asset.productId << endl;
                     cout << "Version: " << asset.version << endl;
                  }
               }
            }
            if( categories.size() == 0 )
            {
               cout << "Not enough categories" << endl;
            }
         }

         if( key == 'b' )
         //if( asset.IsDataValid() == false )
         {
            network.RequestAssetByHash( "4" );
         }

         if( key == 'f' )
         {
            cout << " f- load ad01 for ios" << endl;
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            bool requested = false;
            while( itCategory != categories.end() && requested == false )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
               
               if( numInCategory > 0 )
               {
                  for( int i=0; i<numInCategory; i++ )
                  {
                     AssetInfoExtended asset;
                     network.GetAssetInfo( categoryName, i, asset );
                     if( asset.assetName == targetFile [ currentFile ] )
                     {
                        network.RequestAssetByHash( asset.assetHash );
                        cout << "requested: " << asset.assetName << endl;
                        requested = true;
                        break;
                     }
                  }
               }
               else
               {
                  cout << "not enough in this category" << endl;
               }
            }
         }
         if( key == 's' )
         {
            cout << " s- save ad01 for ios" << endl;
             vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            bool isDone = false;
            while( itCategory != categories.end() && isDone == false )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
               
               if( numInCategory > 0 )
               {
                  for( int i=0; i<numInCategory; i++ )
                  {
                     AssetInfoExtended asset;
                     network.GetAssetInfo( categoryName, i, asset );
                     if( asset.assetName == targetFile [ currentFile ] )
                     {
                        isDone = true;
                        if( asset.IsAssetFullyLoaded() == false )
                        {
                           cout << "Asset not loaded" << endl;
                           break;
                        }
                        else
                        {
                           U8* ptr = asset.data;
                           int size = asset.size;
                           std::ofstream file;
                           string filename = "C:/temp/" + targetFile [ currentFile ] + ".dek";
                           remove( filename.c_str() );
                           file.open( filename.c_str(), ofstream::binary|ofstream::out );
                           file.write( (const char*)ptr, size );
                           file.close();
                           
                           break;
                        }
                     }
                  }
               }
               else
               {
                  cout << "not enough in this category" << endl;
               }
            }
         }
         if( key == 'n' )
         {
            currentFile ++;
            if( currentFile  >= numFiles )
               currentFile = 0;

            cout << "File selected: " << targetFile [ currentFile ] << endl;
         }

         if( key == '1' )
         {
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               int numInCategory = network.GetNumAssets( categoryName );
               cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
               
               if( numInCategory > 0 )
               {
                  AssetInfoExtended asset;
                  network.GetAssetInfo( categoryName, 0, asset );
                  network.RequestAssetByHash( asset.assetHash );
                  cout << "requested: " << asset.assetName << endl;
               }
               else
               {
                  cout << "not enough in this cat" << endl;
               }
            }
            cout << "Done with request" << endl;
           
         }

         if( key == '3' )
         {
            vector< string > categories;
            network.GetAssetCategories( categories );
            cout << "Asset categories: " << categories.size() << endl;
            vector< string > ::iterator itCategory = categories.begin();
            while( itCategory != categories.end() )
            {
               const string& categoryName = *itCategory++;
               if( categoryName == "icons" )
               {
                  int numInCategory = network.GetNumAssets( categoryName );
                  cout << "Category name: " << categoryName << " num=" << numInCategory << " ------------- " << endl;
                  
                  if( numInCategory > 0 )
                  {
                     AssetInfoExtended asset;
                     network.GetAssetInfo( categoryName, 0, asset );
                     network.RequestAssetByHash( asset.assetHash );
                     cout << "requested: " << asset.assetName << endl;
                  }
                  else
                  {
                     cout << "not enough in this cat" << endl;
                  }
               }
            }
            cout << "Done with request" << endl;
           
         }

        
         if( key == 13 )// carriage return
         {
           // clrscr();
            system("cls");// ms specific
            cout << "Login:: user: "******" email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;
            ListAssetSaveToFileInstructions ();
         }
         //---------------------------------
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