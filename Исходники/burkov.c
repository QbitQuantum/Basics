void dicho_tree_notrecursive(node_t *head, const int size, item_t *items){
  int p_size = 1, pnext_size = 2;
  node_t *p = head, *pnext, *t1, *t2;
  int *sizes = (int*)malloc(2*sizeof(int)), // size of accordingly subtree items
      *indexes = sizes + 1, // start index of items that belongs to accordingly subtree
      *tmpsizes, *tmpindexes, *ss, *ii, *ss2, *ii2;
    *sizes = size; *indexes = 0;

  // creating a maximum symmetric tree
  int dp = (int)log2f ((float)size); // tree's depth
  int i;
  for ( i = 0 ; i < dp ; i++ ){
    //1: pnext = (node_t*)calloc (pnext_size, NODE_SIZE); // the next level of tree
    pnext = p + p_size; // the next level of tree
    ss = (int*)malloc (2*pnext_size*sizeof(int));
    ii = ss + pnext_size;

    t2 = pnext;
    ss2 = ss;
    ii2 = ii;
    tmpsizes = sizes; // for free()
    //tmpindexes = indexes; // for free()
    int j = 0, d;
    for( t1 = p ; t1 < p + p_size ; t1++ ){
      d = (*sizes) / 2;
        *ss2 = d;
        *(ss2+1) = (*sizes) - d;
        ss2 = ss2 + 2;
        *ii2 = (*indexes);
        *(ii2+1) = (*indexes) + d;
        ii2 = ii2 + 2;
        sizes++;
        indexes++;

      t1->lnode = t2;
      t2->hnode = t1; t2++;
      t1->rnode = t2;
      t2->hnode = t1; t2++;
      j++;
    }
    sizes = ss;
    indexes = ii;
    free (tmpsizes);
    //free(tmpindexes); commented because ss = malloc; ii = ss + ...

    p = pnext;
    p_size = pnext_size;
    pnext_size <<= 1;
  } // for i

  // hang up all remaining items (where sizes[i]==2)
  //t2 = p;
  item_t *tmp;
  pnext = p + p_size;
  for( i = 0 ; i < p_size ; i++ ){
    if( sizes[i] > 2 ) { printf("size of leaf more than 2\n"); fflush(stdout); }
    if( sizes[i] == 2 ){
      //1: pnext = (node_t*)calloc (2,NODE_SIZE);
      pnext->items = NULL;
      tmp = copyitem (&items[indexes[i]]);
      HASH_ADD_KEYPTR (hh, pnext->items, tmp->w, KNINT_SIZE, tmp);
      pnext->length = 1;
      p->lnode = pnext;
      pnext->hnode = p; pnext++;

      pnext->items = NULL;
      tmp = copyitem (&items[indexes[i]+1]);
      HASH_ADD_KEYPTR (hh, pnext->items, tmp->w, KNINT_SIZE, tmp);
      pnext->length = 1;
      p->rnode = pnext;
      pnext->hnode = p; pnext++;
    } else if( sizes[i] == 1 ){
      p->items = NULL;
      tmp = copyitem (&items[indexes[i]]);
      HASH_ADD_KEYPTR (hh, p->items, tmp->w, KNINT_SIZE, tmp);
      p->length = 1;
    } else {
      // error
      printf("size of leaf is non-positive?\n");
      fflush(stdout);
    }
    p++;
  }

}// dicho_tree_notrecursive()