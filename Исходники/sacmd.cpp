 byte getWUSresult(MemoryBuffer &mb)
 {
     byte ret = 0;
     wusbuf.swapWith(mb);    
     if (mb.length()==1) {
         mb.read(ret);
         mb.clear();
     }
     return ret;
 }