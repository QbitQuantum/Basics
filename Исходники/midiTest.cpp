int main() 
{
  std::vector<unsigned char> message;
  RtMidiOut *midiout = new RtMidiOut();
  // Check available ports.
  unsigned int nPorts = midiout->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    goto cleanup;
  }
  cout<<"sending messages"<<endl;
  // Open first available port.
  midiout->openPort( 0 );
  // Send out a series of MIDI messages.
  // Program change: 192, 5
  message.push_back( 192 );
  message.push_back( 5 );
  midiout->sendMessage( &message );
  // Control Change: 176, 7, 100 (volume)
  message[0] = 176;
  message[1] = 7;
  message.push_back( 100 );
  midiout->sendMessage( &message );
  // Note On: 144, 64, 90
  message[0] = 144;
  message[1] = 64;
  message[2] = 90;
  midiout->sendMessage( &message );
sleep(1);
  message[0] = 144;
  message[1] = 64;
  message[2] = 90;
  midiout->sendMessage( &message );
sleep(3);
cout<<"inside"<<endl;
	int bend;
while(1){
cin>>bend;
if (!bend) break;
			message[0] = 224;
			message[1] = 0;
			message[2] = bend;
			midiout->sendMessage( &message );
}
  // Note Off: 128, 64, 40
  message[0] = 128;
  message[1] = 64;
  message[2] = 40;
  midiout->sendMessage( &message );
  // Clean up
 cleanup:
  delete midiout;
}