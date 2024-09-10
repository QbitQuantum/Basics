 void processKeys(void) {
     XEvent event;
     while (XCheckWindowEvent(display, window, StructureNotifyMask | KeyPressMask, &event)) {
         processEvent(event);
     }
 }