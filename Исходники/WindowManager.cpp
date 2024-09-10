 // called every couple of lines. Use it to check for events
 void Turing_StdlibSFML_PeriodicCallback() {
     // check every quarter of a second. This does make input delayed.
     // It only stops the system from deeming us unresponsive
     if(WinMan && eventClock.GetElapsedTime() > 0.5) {
         WinMan->surface();
         eventClock.Reset();
     }
 }