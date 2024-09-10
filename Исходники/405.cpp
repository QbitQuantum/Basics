 string toHex(int num) {
     string hex = "";
     int n = num;
     unsigned bin;
     for (int i = 0; i < 8; i++) {
         bin = 15 << ((7 - i) * 4);
         bin = (bin & n) >> ((7 - i) * 4);
         char h = intToChar(bin);
         if (bin != 0 || hex.size() != 0)
             hex.push_back(h);
     }
     if (hex.size() == 0) hex = "0";
     return hex;
 }