 void init() {
     if (fOnce.once()) {
         fBitmap = createBitmap(64, 64);
     }
 }