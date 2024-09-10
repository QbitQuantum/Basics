/* midi_win32_in_init:
 */
int midi_win32_in_init(int input, int voices)
{
   MMRESULT hr;
   int id;

   /* deduce our device number from the driver ID code */
   id = (midi_input_driver->id & 0xFF) - 'A';

   /* open midi input device */
   hr = midiInOpen(&midi_in_device, id, (DWORD)midi_in_proc,
		   (DWORD)NULL, CALLBACK_FUNCTION);
   if (hr != MMSYSERR_NOERROR) {
      _TRACE(PREFIX_E "midiInOpen failed (%x)\n", hr);
      midi_win32_in_exit(input);
      return -1;
   }


   midiInReset(midi_in_device);
   midiInStart(midi_in_device);

   return 0;
}