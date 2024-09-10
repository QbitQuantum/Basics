perm2 createPerm2(unsigned int *elems, unsigned int nelems, unsigned int t, static_bitsequence_builder * bmb) {//if uints is set to true the given array is of uints using 32 bits each
  perm2 P;
  unsigned int *b, *baux, nextelem, i, j, bptr,
    aux, antbptr,nbwdptrs, elem,nbits, firstelem, cyclesize;
  auxbwd2 *auxbwdptr;
  P = new struct sperm2;
  P->elems  = elems;
  P->nelems = nelems;
  P->nbits  = bits(nelems-1);
  nbits = bits(nelems-1);
  P->t = t;
  if (t==1) {
    P->bwdptrs = new unsigned int[uint_len(nelems,nbits)];
    for(unsigned int m=0;m<uint_len(nelems,nbits);m++)
        P->bwdptrs[m]=0;
    assert(P->bwdptrs!=NULL);
    P->nbwdptrs = nelems;
    for (i=0; i<nelems; i++) {
      unsigned int bg = elems[i];
      assert(bg<nelems);
      set_field(P->bwdptrs, nbits, bg, i);
    }
    P->bmap = NULL;
  }
  else {
    auxbwdptr = new auxbwd2[(t+((int)ceil((double)nelems/t)))];
    assert(auxbwdptr!=NULL);
    b = new unsigned int[uint_len(nelems,1)];
    for(i=0;i<uint_len(nelems,1);i++)
      b[i]=0;
    assert(b!=NULL);    
    baux = new unsigned int[uint_len(nelems,1)];
    for(i=0;i<uint_len(nelems,1);i++)
      baux[i] = 0;
    assert(baux!=NULL);
    nbwdptrs = 0;
    for (i = 0; i < nelems; i++) {
      if (bitget(baux,i) == 0) {
        nextelem = j = bptr = antbptr = i;
        aux = 0;
        bitset(baux, j);
        cyclesize = 0;
        firstelem = j;
        while ((elem=elems[j]) != nextelem) {//P->elems[j]
          j = elem;
          bitset(baux, j);
          aux++;
          if (aux >= t) {
            auxbwdptr[nbwdptrs].key = j;
            auxbwdptr[nbwdptrs++].pointer = bptr;
            antbptr = bptr;
            bptr    = j;
            aux     = 0;
            bitset(b, j);
          }
          cyclesize++;
        }
        if (cyclesize >= t) {
          auxbwdptr[nbwdptrs].key = nextelem;
          auxbwdptr[nbwdptrs++].pointer = bptr;
          bitset(b, nextelem);
        }
      }
    }
    qsort(auxbwdptr, nbwdptrs, sizeof(auxbwd2), &compare2);
    aux = uint_len(nbwdptrs,P->nbits);
    P->bwdptrs = new unsigned int[aux];
    assert(P->bwdptrs!=NULL);
    for(i=0;i<aux;i++) P->bwdptrs[i] = 0;
    P->nbwdptrs = nbwdptrs;
    for (i = 0; i < nbwdptrs; i++) {
      set_field(P->bwdptrs, nbits, i, auxbwdptr[i].pointer);
      //if(i<5) 
      //  printf(" %d ",get_field(P->bwdptrs,nbits,i));
    }
    //printf("\n");
    P->bmap = bmb->build(b, nelems);
    //delete [] P->bmap;
    delete [] b;
    delete [] (baux);
    delete [] (auxbwdptr);
  }
  return P;
}