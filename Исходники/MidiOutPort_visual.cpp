void MidiOutPort_visual::closeAll(void) {
   for (int i=0; i<getNumPorts(); i++) {
      if (openQ[i] == 1 && device[i] != NULL) {
         midiOutReset(device[i]);
         midiOutClose(device[i]);
         openQ[i] = 0;
      }
   }
}