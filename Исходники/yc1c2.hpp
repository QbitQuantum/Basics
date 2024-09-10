 ColorVal max(int p) const {
   switch(p) {
     case 0: return maximum;
     case 1: return maximum;
     case 2: return maximum;
     default: return ranges->max(p);
   };
 }