 VideoGlobalState() {
     /* first let's make sure we are running on 1.1 */
     WORD wVer = HIWORD(VideoForWindowsVersion());
     if (wVer < 0x010a) {
         throw openrave_exception("can't init avi library");
     }
     AVIFileInit();
 }