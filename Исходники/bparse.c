void bparse_test( FILE *FH ) {
    char *s;
    size_t bd_sz = 0, i;
    struct bdeque **bd=xmalloc(bd_sz), /* Array of bdeque pointers */
                  *deque;

    while ( !feof(FH) ) {
        /* Get a line from the file */
        s=b_gets(FH,INPUT_BLOCKSIZE);
        /* Remove comments */
        strtrunc(s,comment_chars);
        /* Remove trailing new line */
        chomp(s);
        /* Tokenize line and load into a deque */
        deque = blex(s);

        if ( bdeque_count( deque ) > 0 ) {
            /* Grow the bdeque pointer array by one and append the new deque to the end */
            struct bdeque **temp = xrealloc(bd,sizeof(*bd)*(++bd_sz));
            bd = temp;
            bd[bd_sz-1] = deque;
        }
    }
    printf("<<DEQUE PRINT>>\n");
    /* Print the bdeques */
    for (i=0; i<bd_sz; i++)
        bdeque_print(bd[i]);
    printf("<<END DEQUE PRINT>>\n");
    for (i=0; i<bd_sz; i++) {
        struct bdeque *deque = bd[i], *dupdeque = bdeque_create();
        struct d_elem *node = deque->head;
        /* Keep track of operation count. If the line isn't 'done' and we can't do operations on it, we don't want to loop on it forever */
        unsigned int ops = 0;
        while ( node != NULL ) {
            struct d_elem *retnode = NULL; // Node returned by the current operation
            int def = is_def(*node->var->value);
            if ( def != -1 ) {
                if ( defs[def].operands == 2 ) {
                    retnode = defs[def].op( node->prev, node->next ); // Perform the binary operation of the current defined operator and place the result into retnode.
                    //bdeque_npush( dupdeque, defs[def].op( node->prev, node->next ) );
                // FIXME: I don't put my return value back into the deque.
                } else if ( defs[def].operands == 1 ) {
                    //struct d_elem *retval = defs[def].op( node->next );
                    retnode = defs[def].op( node->next ); // Perform the unary operation of the current defined operator and place the result into retnode.
                    //defs[def].op( node->next );
                    //if ( retval != NULL ) 
                    //    bdeque_npush( dupdeque, retval );
                } else if ( defs[def].operands == 0 ) {
                    defs[def].op( node->next );
                } else {
                    bdeque_npush( dupdeque, d_elem_copy(node) );
                }
            } //else {
                //bdeque_npush( dupdeque, d_elem_copy(node) );
            //}
            /*
            int def = is_def(*node->var->value);
            if ( def != -1 ) {
                if ( defs[def].operands == 1 )
                    b_PRINT( defs[def].op( node->next ) );
                else if ( defs[def].operands == 2 )
                    b_PRINT( defs[def].op( node->prev, node->next ) );
            }
            */
            if ( node->next == NULL )
                break;
            //else if ( node->next->prev == node )
            if ( retnode != NULL ) {
                
            }
            node = node->next;
        }
        bdeque_print( dupdeque );

    }
}