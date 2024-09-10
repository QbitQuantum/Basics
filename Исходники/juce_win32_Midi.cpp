 void stop()
 {
     if (isStarted)
     {
         isStarted = false;
         midiInReset (deviceHandle);
         midiInStop (deviceHandle);
         activeMidiCollectors.removeValue (this);
         unprepareAllHeaders();
         concatenator.reset();
     }
 }