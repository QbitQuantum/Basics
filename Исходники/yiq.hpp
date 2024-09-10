 ColorVal max(int p) const { switch(p) {
                                     case 0: return 4*par-1;
                                     case 1: return 8*par-2;
                                     case 2: return 8*par-2;
                                     default: return ranges->max(p);
                                      };
                           }