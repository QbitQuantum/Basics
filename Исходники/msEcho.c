/* ----------------------------------------------------------------------------
MidiShare setup
---------------------------------------------------------------------------- */
Boolean SetUpMidi(void)
{
  if ( !MidiShare() ) {
                printf("MidiShare is not installed\n");
                return false;
  }
  myRefNum = MidiOpen(AppliName);
  if ( myRefNum == MIDIerrSpace ) {
                printf("Too much MidiShare client applications\n");
                return false;
  }
  MidiSetRcvAlarm(myRefNum,ReceiveEvents);
  InstallFilter();
  MidiConnect (myRefNum, 0, true);
  MidiConnect (0, myRefNum, true);
  return true;
}