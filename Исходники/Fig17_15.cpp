// create formatted text file for printing
void createTextFile( fstream &readFromFile )
{
   // create text file
   ofstream outPrintFile( "print.txt", ios::out );

   // exit program if ofstream cannot create file
   if ( !outPrintFile ) 
   {
      cerr << "File could not be created." << endl;
      exit( 1 );
   } // end if

   outPrintFile << left << setw( 10 ) << "Account" << setw( 16 )
      << "Last Name" << setw( 11 ) << "First Name" << right
      << setw( 10 ) << "Balance" << endl;

   // set file-position pointer to beginning of readFromFile
   readFromFile.seekg( 0 );

   // read first record from record file
   ClientData client;
   readFromFile.read( reinterpret_cast< char * >( &client ),
      sizeof( ClientData ) );

   // copy all records from record file into text file
   while ( !readFromFile.eof() ) 
   {
      // write single record to text file
      if ( client.getAccountNumber() != 0 ) // skip empty records
         outputLine( outPrintFile, client );

      // read next record from record file
      readFromFile.read( reinterpret_cast< char * >( &client ), 
         sizeof( ClientData ) );
   } // end while
} // end function createTextFile