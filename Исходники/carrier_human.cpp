 virtual bool checkHeader(const Bytes& header) {
     if (header.length()!=8) {
         return false;
     }
     const char *target = "HUMANITY";
     for (int i=0; i<8; i++) {
         if (header.get()[i] != target[i]) {
             return false;
         }
     }
     return true;
 }