 ColorVal max(int p) const { switch(p) {
                                     case 0: return 0;
                                     case 1: return nb_colors-1;
                                     case 2: return 0;
                                     default: return ranges->max(p);
                                      };
                           }