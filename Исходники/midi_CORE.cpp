/* ------------------------------------------------------------------------- */
int InitMidi()
{
if ( !MidiShare())
{
sprintf (string_Last_Order,"MidiShare not available\n");
}
InitTblLibEv();
myRefNum = MidiOpen(AppliName);
if (myRefNum < 0) {sprintf(string_Last_Order,"MidiOpen failed!");}

MidiSetRcvAlarm(myRefNum,ReceiveEvents);
MidiConnect(0, myRefNum, true);//in
MidiConnect(myRefNum,0,true);//out
myFilter = MidiNewFilter();
InstallFilter( myRefNum,myFilter ); //filtrage

return(0);
}