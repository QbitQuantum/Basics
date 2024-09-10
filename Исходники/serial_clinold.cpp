int main(int argc, char* argv[])
{
  int type;
  const char * port="8786";
  const char * server_name="192.168.1.9";
  const char * serial_name="/dev/ttyUSB0"; //default to ttyUSB0
  int baud_rate=115200; // default baud rate
  const char * client="192.168.1.79"; // replace it with a list of clients
  string figa;
  
  for (int i=0; i<argc; i++){
    cout<< argv[i]<<endl;
    figa=argv[i];
    if(figa=="--client"){
      type=SLAVE;
    }
    else if(figa=="--master"){
      type=MASTER; 
    }
    else if(figa=="--host")
      server_name=argv[i+1]; // must be an IP address
    else if(figa=="--serial")
      serial_name=argv[i+1];
    else if(figa=="--baud")
      baud_rate=atoi(argv[i+1]);
    else if(figa=="--port")
      port=argv[i+1]; 
  }

  Joy2Ser * joy = new Joy2Ser("/dev/input/js0",server_name,port);
  joy->openthread();
  delete joy;
  return 0;
}