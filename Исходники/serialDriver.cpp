int main(int argc, char * argv[])
{
   char newline = '\n';
   char cmd[2] = {'V', 'V'};
   char blockread[] = { '5', 'R' , 0x00, 0x00, 0x00, 0x00 };
   char block[257];
   unsigned char sum;

   int tmp, i, j ;
   char tmpc;
   Serial serialPort;

   if(argc != 3)
   {
      cerr<< "Usage: " << argv[0] << " <Serial device> <string to send>" << endl;
      return false;
   }

   std::string pname(argv[1]);
   std::string command(argv[2]);

   if(serialPort.setPort(pname))
      cerr << "setPort OK" << endl;
   else
      cerr << "setPort NOK" << endl;

   if(serialPort.openCommPort())
      cerr << "openCommPort OK " << endl;
   else
      cerr << "openCommPort NOK: " << pname << endl;

   serialPort.setSpeedAndDataBits(921600,8,'n',1);

   serialPort.setTimeouts(5,50,50,50,50);

   if( serialPort.applySettings())
      cerr << "applySettings OK" << endl;
   else
      cerr << "applySettings NOK" << endl;

   if (!serialPort.sendBytes(( char *) command.c_str(), command.length()))
   {
      cerr << "Error with sending command" << endl;
      return false;
   }
   else
      cerr << "sendBytes OK" << endl;

   while(serialPort.getByte(&tmpc))
      cout << "returned byte is: " << hex << (int) tmpc << endl;

   for( i = 0; i < 256; i++)
   {
      cerr << "reading block: " << i ;
      blockread[3] = i;

      for(sum = j = 0; j < 5; j++)
         sum += blockread[j];

      blockread[5] = sum;

      if(!serialPort.sendBytes(blockread, 6))
         cerr << " send commands for blockread failed" << endl;

      else if(!serialPort.getBytes(block, 257))
         cerr << " read data failed" << endl;

      for(sum = j = 0; j < 256; j++)
         sum += block[j];

      if( sum != block[256] )
         cerr << "checksum invalid " << endl;
      else
         cerr << " OK " << endl;

   }
   return true;
}