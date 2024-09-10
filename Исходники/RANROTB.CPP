 // returns a random number between 0 and 1:                                             
 double TRanrotBGenerator::Random() {                                                    
   uint32 x;                                                                             
   // generate next random number                                                        
   x = randbuffer[p1] = _lrotl(randbuffer[p2], R1) + _lrotl(randbuffer[p1], R2);         
   // rotate list pointers                                                               
   if (--p1 < 0) p1 = KK - 1;                                                            
   if (--p2 < 0) p2 = KK - 1;                                                            
   // perform self-test                                                                  
   if (randbuffer[p1] == randbufcopy[0] &&                                               
     memcmp(randbuffer, randbufcopy+KK-p1, KK*sizeof(uint32)) == 0) {                    
       // self-test failed                                                               
       if ((p2 + KK - p1) % KK != JJ) {                                                  
         // note: the way of printing error messages depends on system                   
         // In Windows you may use FatalAppExit                                          
         printf("Random number generator not initialized");}                             
       else {                                                                            
         printf("Random number generator returned to initial state");}                   
       exit(1);}                                                                         
   // conversion to float:                                                               
   union {double f; uint32 i[2];} convert;                                               
   switch (Architecture) {                                                               
   case LITTLEENDIAN:                                                                    
     convert.i[0] =  x << 20;                                                            
     convert.i[1] = (x >> 12) | 0x3FF00000;                                              
     return convert.f - 1.0;                                                             
   case BIGENDIAN:                                                                       
     convert.i[1] =  x << 20;                                                            
     convert.i[0] = (x >> 12) | 0x3FF00000;                                              
     return convert.f - 1.0;                                                             
   case NONIEEE: default:                                                                
   ;}                                                                                    
   // This somewhat slower method works for all architectures, including                 
   // non-IEEE floating point representation:                                            
   return (double)x * (1./((double)(uint32)(-1L)+1.));}                                  