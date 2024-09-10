 void QSort(T *sa,
            S *pa,
            int na,
            int (*comp)(const T&, const T&) = gpstk::Qsort_compare)
 {
    int i,j,nr;
    T stemp, spart;
    S ptemp, ppart;
    while(1) { 
       if(na < 8) {                     // use insert sort for small arrays
          insert(sa,pa,na,comp);
          return;
       }
       spart = sa[na/2];                // pick middle element as pivot
       ppart = pa[na/2];
       i = -1; 
       j = na;
       while(1) {
          do {                          // find first element to move right
             i = i + 1;
          } while(comp(sa[i],spart) < 0);
          do {                          // find first element to move left
             j = j - 1;
          } while(comp(sa[j], spart) > 0);
                                        // if the boundaries have met,
                                        // through paritioning,
          if(i >= j) break;
                                        // swap i and j elements
          stemp = sa[i]; ptemp = pa[i];
          sa[i] = sa[j]; pa[i] = pa[j];
          sa[j] = stemp; pa[j] = ptemp;
       }
       nr = na - i;
       if(i < (na/2)) {                 // now sort each partition
          QSort(sa, pa, i, comp);       // sort left side 
          sa = &sa[i];                  // sort right side here
          pa = &pa[i];
          na = nr;                      // memsort(&(sa[i]),nr,comp);
       }
       else { 
          QSort(&(sa[i]), &(pa[i]), nr, comp);    // sort right side
          na = i;
       }
    }
 }  // end QSort