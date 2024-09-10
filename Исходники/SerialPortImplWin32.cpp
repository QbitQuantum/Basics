// Transmit a continuous stream of zero bits for the given duration.  If the
// argument is 0, the transmission will last between 0.25 and 0.5 seconds.
// Otherwise, the duration specfies the number of seconds to send the zero bit
// stream.
void SerialPortImplWin32::sendBreak(const vpr::Int32 duration)
{
   DWORD flags;

   //Send a break for .5 seconds
   SetCommBreak(mHandle);
   Sleep(500);
   ClearCommBreak(mHandle);
   Sleep(35);
   ClearCommError(mHandle,&flags,NULL); //Clear the break error
}