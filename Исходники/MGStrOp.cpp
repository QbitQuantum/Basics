 //-----------------------------------------------------------------------------
 void MGStrOp::toString( U64 src,std::string& dest )
 {
     Char8 buff[21] = {0}; 
     _ui64toa_s(src,buff,20,10);
     dest = buff;
 }