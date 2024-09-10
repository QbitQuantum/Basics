revtrie loadRevTrie(FILE *f, lztrie trie)
 { 
    revtrie T;
    uint *emptybmap;
    unsigned long long aux;
    T = malloc(sizeof(struct srevtrie));
    if (fread(&T->n,sizeof(uint),1,f) != 1) {
       fprintf(stderr,"Error: Cannot read RevTrie from file\n");
       exit(1);
    }
    aux = (2*(unsigned long long)T->n+W-1)/W;
    T->data = malloc(aux*sizeof(uint));
    if (fread(T->data,sizeof(uint),aux,f) != aux) {
       fprintf (stderr,"Error: Cannot read RevTrie from file\n");
       exit(1);
    }                                                                       
    T->pdata = createParentheses(T->data,2*T->n,false,true);
    // loads the bitstring indicating the empty nodes
    emptybmap = malloc(((T->n+W-1)/W)*sizeof(uint));
    if (fread(emptybmap,sizeof(uint),(T->n+W-1)/W,f) != (T->n+W-1)/W) {
       fprintf(stderr,"Error: Cannot read RevTrie from file\n");
       exit(1);
    }
    // creates, from the above bitstring, the bitmap indicating the empty nodes
    T->B = createBitmap(emptybmap, T->n, false);
    T->nbits = bits(trie->n-1);
    aux = (((unsigned long long)trie->n)*trie->nbits+W-1)/W;
    T->rids_1 = malloc(aux*sizeof(uint));
    if (fread(T->rids_1,sizeof(uint),aux,f)!= aux) {
       fprintf(stderr,"Error: Cannot read RevTrie from file\n");
       exit(1);
    }
    
    T->trie = trie;
    return T;
 }