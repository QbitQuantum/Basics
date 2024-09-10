 template<typename Iter> inline int _parse_quadhex(input<Iter> &in) {
   int uni_ch = 0, hex;
   for (int i = 0; i < 4; i++) {
     if ((hex = in.getc()) == -1) {
   return -1;
     }
     if ('0' <= hex && hex <= '9') {
   hex -= '0';
     } else if ('A' <= hex && hex <= 'F') {
   hex -= 'A' - 0xa;
     } else if ('a' <= hex && hex <= 'f') {
   hex -= 'a' - 0xa;
     } else {
   in.ungetc();
   return -1;
     }
     uni_ch = uni_ch * 16 + hex;
   }
   return uni_ch;
 }